
cmake_minimum_required(VERSION 3.11)

project(lmjOpenSceneGraph)

set(ADDRESS_MODEL 64)
set(NODE_TARGET x64)

set(OSG_DIR "h:/vcpkg/installed/x64-windows")
set(OSG_ROOT "h:/vcpkg/installed/x64-windows")
FIND_PATH(OSG_INCLUD_DIR osg/Referenced
	${OSG_ROOT}/include
	)
FIND_PATH(OSG_LIB_DIR osg.lib
	${OSG_ROOT}/lib
	${OSG_ROOT}/debug/lib
	)
set(OSG_DEBUG_POSTFIX "d" CACHE STRING "add post d in osg, on windows")
set(OSG_FILE_PATH "f:/openscenegraph/OpenSceneGraphData")
set(OSG_PLUGIN_PATH ${OSG_ROOT}/tools/osg/osgPlugins-3.6.2)
set(OSG_BIN_PATH ${OSG_ROOT}/tools/osg/osgPlugins-3.6.2)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(demo)
