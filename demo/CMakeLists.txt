
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
include_directories(${OSG_ROOT}/include)

link_directories(${OSG_ROOT}/lib)
link_directories(${OSG_ROOT}/debug/lib)

ADD_EXECUTABLE(demo ${SRC_FILES})

LMJ_LINK(demo OpenThreads)
LMJ_LINK(demo osg)
LMJ_LINK(demo osgViewer)
LMJ_LINK(demo osgGA)
LMJ_LINK(demo osgDB)
