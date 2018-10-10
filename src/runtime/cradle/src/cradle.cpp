#include "cradle.h"

#include "i_launcher.h"
#include <QPluginLoader>
#include <QMap>
#include <QDir>

static struct
{
    QStringList module_dir_list;
    QMap<QString, QPluginLoader *> loader_list;

} g_cradle_data;


void Cradle::setModuleDir(const QStringList &dir_list)
{
    g_cradle_data.module_dir_list = dir_list;
}

void Cradle::loadModules()
{
    Q_ASSERT(g_cradle_data.loader_list.size() == 0);

    for(QString &dir_path : g_cradle_data.module_dir_list){
        QDir dir(dir_path);
        for(QFileInfo &file_info : dir.entryInfoList(QDir::Files)){
            QPluginLoader *loader = new QPluginLoader(file_info.absoluteDir().absoluteFilePath(file_info.baseName()));
            if(loader->load()){
                loader->instance();
                g_cradle_data.loader_list[file_info.baseName()] = loader;
            }
            else {
                Q_ASSERT(false);
                // TODO: report error
            }
        }
    }

    for(QPluginLoader *& loader : g_cradle_data.loader_list.values()){
        ILauncher *launcher = qobject_cast<ILauncher *>(loader->instance());
        if(launcher != nullptr){
            launcher->start();
        }
    }
}

void Cradle::unloadModules()
{
    for(QPluginLoader *& loader : g_cradle_data.loader_list.values()){
        ILauncher *launcher = qobject_cast<ILauncher *>(loader->instance());
        if(launcher != nullptr){
            launcher->stop();
        }
    }

    for(QPluginLoader *& loader : g_cradle_data.loader_list.values()){
        loader->unload();
        delete loader;
    }
    g_cradle_data.loader_list.clear();
}

QObject *Cradle::getModule(const QString &name)
{
    if(g_cradle_data.loader_list.contains(name)){
        return g_cradle_data.loader_list[name]->instance();
    }

    return nullptr;
}

QList<QObject *> Cradle::getModules(const QString &prefix)
{
    QList<QObject *> object_list;
    QStringList name_list = g_cradle_data.loader_list.keys();
    for(const QString &name : name_list){
        if(name.startsWith(prefix)){
            object_list.append(g_cradle_data.loader_list[name]->instance());
        }
    }

    return qMove(object_list);
}
