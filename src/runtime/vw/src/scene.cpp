#include "scene.h"

namespace vw
{

class Scene::Imp
{
public:

};

Scene::Scene(QObject *parent):
    Entity (parent)
{
    imp_ = std::make_unique<Imp>();
}

Scene::~Scene()
{

}

}
