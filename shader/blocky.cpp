
#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include <osg/Geode>
#include <osg/Vec3>
#include <osg/program>
#include <osg/Shader>
#include <osg/Uniform>

// callback for animating various uniforms(currently only the sin unfirom)
//
class AnimateCallback : public osg::Uniform::Callback
{
public:
	enum Operation 
	{
		SIN,
		COLOR1,
		COLOR2
	};
	AnimateCallback(Operation op) : operator_(op)
	{}
	virtual void operator()(osg::Uniform *uniform, osg::NodeVisitor *nv)
	{
		float angle = 2.0 * nv->getFrameStamp()->getSimulationTime();
		float sine = sinf(angle);
		switch(operator_)
		{
		case SIN:
			uniform->set(sine);
			break;
		case COLOR1:
			//uniform->set(osg::Vec3(1.0, 0.0, 0.0));
			break;
		case COLOR2:
			//uniform->set(osg::Vec3(0.0, 0.0, 1.0));
			break;
		}
	}
private:
	Operation operator_;
};

int main( int argc, char** argv )
{
    osgViewer::Viewer viewer;

    osg::Geode *basicModel = new osg::Geode;
    basicModel->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0f, 0.0f, 0.0f), 1.0f)));

    osg::StateSet *ss = basicModel->getOrCreateStateSet();
    osg::Program *program = new osg::Program;
    program->setName("blocky");
    program->addShader(osg::Shader::readShaderFile(osg::Shader::VERTEX, "../OpenSceneGraphData/shaders/blocky.vert"));
    program->addShader(osg::Shader::readShaderFile(osg::Shader::FRAGMENT, "../OpenSceneGraphData/shaders/blocky.frag"));
    ss->setAttributeAndModes(program, osg::StateAttribute::ON);

    // attach some animated uniform variable to the state set
    osg::Uniform *sineUniform = new osg::Uniform("Sine", 0.0f);
    ss->addUniform(sineUniform);
    sineUniform->setUpdateCallback(new AnimateCallback(AnimateCallback::SIN));
    osg::Uniform *color1 = new osg::Uniform("Color1", osg::Vec3(1.0, 0.0, 0.0));
    ss->addUniform(color1);
    osg::Uniform *color2 = new osg::Uniform("Color2", osg::Vec3(0.0, 0.0, 1.0));
    ss->addUniform(color2);

    // run
    viewer.setSceneData(basicModel);
    return viewer.run();
}

