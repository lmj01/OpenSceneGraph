
cmake_minimum_required(VERSION 3.11)

project(lmjOpenSceneGraph)

set(ADDRESS_MODEL 64)
set(NODE_TARGET x64)

set(OSG_DIR "h:/vcpkg/installed/x64-windows")
set(OSG_ROOT "h:/vcpkg/installed/x64-windows")
set(OSG_DEBUG_POSTFIX "d" CACHE STRING "add post d in osg, on windows")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/Dbin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/Dbin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin)

MACRO(LMJ_LINK LMJ_TARGET LMJ_LIBRARY)
	target_link_libraries(${LMJ_TARGET} PRIVATE optimized ${LMJ_LIBRARY})
	target_link_libraries(${LMJ_TARGET} PRIVATE debug ${LMJ_LIBRARY}${OSG_DEBUG_POSTFIX})
ENDMACRO()

add_subdirectory(demo)
add_subdirectory(shader)
add_subdirectory(oglpg8)
