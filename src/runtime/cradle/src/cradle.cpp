#include "cradle.h"

#include "i_launcher.h"
#include <QPluginLoader>
#include <QMap>
#include <QDir>
#include <QtDebug>

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
        QStringList name_filter;
        name_filter << "*.dll";
        for(QFileInfo &file_info : dir.entryInfoList(name_filter, QDir::Files)){
            QPluginLoader *loader = new QPluginLoader(file_info.absoluteFilePath());
            qDebug() << "loading... " << loader->fileName();
            if(loader->load()){
                loader->instance();
                g_cradle_data.loader_list[file_info.baseName()] = loader;
            }
            else {
                qDebug() << "failed: " << loader->errorString();
                Q_ASSERT(false);
                // TODO: report error
            }
        }
    }

    for(QPluginLoader *& loader : g_cradle_data.loader_list.values()){
        ILauncher *launcher = qobject_cast<ILauncher *>(loader->instance());
        if(launcher != nullptr){
            qDebug() << "launching... " << loader->fileName();
            launcher->start();
        }
    }
}

void Cradle::unloadModules()
{
    for(QPluginLoader *& loader : g_cradle_data.loader_list.values()){
        ILauncher *launcher = qobject_cast<ILauncher *>(loader->instance());
        if(launcher != nullptr){
            qDebug() << "stoping... " << loader->fileName();
            launcher->stop();
        }
    }

    for(QPluginLoader *& loader : g_cradle_data.loader_list.values()){
        qDebug() << "unloading... " << loader->fileName();
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
