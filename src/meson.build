##### Generate and install libsamplewebextension.so
libsamplewebextension_sources = ['sample_web_extension.cpp']

webkit_port_libdir = webkit_port_dep.get_pkgconfig_variable('libdir')
webkit_extension_install_dir = join_paths(webkit_port_libdir, webkit_extension_path)

lib_dep = [webkit_port_dep, webkit_port_web_extension_dep, glib_dep]
sample_web_ext = shared_library('samplewebextension',
                                libsamplewebextension_sources,
                                include_directories : includedir,
                                dependencies : lib_dep,
                                install: true,
                                install_dir : webkit_extension_install_dir)
