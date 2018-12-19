#ifndef SAFERUNEVENT_H
#define SAFERUNEVENT_H

#include <QEvent>
#include <functional>

class SafeRunEvent: public QEvent
{
public:
    SafeRunEvent(const std::function<void ()> &runner);

    static Type eventType();

    void run()
    {
        runner_();
    }

private:
    std::function<void ()> runner_;
};

#endif // SAFERUNEVENT_H
