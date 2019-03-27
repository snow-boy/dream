#include <QCoreApplication>
#include <iostream>
#include <memory>

#include <QtDebug>
#include <QThread>

#include <object_accessor/object_accessor.h>
#include <object_accessor/qthread_queue.h>

class Tester
{
public:
    Tester(QThread *thread):
        thread_(thread),
        value_(0)
    {}

    QThread *thread() const
    {
        return thread_;
    }

    int get() const
    {
        Q_ASSERT(QThread::currentThread() == thread());
        qDebug() << "get: " << value_ << " in " << QThread::currentThread();
        return value_++;
    }

    int set(int value)
    {
        Q_ASSERT(QThread::currentThread() == thread());
        qDebug() << "set: " << value << " in " << QThread::currentThread();

        int current_value = value_;
        value_ = value;
        return current_value;
    }

private:
    QThread *thread_;
    mutable int value_;
};

ObjectAccessor<Tester> tester_accessor;

void test_init_state()
{
    Q_ASSERT(!tester_accessor);
    Q_ASSERT(tester_accessor == nullptr);
    Q_ASSERT(!(tester_accessor != nullptr));
}

void create_accessor()
{
//    QThread *thread = new QThread;
//    thread->start();
    QThread *thread = QThread::currentThread();
    tester_accessor =
    ObjectAccessor<Tester>(std::make_shared<Tester>(thread),
                           std::make_shared<QThreadQueue>(thread));
}

void test_get()
{
    tester_accessor.get<int>(
        [](std::shared_ptr<const Tester> t)
        {
            return t->get();
        },
        [](const int &data)
        {
            qDebug() << "get in client: " << data << " " << QThread::currentThread();
        },
        std::make_shared<QThreadQueue>(QThread::currentThread())
    );

    qDebug() << "direct get: " << tester_accessor.get<int>([](std::shared_ptr<const Tester> t)
    {
        return t->get();
    });

    tester_accessor.postGet([](std::shared_ptr<const Tester> t){
        qDebug() << "postGet: " << t->get() << " " << QThread::currentThread();
    });
}

void test_set()
{
    static int value_set = 100;
    tester_accessor.set<int>(
        [](std::shared_ptr<Tester> t)
        {
            value_set++;
            return t->set(value_set);
        },
        [](const int &data)
        {
            qDebug() << "set return: " << data;
        },
        std::make_shared<QThreadQueue>(QThread::currentThread())
    );

    tester_accessor.postSet([](std::shared_ptr<Tester> t){
        value_set++;
        qDebug() << "post set: " << t->set(value_set);
    });
}

std::shared_ptr<void> object_change_binder;
void bind_object_change_notifier()
{
    object_change_binder = tester_accessor.bindObjectChangedNotifier<int>(
        -1,
        [](std::shared_ptr<const Tester> t){
            return t->get();
        },
        [](const int& value){
            qDebug() << "on notifer" << value << QThread::currentThread();
        },
        std::make_shared<QThreadQueue>(QThread::currentThread())
        );
}

std::shared_ptr<void> child_change_binder;
void bind_child_change_notifer()
{
    child_change_binder =
    tester_accessor.bindChildChangedNotifier<Tester>(
                [](ObjectAccessor<Tester> child){
                    qDebug() << "on add child" << QThread::currentThread();
                },
                [](ObjectAccessor<Tester> child){
                    qDebug() << "on remove child" << QThread::currentThread();
                },
                std::make_shared<QThreadQueue>(QThread::currentThread())
                );
}

ObjectAccessor<Tester> g_child;
void add_child()
{
    g_child = ObjectAccessor<Tester>(std::make_shared<Tester>(QThread::currentThread()),
                                     std::make_shared<QThreadQueue>(QThread::currentThread()));
    tester_accessor.addChild(g_child);
}

void remove_child()
{
    tester_accessor.removeChild(g_child);
}

void find_child()
{
    Q_ASSERT(tester_accessor.children<Tester>().size() == 1);
    Q_ASSERT(tester_accessor.firstChild<Tester>() != nullptr);
}

int main(int argc, char **argv)
{
    QCoreApplication a(argc, argv);

    test_init_state();
    create_accessor();
//    test_get();
//    test_set();
//    test_get();
//    bind_object_change_notifier();
//    test_set();
//    test_get();
//    test_set();
    bind_child_change_notifer();
    add_child();
    child_change_binder = nullptr;
    a.processEvents();
    find_child();
    remove_child();

    return a.exec();
}


