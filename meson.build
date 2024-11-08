project('scanner', 'cpp')

subdir('src')

fmt = subproject('fmt')
fmt_dep = fmt.get_variable('fmt_header_only_dep')

executable(
    'scanner',
    sources: ['main.cpp'] + sources,
    include_directories: include_directories('include'),
    dependencies: fmt_dep
)