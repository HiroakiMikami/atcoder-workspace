# TODO move them to languages/cc/
file(GLOB_RECURSE files RELATIVE ${PROJECT_SOURCE_DIR} ./**/**.cc)
foreach(file ${files})
    string(REPLACE / - target_ ${file})
    get_filename_component(target ${target_} NAME_WE)
    add_executable(${target} ${PROJECT_SOURCE_DIR}/${file})
endforeach(file)
