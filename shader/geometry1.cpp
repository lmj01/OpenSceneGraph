
#include <osg/Program>
#include <osg/Shader>
#include <osg/Texture2D>
#include <osg/Texture1D>
#include <osg/Image>
#include <osg/Geometry>
#include <osg/Material>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

void configureShaders(osg::StateSet *ss)
{
	osg::Program *program = new osg::Program;
	program->addShader(osg::Shader::readShaderFile(osg::Shader::VERTEX, "../lmjdata/shaders/geometry1.vert"));
	program->addShader(osg::Shader::readShaderFile(osg::Shader::GEOMETRY, "../lmjdata/shaders/geometry1.geom"));
	program->addShader(osg::Shader::readShaderFile(osg::Shader::FRAGMENT, "../lmjdata/shaders/geometry1.frag"));
	ss->setAttribute(program);
}

int main(int argc, char **argv)
{
	osgViewer::Viewer viewer;

	osg::ref_ptr<osg::Group> root = new osg::Group;
	osg::ref_ptr<osg::Vec3Array> vertexArray = new osg::Vec3Array;
	vertexArray->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	vertexArray->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
	vertexArray->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));

	osg::ref_ptr<osg::Vec4Array> colorArray = new osg::Vec4Array;
	colorArray->push_back(osg::Vec4(0.0, 1.0, 1.0, 1.0));
	colorArray->push_back(osg::Vec4(0.0, 0.0, 1.0, 1.0));
	colorArray->push_back(osg::Vec4(1.0, 1.0, 1.0, 1.0));

	osg::ref_ptr<osg::Vec3Array> normalArray = new osg::Vec3Array;
	normalArray->push_back(osg::Vec3(0.0, 1.0, 0.0));

	osg::ref_ptr<osg::Vec2Array> texArray = new osg::Vec2Array;
	texArray->push_back(osg::Vec2(0.0, 0.0));
	texArray->push_back(osg::Vec2(1.0, 0.0));
	texArray->push_back(osg::Vec2(1.0, 1.0));
	texArray->push_back(osg::Vec2(0.0, 1.0));

	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	geom->setVertexAttribArray(0, vertexArray);
	geom->setVertexAttribBinding(0, osg::Geometry::BIND_PER_VERTEX);
	
	geom->setVertexAttribArray(1, colorArray);
	geom->setVertexAttribBinding(1, osg::Geometry::BIND_PER_VERTEX);

	geom->setVertexAttribArray(2, normalArray);
	geom->setVertexAttribBinding(2, osg::Geometry::BIND_PER_VERTEX);

	geom->setVertexAttribArray(3, texArray);
	geom->setVertexAttribBinding(3, osg::Geometry::BIND_PER_VERTEX);

	osg::ref_ptr<osg::Image> img = osgDB::readImageFile("../OpenSceneGraphData/Images/forestWall.png");
	if (!img) {
		std::cout << "cannot open image file !" << std::endl;
	}

	osg::ref_ptr<osg::Texture2D> texture1 = new osg::Texture2D;
	texture1->setDataVariance(osg::Object::DYNAMIC);
	texture1->setImage(img.get());

	osg::StateSet *ss = geom->getOrCreateStateSet();
	ss->setTextureAttributeAndModes(0, texture1.get(), osg::StateAttribute::ON);
	ss->addUniform(new osg::Uniform("map1", 0));
	//ss->addUniform(new osg::Uniform("map2", 1));

	geom->addPrimitiveSet(new osg::DrawArrays(GL_TRIANGLES, 0, 3));
	configureShaders(ss);
	root->addChild(geom);

    	const int width( 800 ), height( 450 );
    	const std::string version( "3.1" );
    	osg::ref_ptr< osg::GraphicsContext::Traits > traits = new osg::GraphicsContext::Traits();
    	traits->x = 20; traits->y = 30;
    	traits->width = width; traits->height = height;
    	traits->windowDecoration = true;
    	traits->doubleBuffer = true;
    	traits->glContextVersion = version;
    	osg::ref_ptr< osg::GraphicsContext > gc = osg::GraphicsContext::createGraphicsContext( traits.get() );
    	if( !gc.valid() )
    	{
        	osg::notify( osg::FATAL ) << "Unable to create OpenGL v" << version << " context." << std::endl;
        	return( 1 );
    	}

    	// Create a Camera that uses the above OpenGL context.
	osg::Camera* cam = viewer.getCamera();
    	cam->setGraphicsContext( gc.get() );
    	// Must set perspective projection for fovy and aspect.
    	cam->setProjectionMatrix( osg::Matrix::perspective( 30., (double)width/(double)height, 1., 100. ) );
    	// Unlike OpenGL, OSG viewport does *not* default to window dimensions.
    	cam->setViewport( new osg::Viewport( 0, 0, width, height ) );

    	viewer.setSceneData( root );

    	// for non GL3/GL4 and non GLES2 platforms we need enable the osg_ uniforms that the shaders will use,
    	// you don't need thse two lines on GL3/GL4 and GLES2 specific builds as these will be enable by default.
    	gc->getState()->setUseModelViewAndProjectionUniforms(true);
    	gc->getState()->setUseVertexAttributeAliasing(true);

	return viewer.run();
}

