let g:column_number_highlight = 160
call ToggleColumnHighlight()
call ToggleColumnHighlight()

autocmd Filetype cpp,python autocmd BufWritePre <buffer> %s/\s\+$//e

let g:ale_c_build_dir='/media/dev/builds/isometric-build'
let g:ale_cpp_clang_executable='clang-6.0'
let g:ale_c_clangformat_executable='clang-format-6.0'
let g:ale_cpp_clang_options='-Wall -Wextra -Wpedantic -std=c++14 -I/media/dev/isometric -I/media/dev/isometric/thirdparty/gum/gum -I/usr/include/eigen3 -I/media/dev/isometric/thirdparty/gum'
let g:ale_linters = {
\   'cpp': ['clang'],
\   'python': ['flake8'],
\}
let g:ale_fixers = {
\   'cpp': ['clang-format'],
\   'python': ['yapf'],
\}

let g:alternateExtensions_cxx = 'hxx'
let g:alternateExtensions_hxx = 'cxx'
