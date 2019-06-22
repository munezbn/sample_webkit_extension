project('sample_webkit_web_extension', 'cpp',
        version : '0.0.1',
        license: 'MIT'
    )

#########################
# Directories & Options #
########################

top_srcdir = meson.source_root()
includedir = include_directories('include')
webkit_port = get_option('webkit_port')
webkit_extension_path = get_option('extension_path')

###################
# End Directories #
###################

#########################
# External Dependencies #
#########################

glib_dep = dependency('glib-2.0', version: '>= 2.24.1')

if webkit_port == 'wpe'
    webkit_port_dep = dependency('wpe-webkit-1.0', version: '>= 2.24.1')
    webkit_port_web_extension_dep = dependency('wpe-web-extension-1.0', version: '>= 2.24.1')
elif webkit_port == 'gtk'
    webkit_port_dep = dependency('webkit2gtk-4.0', version: '>= 2.24.1')
    webkit_port_web_extension_dep = dependency('webkit2gtk-web-extension-4.0', version: '>= 2.24.1')
else
    error('Invalid webkit_port option : ' + webkit_port)
endif

#############################
# End External Dependencies #
#############################

###############################
# Compiler and Linker options #
###############################

sample_extension_compiler_flag =  ['-rdynamic', '-fvisibility=default']
sample_extension_compiler_flag += ['-Wall', '-Werror']
sample_extension_compiler_flag += ['-Wfloat-equal', '-Wformat=2', '-Wunreachable-code', '-Wundef', '-Winline', '-Wconversion', '-Wswitch', '-Wcast-align', '-Wshadow']
sample_extension_compiler_flag += ['-Wsign-conversion', '-Wint-to-pointer-cast', '-Wcast-function-type', '-Wno-parentheses']

##### Developer Compiler flags #####
sample_extension_compiler_flag += ['-g']

sample_extension_linker_flag = '-Wl,--as-needed'

##### Conditional CPP defines #####

if webkit_port == 'gtk'
sample_extension_compiler_flag += ['-DPLATFORM_GTK']
elif webkit_port == 'wpe'
sample_extension_compiler_flag += ['-DPLATFORM_WPE']
endif

add_project_arguments([sample_extension_compiler_flag, sample_extension_linker_flag], language : 'cpp')

###################################
# End compiler and Linker options #
###################################


#########
# Build #
#########

subdirs = [ 'src' ]

foreach n : subdirs
    subdir(n)
endforeach

#############
# End Build #
#############
