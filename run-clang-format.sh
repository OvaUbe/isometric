#!/bin/bash

current_dir=`dirname "${BASH_SOURCE[0]}"`

${current_dir}/clang-format/run-clang-format.sh "igd ui" "cxx|hxx"
