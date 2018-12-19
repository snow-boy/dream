#ifndef ACTOR_H
#define ACTOR_H

#include <QObject>

class Actor : public QObject
{
    Q_OBJECT
public:
    explicit Actor(QObject *parent = nullptr);

public:
    virtual bool event(QEvent *e) override;

signals:

public slots:

};

#endif // ACTOR_H
