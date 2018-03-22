#!/bin/bash

clang_format_version=6.0

do_find_clang_format() {
    result=`which clang-format-${clang_format_version}` && echo ${result} && exit 0
    result=`which clang-format` && echo ${result} && exit 0
    exit 1
}

find_clang_format() {
    clang_format=`do_find_clang_format` || exit 1

    actual_version=`${clang_format} --version | grep -oP "version \K(\d\.\d)"`
    if [[ ${actual_version} != ${clang_format_version} ]]; then exit 1; fi

    echo ${clang_format}
    exit 0
}

initial_state=`git status | grep "modified"`
if ! [[ -z $initial_state ]]; then
    echo "Clang-format script must be applied on a clean git state"
    exit 1
fi

clang_format=`find_clang_format`
if [[ $? -ne 0 ]]; then echo "clang-format ${clang_format_version} not found"; exit 0; fi
echo "Found ${clang_format}"

clang_format_opts="-style=file -assume-filename=.clang-format -i"

src_dirs=(
    igd
    ui
)

file_list=`find "${src_dirs[@]}" -type f | grep -E "^.*\.(cxx|hxx)$"`
for file in $file_list; do
    ${clang_format} ${clang_format_opts} ${file}
done

final_filelist=`git status | grep "modified"`
if [[ -z $final_filelist ]]; then
    echo "Code-style is pretty good :thumbsup:"
    exit 0;
fi

echo "Read code-style guide again and apply those patches:"
git diff

exit 1
