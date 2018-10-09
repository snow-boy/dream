import sys
import os
from name_convertor import NameConvertor
from datetime import datetime
 
plugin_name = raw_input("module name: ")
name_convertor = NameConvertor(plugin_name)
dest_path = os.path.join('../src/modules', name_convertor.to_aa_bb_cc())
if os.path.exists(dest_path):
    raise '{0} is already exists!'.format(dest_path)

print('begin generate plugin template {0} in {1}'.format(plugin_name, dest_path))

plugin_path = os.path.join(dest_path)
plugin_include_path = os.path.join(dest_path, 'include', plugin_name)
plugin_src_path = os.path.join(dest_path, 'src')

os.makedirs(plugin_path)
os.makedirs(plugin_include_path)
os.makedirs(plugin_src_path)

cmakelist_path = os.path.join(plugin_path, 'CMakeLists.txt')
readme_path = os.path.join(plugin_path, 'readme.txt')

cmake_template = '''\
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${{bin_dir}}/modules)

file(GLOB {prefix}_SRC 
    ${{CMAKE_CURRENT_SOURCE_DIR}}/include/{module_name}/*.h
    ${{CMAKE_CURRENT_SOURCE_DIR}}/src/*.h
    ${{CMAKE_CURRENT_SOURCE_DIR}}/src/*.cpp
)

qt5_wrap_cpp({prefix}_MOC_SRC {prefix}_SRC)

#file(GLOB {prefix}_UI
#    ${{CMAKE_CURRENT_SOURCE_DIR}}/src/*.ui
#)

#qt5_wrap_ui({prefix}_UI_H ${{{prefix}_UI}})
#qt5_add_resources({prefix}_QRC ${{CMAKE_CURRENT_SOURCE_DIR}}/src/resource.qrc)

add_library({module_name} 
            ${{{prefix}_SRC}} 
            ${{{prefix}_MOC_SRC}}
#            ${{{prefix}_UI_H}} 
#            ${{{prefix}_QRC}}
                )

#target_compile_definitions({module_name}  
#    PRIVATE 
#        
#    )

target_include_directories({module_name} 
    PRIVATE
        ${{CMAKE_CURRENT_SOURCE_DIR}}/include/{module_name}
    )

#target_include_modules({module_name} 
#    PRIVATE
#
#    )

#target_link_libraries({module_name} 
#    PRIVATE
#        
#    )

qt5_use_modules({module_name} 
    LINK_PRIVATE
        Core
    )

#target_generate_qt_translation({module_name}
#        ${{{prefix}_SRC}} 
#        ${{{prefix}_UI}}
#    )

'''.format(
    prefix=name_convertor.to_AA_BB_CC(),
    module_name=name_convertor.to_aa_bb_cc()
    )

cmake_file = open(cmakelist_path, 'w')
cmake_file.write(cmake_template)
cmake_file.close()

readme_file = open(readme_path, 'w')
today = datetime.today()
readme_file.write("Created by xuesheng.zhang {0}".format(today.strftime("%Y-%m-%d %H:%M:%S")))
readme_file.close()

print("{0} is generated!".format(plugin_name))
