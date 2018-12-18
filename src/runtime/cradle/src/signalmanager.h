#ifndef SIGNALMANAGER_H
#define SIGNALMANAGER_H

#include <QObject>
#include <string>
#include <QMap>
#include <QList>
#include <QSharedPointer>

class SignalManager
{
public:
    struct SignalContext
    {
        QObject *signaler;
        QMap<std::string, std::string> signal_alias;
    };
    typedef QSharedPointer<SignalContext> SignalContextPtr;

    struct SlotContext
    {
        QObject *sloter;
        std::string signal;
        std::string slot;
    };
    typedef QSharedPointer<SlotContext> SlotContextPtr;

    struct ConnectionContext
    {
        SignalContextPtr signal_context;
        SlotContextPtr slot_context;
        std::string signal;
        std::string slot;
    };
    typedef QSharedPointer<ConnectionContext> ConnectionContextPtr;

    SignalManager();
    ~SignalManager();

    // signal -> connection, signal -> signal_alias
    // slot -> connection
    // slot context, signal -> slot context,
    // signal context, signal -> signal context
    // connection context, slot context -> connection context, signal context -> connection context

    void registerSignaler(QObject *signaler);
    void unregisterSignaler(QObject *signaler);
    void installSignalAlias(QObject *signaler, const char *signal, const char *alias);

    void registerSloter(QObject *sloter, const char *signal, const char *slot);
    void unregisterSloter(QObject *sloter, const char *signal, const char *slot);
    void unregisterSloter(QObject *sloter);

private:
    SignalContextPtr findSignalContext(QObject *signaler);
    SlotContextPtr findSlotContext(QObject *sloter, const char *signal, const char *slot);
    void makeConnection(SignalContextPtr signaler,
                        SlotContextPtr sloter);

    QList<SignalContextPtr> signaler_list_;
    QList<SlotContextPtr> sloter_list_;
    QMap<SignalContextPtr, QList<ConnectionContextPtr>> signaler_connection_;
    QMap<SlotContextPtr, QList<ConnectionContextPtr>> sloter_connection_;
};

#endif // SIGNALMANAGER_H
