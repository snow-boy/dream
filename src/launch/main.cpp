#include <QApplication>
#include <QDir>

#include <cradle/cradle.h>
#include <vw/life.h>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    dream::Life *life = new dream::Life;
    dream::Scene *demo_scene = life->addScene("demo01");
    Cradle::addObject(life);

    QStringList module_dirs;
    module_dirs << QDir(a.applicationDirPath()).absoluteFilePath("modules");
    Cradle::setModuleDir(module_dirs);
    Cradle::loadModules();

    QObject::connect(&a, &QApplication::aboutToQuit, [=](){
        delete demo_scene;

        Cradle::unloadModules();
        Cradle::removeObject(life);

        delete life;
    });

    return a.exec();
}
