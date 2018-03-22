#!/bin/bash

current_dir=`dirname "${BASH_SOURCE[0]}"`

"${current_dir}"/run-clang-format.sh && exit 0

git reset HEAD --hard
exit 1
