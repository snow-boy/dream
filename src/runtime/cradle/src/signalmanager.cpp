#include "signalmanager.h"

SignalManager::SignalManager()
{

}

SignalManager::~SignalManager()
{

}

void SignalManager::registerSignaler(QObject *signaler)
{
    Q_ASSERT(findSignalContext(signaler) == nullptr);
    SignalContextPtr signal_context = SignalContextPtr::create();
    signal_context->signaler = signaler;
    signaler_list_.append(signal_context);

    for(SlotContextPtr e: sloter_list_){
        if(signaler->metaObject()->indexOfSignal(
                    QMetaObject::normalizedSignature(e->signal.data() + 1)) >= 0)
        {
            makeConnection(signal_context, e);
        }
    }
}

void SignalManager::unregisterSignaler(QObject *signaler)
{
    SignalContextPtr signal_context = findSignalContext(signaler);
    Q_ASSERT(signal_context != nullptr);
    signaler_list_.removeOne(signal_context);
    QList<ConnectionContextPtr> connection_list = signaler_connection_[signal_context];
    for(ConnectionContextPtr e: connection_list){
        sloter_connection_[e->slot_context].removeOne(e);
        QObject::disconnect(e->signal_context->signaler, e->signal.data(), e->slot_context->sloter, e->slot.data());
    }
    signaler_connection_.remove(signal_context);
}

void SignalManager::installSignalAlias(QObject *signaler, const char *signal, const char *alias)
{
    SignalContextPtr signal_context = findSignalContext(signaler);
    Q_ASSERT(signal_context != nullptr);
    signal_context->signal_alias[alias] = signal;

    for(SlotContextPtr e: sloter_list_){
        if(e->signal == alias){
            makeConnection(signal_context, e);
        }
    }
}

void SignalManager::registerSloter(QObject *sloter, const char *signal, const char *slot)
{
    Q_ASSERT(findSlotContext(sloter, signal, slot) == nullptr);
    SlotContextPtr slot_context = SlotContextPtr::create();
    slot_context->sloter = sloter;
    slot_context->signal = signal;
    slot_context->slot = slot;
    sloter_list_.append(slot_context);

    for(SignalContextPtr e: signaler_list_){
        if((e->signaler->metaObject()->indexOfSignal(QMetaObject::normalizedSignature(signal+1)) >= 0) ||
           (e->signal_alias.contains(signal) &&
                (e->signaler->metaObject()->indexOfSignal(
                     QMetaObject::normalizedSignature(e->signal_alias[signal].data() + 1)) >= 0)))
        {
            makeConnection(e, slot_context);
        }
    }
}

void SignalManager::unregisterSloter(QObject *sloter, const char *signal, const char *slot)
{
    SlotContextPtr slot_context = findSlotContext(sloter, signal, slot);
    Q_ASSERT(slot_context != nullptr);
    QList<ConnectionContextPtr> connection_list = sloter_connection_[slot_context];
    for(ConnectionContextPtr e: connection_list){
        signaler_connection_[e->signal_context].removeOne(e);
        QObject::disconnect(e->signal_context->signaler, e->signal.data(), e->slot_context->sloter, e->slot.data());
    }
    sloter_connection_.remove(slot_context);
}

SignalManager::SignalContextPtr SignalManager::findSignalContext(QObject *signaler)
{
    SignalContextPtr context;

    for(SignalContextPtr e: signaler_list_){
        if(e->signaler == signaler){
            context = e;
            break;
        }
    }

    return context;
}

SignalManager::SlotContextPtr SignalManager::findSlotContext(QObject *sloter, const char *signal, const char *slot)
{
    SlotContextPtr context;

    for(SlotContextPtr e: sloter_list_){
        if((e->sloter == sloter) && (e->signal == signal) && (e->slot == slot)){
            context = e;
            break;
        }
    }

    return context;
}

void SignalManager::makeConnection(SignalManager::SignalContextPtr signaler,
                                   SignalManager::SlotContextPtr sloter)
{
    QObject::connect(signaler->signaler, sloter->signal.data(), sloter->sloter, sloter->slot.data());
    ConnectionContextPtr connection_context = ConnectionContextPtr::create();
    connection_context->signal_context = signaler;
    connection_context->slot_context = sloter;
    connection_context->signal = sloter->signal;
    connection_context->slot = sloter->slot;
    signaler_connection_[signaler].append(connection_context);
    sloter_connection_[sloter].append(connection_context);
}
