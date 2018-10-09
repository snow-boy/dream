#include <cradle/cradle.h>
#include <QApplication>
#include <QDir>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    QStringList module_dirs;
    module_dirs << QDir(a.applicationDirPath()).absoluteFilePath("modules");
    Cradle::setModuleDir(module_dirs);
    Cradle::loadModules();

    QObject::connect(&a, &QApplication::aboutToQuit, [](){
        Cradle::unloadModules();
    });

    return a.exec();
}
