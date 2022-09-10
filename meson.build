project('renderex','cpp', version : '0.1.0',
  default_options : ['cpp_std=c++20', 'buildtype=release', 'warning_level=3'])

# Print relevant options.
message('C++ Version = ' + get_option('cpp_std'))
message('Warning level = ' + get_option('warning_level'))
message('Build type = ' + get_option('buildtype'))
 
glew_dep = dependency('glew', fallback : ['glew', 'glew_dep'])
glfw_dep = dependency('glfw3', fallback : ['glfw', 'glfw_dep'])
opengl_dep = dependency('opengl')
imgui_dep = dependency('imgui', fallback : ['imgui', 'imgui_dep'])
glm_dep = dependency('glm', fallback: ['glm', 'glm_dep'])

main_file = 'src/Main.cpp'

src_files = [
    'src/Auxiliary/Auxiliary.cpp',
    'src/Buffers/VertexBuffer.cpp',
    'src/Buffers/ElementBuffer.cpp',
    'src/Buffers/BufferManager.cpp',
    'src/Model/ModelManager.cpp',

]

include_dirs = [ 
    'vendor/stb',
    'src',
    'src/Buffers',
    'src/Model',
    'src/Auxiliary'
]

executable('renderex',
    sources : [main_file, src_files],
    dependencies : [ glew_dep, glfw_dep, opengl_dep, imgui_dep, glm_dep ],
    include_directories : include_dirs
)

# Testing ---------------------------------------------------------------------------
gtest_main_dep = dependency('gtest_main')
gmock_dep = dependency('gmock')

google_test_deps = [ gtest_main_dep, gmock_dep ]

test_includes = [
  'tests',
]

test_files = [
    'tests/Setup.cpp',
    'tests/Model/ModelManagerTests.cpp',
    'tests/Buffers/VertexBufferTests.cpp',
]

test_exe = executable('tests',
    sources : [ test_files, src_files ],
    dependencies : [ glew_dep, glfw_dep, opengl_dep, imgui_dep, glm_dep, google_test_deps ],
    include_directories : [ include_dirs, test_includes ]
)

test('tests', test_exe)
