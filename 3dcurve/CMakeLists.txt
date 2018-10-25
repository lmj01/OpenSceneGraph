
set(PROJECT_NAME "3dcurve")
set(SRC_main
	Data.h
	Callbacks.h
	osgShader.cpp
)

find_package(OpenThreads REQUIRED)
find_package(osg REQUIRED)
find_package(osgViewer REQUIRED)
find_package(osgGA REQUIRED)
find_package(osgDB REQUIRED)
find_package(osgUtil REQUIRED)
find_package(osgManipulator REQUIRED)
find_package(osgVolume REQUIRED)

include_directories(${OSG_INCLUDE_DIR})
include_directories(${OSG_ROOT}/include)

link_directories(${OSG_ROOT}/lib)
link_directories(${OSG_ROOT}/debug/lib)

ADD_EXECUTABLE(3dcurve ${SRC_main})
LMJ_LINK(3dcurve OpenThreads)
LMJ_LINK(3dcurve osg)
LMJ_LINK(3dcurve osgViewer)
LMJ_LINK(3dcurve osgUtil)
LMJ_LINK(3dcurve osgDB)
LMJ_LINK(3dcurve osgGA)

