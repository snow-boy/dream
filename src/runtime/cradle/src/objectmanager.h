#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <QObject>
#include <QList>
#include <QMap>
#include <QString>

class ObjectManager : public QObject
{
    Q_OBJECT
public:
    explicit ObjectManager(QObject *parent = nullptr);

    void addObject(QObject *obj);
    void removeObject(QObject *obj);

    QList<QObject *> findObjects(const QString &name);

signals:
    void objectAdded(QObject *);
    void objectRemoved(QObject *);

public slots:
    void onObjectNameChanged(const QString &name);

private:
    QList<QObject *> object_list_;
    QMap<QString, QList<QObject *>> name_object_list_;
};

#endif // OBJECTMANAGER_H
