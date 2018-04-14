#!/usr/bin/env python

import argparse
import sys

def tab():
    return '    '

def tabulate(*lines):
    def mapper(line):
        if isinstance(line, list):
            return list(map(mapper, line))
        return tab() + line
    return list(map(mapper, lines))

def to_pointer(type):
    return '{}*'.format(type)

def include_guard():
    return '#pragma once'

def include_directive(file):
    return '#include <{}>'.format(file)

def class_begin(typename, basename):
    return 'class {} : public {} {{'.format(typename, basename)

def class_end():
    return '};'

def private_qualifier():
    return 'private:'

def public_qualifier():
    return 'public:'

def signals_qualifier():
    return 'signals:'

def qinvokable_declaration():
    return 'Q_INVOKABLE'

def nullptr_literal():
    return 'nullptr'

def member_identifier(name):
    return '_{}'.format(name)

def member_declaration(type, name):
    return '{} {};'.format(type, member_identifier(name))

def member_declarations(members):
    return list(map(lambda arg: member_declaration(*arg), members))

def using_directive(alias, target):
    return 'using {} = {};'.format(alias, target)

def self_typedef(target):
    return using_directive('Self', target)

def qobject_declaration():
    return 'Q_OBJECT'

def property_getter_identifier(name):
    return name

def property_setter_identifier(name):
    return 'set{}'.format(name.title())

def property_signal_identifier(name):
    return '{}Changed'.format(name)

def property_declaration(type, name):
    return 'Q_PROPERTY({} {} READ {} WRITE {} NOTIFY {})'.format(type, name, property_getter_identifier(name), property_setter_identifier(name), property_signal_identifier(name))

def property_declarations(properties):
    return list(map(lambda arg: property_declaration(*arg), properties))

def parent_identifier():
    return 'parent'

def initializer_list_entry(member):
    return ', {}()'.format(member_identifier(member))

def initializer_list(members):
    return list(map(initializer_list_entry, members))

def constructor(type, parent, base, members):
    return [
        '{}({} {} = {})'.format(type, to_pointer(parent), parent_identifier(), nullptr_literal()),
        tabulate( \
            ': {}({})'.format(base, parent_identifier()), \
            initializer_list(members) \
        ),
        '{}',
        ''
    ]

def expand_function_args(args):
    def fold(s, type, name):
        comma_if = '' if s == '' else ', '
        return s + '{}{} {}'.format(comma_if, type, name)
    return reduce(lambda s, arg: fold(s, *arg), args, '')

def function_declaration(ret, identifier, this_qualifier='', args=[]):
    space_if = '' if this_qualifier == '' else ' '
    return '{} {}({}){}{}'.format(ret, identifier, expand_function_args(args), space_if, this_qualifier)

def forward_declaration(*args):
    return '{};'.format(function_declaration(*args))

def function_begin(*args):
    return '{} {{'.format(function_declaration(*args))

def function_end():
    return '}'

def property_getter(type, name):
    return [
        '{} {}'.format(qinvokable_declaration(), function_begin(type, property_getter_identifier(name), 'const')),
        tabulate( \
            'return {};'.format(member_identifier(name)), \
        ),
        function_end(),
        ''
    ]

def property_getters(properties):
    return list(map(lambda arg: property_getter(*arg), properties))

def property_setter(type, name):
    return [
        '{} {}'.format(qinvokable_declaration(), function_begin('void', property_setter_identifier(name), '', [(type, name)])),
        tabulate( \
            'if ({} == {})'.format(member_identifier(name), name), \
            tab() + 'return;', \
            '', \
            '{} = {};'.format(member_identifier(name), name), \
            'emit {}();'.format(property_signal_identifier(name)) \
        ),
        function_end(),
        ''
    ]

def property_setters(properties):
    return list(map(lambda arg: property_setter(*arg), properties))

def property_signal(name):
    return forward_declaration('void', property_signal_identifier(name))

def property_signals(properties):
    return list(map(property_signal, properties))

def generate_component(stream, options):
    property_types = zip(*options.properties)[0]
    property_names = zip(*options.properties)[1]

    lines = [
        include_guard(),
        '',
        include_directive(options.base),
        include_directive(options.parent),
        '',
        class_begin(options.type, options.base),
        tabulate( \
            self_typedef(options.type), \
            '', \
            qobject_declaration(), \
            '', \
            property_declarations(options.properties), \
        ),
        '',
        private_qualifier(),
        tabulate( \
            member_declarations(options.properties), \
        ),
        '',
        public_qualifier(),
        tabulate( \
            constructor(options.type, options.parent, options.base, property_names), \
            property_getters(options.properties), \
            property_setters(options.properties), \
        ),
        signals_qualifier(),
        tabulate( \
            property_signals(property_names), \
        ),
        class_end(),
    ]

    def fold(s, line):
        if isinstance(line, list):
            return s + reduce(fold, line, '')
        return s + line + '\n'
    lines = reduce(fold, lines, '')

    stream.write(lines)

def property_type(s):
    try:
        type, identifier = map(str, s.split(','))
        return type, identifier
    except:
        raise argparse.ArgumentTypeError('Property must be passed as [type,identifier ...]')

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Generate C++ QML component.')

    parser.add_argument('--type', required=True, \
                        help='Component type')
    parser.add_argument('--properties', type=property_type, nargs='*', default=[], \
                        help='All component properties, (type, identifier)')
    parser.add_argument('--base', default='QObject', \
                        help='Component base type')
    parser.add_argument('--parent', default='QObject', \
                        help='Component parent type')

    args = parser.parse_args()

    generate_component(sys.stdout, args)
