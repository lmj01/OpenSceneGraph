
#include <osgViewer/Viewer>

osg::ref_ptr<osg::Geometry> getGeometry()
{
	osg::ref_ptr<osg::Geometry> gm = new osg::Geometry;

	//
	osg::Vec3Array *vertexArray = new osg::Vec3Array;
       vertexArray->push_back(osg::Vec3(-0.90,-0.90, 0.0));	
       vertexArray->push_back(osg::Vec3( 0.85,-0.90, 0.0));	
       vertexArray->push_back(osg::Vec3(-0.90, 0.85, 0.0));	
       vertexArray->push_back(osg::Vec3( 0.90,-0.85, 0.0));	
       vertexArray->push_back(osg::Vec3( 0.90, 0.90, 0.0));	
       vertexArray->push_back(osg::Vec3(-0.85, 0.90, 0.0));	

       gm->setVertexAttribArray(0, vertexArray);
       gm->setVertexAttribBinding(0, osg::Geometry::BIND_PER_VERTEX);

       gm->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::Mode::TRIANGLES, 0, vertexArray->size()));

       osg::Program *program = new osg::Program;
       program->addShader(osg::Shader::readShaderFile(osg::Shader::VERTEX, "../OpenSceneGraphData/oglpg8/vtest.glsl"));
       program->addShader(osg::Shader::readShaderFile(osg::Shader::FRAGMENT, "../OpenSceneGraphData/oglpg8/ftest.glsl"));
       gm->getOrCreateStateSet()->setAttributeAndModes(program, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);

	return gm;
}

int main( int argc, char **argv )
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;

	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(getGeometry());
	
	viewer->setSceneData(root);
    	return viewer->run();
}
