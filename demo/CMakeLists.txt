
set(PROJECT_NAME "demo")
set(SRC_FILES
	main.cpp
)

find_package(OpenThreads REQUIRED)
find_package(osg REQUIRED)
find_package(osgViewer REQUIRED)
find_package(osgGA REQUIRED)
find_package(osgDB REQUIRED)

include_directories(${OSG_INCLUDE_DIR})
link_directories(${OSG_LIB_DIR})

ADD_EXECUTABLE(demo ${SRC_FILES})

target_link_libraries(demo PRIVATE
	debug osg${OSG_DEBUG_POSTFIX}			optimized osg
	debug OpenThreads${OSG_DEBUG_POSTFIX}		optimized OpenThreads
	debug osgViewer${OSG_DEBUG_POSTFIX} 		optimized osgViewer
	debug osgGA${OSG_DEBUG_POSTFIX} 		optimized osgGA
	debug osgDB${OSG_DEBUG_POSTFIX}			optimized osgDB
)
