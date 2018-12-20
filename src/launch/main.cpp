#include <QApplication>
#include <QDir>

#include <cradle/cradle.h>
#include <vw/life.h>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    QStringList module_dirs;
    module_dirs << QDir(a.applicationDirPath()).absoluteFilePath("modules");
    Cradle::setModuleDir(module_dirs);
    Cradle::loadModules();

    dream::Life *life = new dream::Life;
    Cradle::addObject(life);

    QObject::connect(&a, &QApplication::aboutToQuit, [=](){
        Cradle::unloadModules();
        Cradle::removeObject(life);

        delete life;
    });

    return a.exec();
}
