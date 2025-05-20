file(GLOB CHILD_DIRS LIST_DIRECTORIES true *)

foreach(dir ${CHILD_DIRS})
    if(IS_DIRECTORY ${dir} AND EXISTS "${dir}/CMakeLists.txt")
        add_subdirectory(${dir})
    endif()
endforeach()