
#include <osgViewer/Viewer>

osg::ref_ptr<osg::Geometry> getGeometry()
{
	osg::ref_ptr<osg::Geometry> gm = new osg::Geometry;

	//
       osg::Vec3Array *vertexArray = new osg::Vec3Array;
       vertexArray->push_back(osg::Vec3(-1.0,-1.0, 0.0));	
       vertexArray->push_back(osg::Vec3( 1.0,-1.0, 0.0));	
       vertexArray->push_back(osg::Vec3(-1.0, 1.0, 0.0));	
       vertexArray->push_back(osg::Vec3(-1.0,-1.0, 0.0));	

       gm->setVertexAttribArray(0, vertexArray);
       gm->setVertexAttribBinding(0, osg::Geometry::BIND_PER_VERTEX);

       osg::Vec4Array *colorArray = new osg::Vec4Array;
       colorArray->push_back(osg::Vec4(1.0, 1.0, 1.0, 1.0));
       colorArray->push_back(osg::Vec4(1.0, 1.0, 0.0, 1.0));
       colorArray->push_back(osg::Vec4(1.0, 0.0, 1.0, 1.0));
       colorArray->push_back(osg::Vec4(0.0, 1.0, 1.0, 1.0));
       gm->setVertexAttribArray(1, colorArray);
       gm->setVertexAttribBinding(1, osg::Geometry::BIND_PER_VERTEX);

       gm->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, 3));

       osg::Program *program = new osg::Program;
       program->addShader(osg::Shader::readShaderFile(osg::Shader::VERTEX, "../OpenSceneGraphData/oglpg8/ch03_primitive_restart.vs.glsl"));
       program->addShader(osg::Shader::readShaderFile(osg::Shader::FRAGMENT, "../OpenSceneGraphData/oglpg8/ch03_primitive_restart.fs.glsl"));
       gm->getOrCreateStateSet()->setAttributeAndModes(program, osg::StateAttribute::ON | osg::StateAttribute::PROTECTED);

	return gm;
}

int main( int argc, char **argv )
{
	osg::ref_ptr<osg::Group> root = new osg::Group;
	root->addChild(getGeometry());

	const int width(800), height(600);
	const std::string version("3.1");
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits();
	traits->x = 100;
	traits->y = 100;
	traits->width = width;
	traits->height = height;
	traits->windowDecoration = true;
	traits->doubleBuffer = true;
	traits->glContextVersion = version;
	osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
       if (!gc.valid()) {
      		osg::notify(osg::FATAL) << "unable to create OpenGL v" << version << " context." << std::endl;
 		return 1;
       }

	osgViewer::Viewer viewer;
	osg::Camera *camera = viewer.getCamera();
	camera->setGraphicsContext(gc.get());
	camera->setProjectionMatrix(osg::Matrix::perspective(30.0, (double)width/(double)height, 1.0, 1000.0));
	camera->setViewport(new osg::Viewport(0, 0, width, height));

	
	viewer.setSceneData(root);
    	return viewer.run();
}
