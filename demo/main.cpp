
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgDB/ReadFile>
#include <iostream>

int main( int argc, char** argv )
{
	osgViewer::Viewer viewer;

	viewer.setUpViewInWindow(100, 100, 1024, 768);
	viewer.realize();

	viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);

	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(osgDB::readNodeFile("../OpenSceneGraphData/cow.osg"));
	viewer.setSceneData(root.get());
	viewer.run();

	return 0;
}
