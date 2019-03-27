#ifndef OBJECT_ACCESSOR_IMP_H
#define OBJECT_ACCESSOR_IMP_H

#include <memory>
#include <any>
#include <list>

#include "i_msg_queue.h"
#include "object_accessor_global.h"

// this class used to manager thread and notifer of any object
class OBJECT_ACCESSOR_DECL ObjectAccessorImp
{
public:
    ObjectAccessorImp(const type_info &type,
                      std::shared_ptr<void> obj,
                      std::shared_ptr<IMsgQueue> object_queue);

    ~ObjectAccessorImp();

    const type_info &type() const;

    void get(std::function<std::any (std::shared_ptr<const void>)> object_action,
             std::function<void (const std::any &)> client_action,
             std::shared_ptr<IMsgQueue> client_queue) const;

    std::any get(std::function<std::any (std::shared_ptr<const void>)> object_action) const;

    void set(std::function<std::any (std::shared_ptr<void>)> object_action,
             std::function<void (const std::any &)> client_action,
             std::shared_ptr<IMsgQueue> client_queue);

    std::any set(std::function<std::any (std::shared_ptr<void>)> object_action);

    void postGet(std::function<void (std::shared_ptr<const void>)> object_action) const;

    void postSet(std::function<void (std::shared_ptr<void>)> object_action);

    std::shared_ptr<void> bindObjectChangedNotifier(
                    const std::any &init_data,
                    std::function<bool (const std::any &, const std::any &)> equaler,
                    std::function<std::any (std::shared_ptr<const void>)> object_action,
                    std::function<void (const std::any &)> client_action,
                    std::shared_ptr<IMsgQueue> client_queue);

    std::shared_ptr<void> bindChildChangedNotifier(
            std::function<void (std::shared_ptr<ObjectAccessorImp>)> on_add,
            std::function<void (std::shared_ptr<ObjectAccessorImp>)> on_remove,
            std::shared_ptr<IMsgQueue> client_queue
            );

    void addChild(std::shared_ptr<ObjectAccessorImp> child);

    void removeChild(std::shared_ptr<ObjectAccessorImp> child);

    std::list<std::shared_ptr<ObjectAccessorImp>>
    children(std::function<bool (std::shared_ptr<ObjectAccessorImp>)> filter = nullptr) const;

    std::shared_ptr<ObjectAccessorImp>
    firstChild(std::function<bool (std::shared_ptr<ObjectAccessorImp>)> filter = nullptr) const;

private:
    class PrivateData;
    std::unique_ptr<PrivateData> data_;
};

#endif // OBJECT_ACCESSOR_IMP_H
