
#include <osg/Program>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

static const char *vertexCode = {
	"varying vec3 normal;\n"
	"void main()\n"
	"{\n"
	"	normal = normalize(gl_NormalMatrix * gl_Normal);\n"
	"	gl_Position = ftransform();\n"
	"}\n"
};
static const char *fragmentCode = {
	"uniform vec4 color1;\n"
	"uniform vec4 color2;\n"
	"uniform vec4 color3;\n"
	"uniform vec4 color4;\n"
	"varying vec3 normal;\n"
	"void main()\n"
	"{\n"
	"	float intensity = dot(vec3(gl_LightSource[0].position), normal);\n"
	"	if (intensity > 0.95)	gl_FragColor = color1;\n"
	"	else if (intensity > 0.5 )	gl_FragColor = color2;\n"
	"	else if (intensity > 0.25)	gl_FragColor = color3;\n"
	"	else	gl_FragColor = color4;\n"
	"}\n"
};

int main(int argc, char **argv)
{
	osg::ref_ptr<osg::Shader> vs = new osg::Shader(osg::Shader::VERTEX, vertexCode);
	osg::ref_ptr<osg::Shader> fs = new osg::Shader(osg::Shader::FRAGMENT, fragmentCode);
	osg::ref_ptr<osg::Program> program = new osg::Program;
	program->addShader(vs.get());
	program->addShader(fs.get());

	osg::ref_ptr<osg::Node> model = osgDB::readNodeFile("../OpenSceneGraphData/cow.osg");
	osg::StateSet *ss = model->getOrCreateStateSet();
	ss->setAttributeAndModes(program.get());
	ss->addUniform(new osg::Uniform("color1", osg::Vec4(1.0f, 0.5f, 0.5f, 1.0f)));
	ss->addUniform(new osg::Uniform("color2", osg::Vec4(0.5f, 0.2f, 0.2f, 1.0f)));
	ss->addUniform(new osg::Uniform("color3", osg::Vec4(0.2f, 0.1f, 0.1f, 1.0f)));
	ss->addUniform(new osg::Uniform("color4", osg::Vec4(0.1f, 0.05f, 0.05f, 1.0f)));

	osgViewer::Viewer viewer;
	viewer.setSceneData(model.get());
	return viewer.run();
}

