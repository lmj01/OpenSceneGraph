
// for 4.3 opengl
//

#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osg/Shape>
#include <osg/Shapedrawable>
#include <osg/MatrixTransform>
#include <osg/Texture2D>

static char* vertexShader = {
	"#version 430 \n"
	"layout (location=0) in vec3 VertexPosition;\n"
	"layout (location=1) in vec2 TexCoord;\n"
	"uniform mat4 MVP;\n"
	"out vec2 coord;\n"
	"void main()\n"
	"{\n"
	"  coord = TexCoord;\n"
	"  gl_Position = MVP * vec4(VertexPosition,1.0);\n"
	"}\n"
};
static char* fragShader = {
	"#version 430 \n"
	"uniform sampler2D map0;\n"
	"uniform sampler2D map1;\n"
	"layout (location=0) out vec4 FragColor;\n"
	"in vec2 coord;\n"
	"void main()\n"
	"{\n"
	"  vec4 tmp = texture(map0, coord);\n"
	"  if (coord[1] > 0.5)\n"
	"     tmp = texture(map1, coord);\n"
	"  FragColor = tmp;\n"
	"}\n"
};

class MVPCallback : public osg::Uniform::Callback
{
public:
	MVPCallback(osg::Camera *camera) : camera_(camera)
	{}
	virtual void operator()(osg::Uniform *uniform, osg::NodeVisitor *nv) {
		osg::Matrix modelView = camera_->getViewMatrix();
		osg::Matrix projectM = camera_->getProjectionMatrix();
		uniform->set(modelView * projectM);
	}
private:
	osg::Camera *camera_;
};

osg::Node* createNode() 
{
	osg::Geode *geode = new osg::Geode;
	osg::Geometry *gm = new osg::Geometry;

	osg::Vec3Array *vertexArray = new osg::Vec3Array;
	vertexArray->push_back(osg::Vec3(0,0,0));
	vertexArray->push_back(osg::Vec3(1,0,0));
	vertexArray->push_back(osg::Vec3(1,0,1));
	vertexArray->push_back(osg::Vec3(0,0,1));
	//gm->setVertexArray(vertexArray);
	gm->setVertexAttribArray(0, vertexArray);
	gm->setVertexAttribBinding(0, osg::Geometry::BIND_PER_VERTEX);

	osg::Vec3Array *normalArray = new osg::Vec3Array;
	normalArray->push_back(osg::Vec3(0,-1,0));
	gm->setNormalArray(normalArray);
	gm->setNormalBinding(osg::Geometry::BIND_OVERALL);

	osg::Vec2Array *texCoords = new osg::Vec2Array(4);
	// ccw 
	(*texCoords)[0].set(0.0f, 0.0f);
	(*texCoords)[1].set(1.0f, 0.0f);
	(*texCoords)[2].set(1.0f, 1.0f);
	(*texCoords)[3].set(0.0f, 1.0f);
	//gm->setTexCoordArray(0, texCoords);
	gm->setVertexAttribArray(1, texCoords);
	gm->setVertexAttribBinding(1, osg::Geometry::BIND_PER_VERTEX);

	gm->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, vertexArray->size()));
	geode->addDrawable(gm);

	// state 
	osg::StateSet *stateset = gm->getOrCreateStateSet();
	
	osg::Texture2D *tex0 = new osg::Texture2D;
	tex0->setDataVariance(osg::Object::DYNAMIC);
	tex0->setImage(osgDB::readImageFile("../OpenSceneGraphData/Images/forestWall.png"));
	stateset->setTextureAttributeAndModes(0, tex0, osg::StateAttribute::ON);

	osg::Texture2D *tex1 = new osg::Texture2D;
	tex1->setDataVariance(osg::Object::DYNAMIC);
	tex1->setImage(osgDB::readImageFile("../OpenSceneGraphData/Images/purpleFlowers.png"));
	stateset->setTextureAttributeAndModes(1, tex1, osg::StateAttribute::ON);

	//gm->setVertexAttribArray(0, vertexArray);
	//gm->setVertexAttribBinding(0, osg::Geometry::BIND_PER_VERTEX);

	//gm->setVertexAttribArray(1, texCoords);
	//gm->setVertexAttribBinding(1, osg::Geometry::BIND_PER_VERTEX);
	
	return geode;
}
int main(int argc, char*argv[])
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;

	osg::Group *root = new osg::Group;
	osg::Node *node = createNode();
	root->addChild(node);

	osg::StateSet *ss = node->getOrCreateStateSet();
	osg::Program *program = new osg::Program;
	program->addBindFragDataLocation("VertexPosition", 0);
	program->addBindFragDataLocation("TexCoord", 1);

	osg::Shader *vs = new osg::Shader(osg::Shader::VERTEX, vertexShader);
	osg::Shader *fs = new osg::Shader(osg::Shader::FRAGMENT, fragShader);
	
	osg::Uniform *MVPUniform = new osg::Uniform("MVP", osg::Matrixf());
	MVPUniform->setUpdateCallback(new MVPCallback(viewer->getCamera()));
	ss->addUniform(MVPUniform);

	osg::Uniform *sample0 = new osg::Uniform("map0", 0);
	ss->addUniform(sample0);
	osg::Uniform *sample1 = new osg::Uniform("map1", 1);
	ss->addUniform(sample1);

	program->addShader(vs);
	program->addShader(fs);
	ss->setAttributeAndModes(program, osg::StateAttribute::ON);

	viewer->setSceneData(root);
	viewer->setUpViewInWindow(100, 100, 1024, 800);

	return viewer->run();
}

