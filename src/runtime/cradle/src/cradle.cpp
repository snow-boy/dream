#include "cradle.h"

#include "i_launcher.h"
#include <QPluginLoader>
#include <QMap>
#include <QDir>
#include <QList>
#include <QCoreApplication>
#include <QtDebug>
#include <QMutex>
#include <QMutexLocker>
#include <QVector>
#include "signalmanager.h"
#include "objectmanager.h"

static struct CradleData
{
    CradleData()
    {
        signal_manager.registerSignaler(&object_manager);
    }

    ~CradleData()
    {
        signal_manager.unregisterSignaler(&object_manager);
    }

    QStringList module_dir_list;
    QMap<QString, QPluginLoader *> loader_list;
    SignalManager signal_manager;
    ObjectManager object_manager;

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

void Cradle::addObject(QObject *obj)
{
    g_cradle_data.object_manager.addObject(obj);
}

void Cradle::removeObject(QObject *obj)
{
    g_cradle_data.object_manager.removeObject(obj);
}

void Cradle::registerSignaler(QObject *signaler)
{
    g_cradle_data.signal_manager.registerSignaler(signaler);
}

void Cradle::unregisterSignaler(QObject *signaler)
{
    g_cradle_data.signal_manager.unregisterSignaler(signaler);
}

void Cradle::installSignalAlias(QObject *signaler, const char *signal, const char *alias)
{
    g_cradle_data.signal_manager.installSignalAlias(signaler, signal, alias);
}

void Cradle::registerSloter(QObject *sloter, const char *signal, const char *slot)
{
    g_cradle_data.signal_manager.registerSloter(sloter, signal, slot);
}

void Cradle::unregisterSloter(QObject *sloter, const char *signal, const char *slot)
{
    g_cradle_data.signal_manager.unregisterSloter(sloter, signal, slot);
}

void Cradle::unregisterSloter(QObject *sloter)
{
    g_cradle_data.signal_manager.unregisterSloter(sloter);
}

QList<QObject *> Cradle::findObjectsByName(const QString &name)
{
    return g_cradle_data.object_manager.findObjects(name);
}
