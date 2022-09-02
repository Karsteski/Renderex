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

src_files = [
    'src/Main.cpp',
    'src/Buffers/VertexBuffer.cpp'
]

include_dirs = [ 'vendor/stb',
    'src',
    'src/Buffers'
]

executable('renderex',
    sources : src_files,
    dependencies : [glew_dep, glfw_dep, opengl_dep, imgui_dep, glm_dep],
    include_directories : include_dirs
)
