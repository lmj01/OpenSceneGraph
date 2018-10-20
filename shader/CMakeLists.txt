
set(PROJECT_NAME "shader")
set(SRC_composition
	composition.cpp
	oldshadercomposition.cpp
)
set(SRC_gl3x
	gl3x.cpp
)
set(SRC_gl4x
	gl4x.cpp
)
set(SRC_tessellation
	tessellation.cpp
)
set(SRC_volume
	volume.cpp
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

ADD_EXECUTABLE(shader_composition ${SRC_composition})
LMJ_LINK(shader_composition OpenThreads)
LMJ_LINK(shader_composition osg)
LMJ_LINK(shader_composition osgViewer)
LMJ_LINK(shader_composition osgDB)

ADD_EXECUTABLE(shader_gl3x ${SRC_gl3x})
LMJ_LINK(shader_gl3x OpenThreads)
LMJ_LINK(shader_gl3x osg)
LMJ_LINK(shader_gl3x osgViewer)
LMJ_LINK(shader_gl3x osgDB)
LMJ_LINK(shader_gl3x osgUtil)

ADD_EXECUTABLE(shader_gl4x ${SRC_gl4x})
LMJ_LINK(shader_gl4x OpenThreads)
LMJ_LINK(shader_gl4x osg)
LMJ_LINK(shader_gl4x osgViewer)
LMJ_LINK(shader_gl4x osgDB)

ADD_EXECUTABLE(shader_tessellation ${SRC_tessellation})
LMJ_LINK(shader_tessellation OpenThreads)
LMJ_LINK(shader_tessellation osg)
LMJ_LINK(shader_tessellation osgViewer)
LMJ_LINK(shader_tessellation osgGA)

ADD_EXECUTABLE(shader_volume ${SRC_volume})
LMJ_LINK(shader_volume OpenThreads)
LMJ_LINK(shader_volume osg)
LMJ_LINK(shader_volume osgViewer)
LMJ_LINK(shader_volume osgGA)
LMJ_LINK(shader_volume osgDB)
LMJ_LINK(shader_volume osgUtil)
LMJ_LINK(shader_volume osgVolume)
LMJ_LINK(shader_volume osgManipulator)
target_link_libraries(shader_volume PUBLIC opengl32)

