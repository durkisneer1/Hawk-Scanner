project('scanner', 'cpp')

subdir('src')

inc = include_directories('include')
src = ['main.cpp'] + sources

fmt = subproject('fmt')
fmt_dep = fmt.get_variable('fmt_header_only_dep')

executable('scanner', sources: src, include_directories: inc, dependencies: fmt_dep)