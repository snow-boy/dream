#ifndef TACTORIMP_H
#define TACTORIMP_H

#include <QObject>
#include <functional>
#include <QMutex>
#include <QMap>
#include <QThread>

Q_DECLARE_METATYPE(std::function<void ()>)
class TActorImp : public QObject
{
    Q_OBJECT
public:
    explicit TActorImp(QObject *parent = nullptr);

signals:
    void postCmd(std::function<void ()> cmd);
    void sendCmd(std::function<void ()> cmd);

private slots:
    void doCmd(std::function<void ()> cmd);
};


class TActorManager: public QObject
{
    Q_OBJECT
public:
    std::shared_ptr<TActorImp> getActor(QThread *thread);

public slots:
    void onThreadDestoryed(QObject *obj);

private:
    QMap<QThread *, std::shared_ptr<TActorImp>> thread_actor_map_;
    QMutex mutex_;
};

#endif // TACTORIMP_H
