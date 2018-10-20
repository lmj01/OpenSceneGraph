
set(PROJECT_NAME "oglProgrammingGuide")
set(SRC_test
	test.cpp
)
set(SRC_ch03drawcommands
	ch03drawcommands.cpp
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

ADD_EXECUTABLE(oglpg8_test ${SRC_test})
LMJ_LINK(oglpg8_test OpenThreads)
LMJ_LINK(oglpg8_test osg)
LMJ_LINK(oglpg8_test osgViewer)

ADD_EXECUTABLE(oglpg8_03drawcommands ${SRC_ch03drawcommands})
LMJ_LINK(oglpg8_03drawcommands OpenThreads)
LMJ_LINK(oglpg8_03drawcommands osg)
LMJ_LINK(oglpg8_03drawcommands osgViewer)

