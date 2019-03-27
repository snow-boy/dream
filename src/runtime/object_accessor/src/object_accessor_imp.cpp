#include "object_accessor_imp.h"
#include <assert.h>
#include <list>

namespace
{
struct ObjectNotifierData
{
    std::any data;
    std::function<bool (const std::any &, const std::any &)> equaler;
    std::function<std::any (const std::shared_ptr<void>)> object_action;
    std::function<void (const std::any &)> client_action;
    std::shared_ptr<IMsgQueue> client_queue;
};

struct ChildNotiferData
{
    std::function<void (std::shared_ptr<ObjectAccessorImp>)> on_add;
    std::function<void (std::shared_ptr<ObjectAccessorImp>)> on_remove;
    std::shared_ptr<IMsgQueue> client_queue;
};

}

class ObjectAccessorImp::PrivateData
{
public:
    PrivateData(const type_info &type):
        type_(type)
    {}

    void notifyObjectChanged()
    {
        auto on_object = [=](){
            for(auto &e: object_changed_notifiers_){
                notifyObjectChanged(e);
            }
        };

        object_queue_->queue(on_object);
    }

    // must call this function in object thread
    void notifyObjectChanged(std::shared_ptr<ObjectNotifierData> notifer_data)
    {
        std::shared_ptr<std::any> data = std::make_shared<std::any>(notifer_data->object_action(object_));
        if(!notifer_data->equaler(*data, notifer_data->data)){
            notifer_data->data = *data;
            notifer_data->client_queue->queue([=](){
                notifer_data->client_action(*data);
            });
        }
    }

    const type_info &type_;
    std::shared_ptr<void> object_;
    std::shared_ptr<IMsgQueue> object_queue_;

    std::list<std::shared_ptr<ObjectNotifierData>> object_changed_notifiers_;
    std::list<std::shared_ptr<ChildNotiferData>> child_changed_notifers_;
    std::list<std::shared_ptr<ObjectAccessorImp>> child_list_;
};

ObjectAccessorImp::ObjectAccessorImp(const type_info &type,
                                     std::shared_ptr<void> obj,
                                     std::shared_ptr<IMsgQueue> object_queue)
{
    assert(obj != nullptr);
    assert(object_queue != nullptr);

    data_ = std::make_unique<PrivateData>(type);
    data_->object_ = obj;
    data_->object_queue_ = object_queue;
}

ObjectAccessorImp::~ObjectAccessorImp()
{

}

const type_info &ObjectAccessorImp::type() const
{
    return data_->type_;
}

void ObjectAccessorImp::get(std::function<std::any (std::shared_ptr<const void>)> object_action,
                            std::function<void (const std::any &)> client_action,
                            std::shared_ptr<IMsgQueue> client_queue) const
{
    std::shared_ptr<std::any> data = std::make_shared<std::any>();
    auto on_client = [=](){
        client_action(*data);
    };

    auto on_object = [=](){
        *data = object_action(data_->object_);
        client_queue->queue(on_client);
    };

    data_->object_queue_->queue(on_object);
}

std::any ObjectAccessorImp::get(std::function<std::any (std::shared_ptr<const void>)> object_action) const
{
    std::any data;

    auto on_object = [&](){
        data = object_action(data_->object_);
    };

    data_->object_queue_->blockQueue(on_object);

    return data;
}

void ObjectAccessorImp::set(std::function<std::any (std::shared_ptr<void>)> object_action,
                            std::function<void (const std::any &)> client_action,
                            std::shared_ptr<IMsgQueue> client_queue)
{
    std::shared_ptr<std::any> data = std::make_shared<std::any>();
    auto on_client = [=](){
        client_action(*data);
    };

    auto on_object = [=](){
        *data = object_action(data_->object_);
        client_queue->queue(on_client);
    };

    data_->object_queue_->queue(on_object);
    data_->notifyObjectChanged();
}

std::any ObjectAccessorImp::set(std::function<std::any (std::shared_ptr<void>)> object_action)
{
    std::any data;

    auto on_object = [&](){
        data = object_action(data_->object_);
    };

    data_->object_queue_->blockQueue(on_object);
    data_->notifyObjectChanged();

    return data;
}

void ObjectAccessorImp::postGet(std::function<void (std::shared_ptr<const void>)> object_action) const
{
    auto on_object = [=](){
        object_action(data_->object_);
    };

    data_->object_queue_->queue(on_object);
}

void ObjectAccessorImp::postSet(std::function<void (const std::shared_ptr<void> )> object_action)
{
    auto on_object = [=](){
        object_action(data_->object_);
    };

    data_->object_queue_->queue(on_object);
    data_->notifyObjectChanged();
}

std::shared_ptr<void> ObjectAccessorImp::bindObjectChangedNotifier(const std::any &init_data,
                                  std::function<bool (const std::any &, const std::any &)> equaler,
                                  std::function<std::any (std::shared_ptr<const void>)> object_action,
                                  std::function<void (const std::any &)> client_action,
                                  std::shared_ptr<IMsgQueue> client_queue)
{
    assert(object_action != nullptr);
    assert(client_action != nullptr);
    assert(client_queue != nullptr);

    std::shared_ptr<ObjectNotifierData> notifer_data = std::make_shared<ObjectNotifierData>();
    notifer_data->data = init_data;
    notifer_data->equaler = equaler;
    notifer_data->object_action= object_action;
    notifer_data->client_action = client_action;
    notifer_data->client_queue = client_queue;

    if(equaler == nullptr){
        notifer_data->equaler = [](const std::any &, const std::any &){return false;};
    }

    auto on_object = [=](){
        data_->object_changed_notifiers_.push_back(notifer_data);
        data_->notifyObjectChanged(notifer_data);
    };
    data_->object_queue_->queue(on_object);

    return std::shared_ptr<void>(notifer_data.get(),
                                  [=](void *handle)
    {
        auto on_object = [=](){
            data_->object_changed_notifiers_.remove_if([=](std::shared_ptr<ObjectNotifierData> data){
                return data.get() == handle;
            });
        };
        data_->object_queue_->blockQueue(on_object);
    });
}

std::shared_ptr<void> ObjectAccessorImp::bindChildChangedNotifier(
        std::function<void (std::shared_ptr<ObjectAccessorImp>)> on_add,
        std::function<void (std::shared_ptr<ObjectAccessorImp>)> on_remove,
        std::shared_ptr<IMsgQueue> client_queue)
{
    assert(client_queue != nullptr);

    std::shared_ptr<ChildNotiferData> notifer_data = std::make_shared<ChildNotiferData>();
    notifer_data->on_add = on_add;
    notifer_data->on_remove = on_remove;
    notifer_data->client_queue = client_queue;

    data_->object_queue_->queue([=](){
        data_->child_changed_notifers_.push_back(notifer_data);
    });

    return std::shared_ptr<void>(notifer_data.get(), [=](void *handle)
    {
        data_->object_queue_->queue([=](){
            data_->child_changed_notifers_.remove_if([=](std::shared_ptr<ChildNotiferData> e){
                return (e.get() == handle);
            });
        });
    });
}

void ObjectAccessorImp::addChild(std::shared_ptr<ObjectAccessorImp> child)
{
    data_->object_queue_->queue([=](){
        data_->child_list_.push_back(child);
        for(auto &e: data_->child_changed_notifers_){
            if(e->on_add != nullptr){
                e->client_queue->queue([=](){
                    e->on_add(child);
                });
            }
        }
    });
}

void ObjectAccessorImp::removeChild(std::shared_ptr<ObjectAccessorImp> child)
{
    data_->object_queue_->queue([=](){
        data_->child_list_.remove(child);
        for(auto &e: data_->child_changed_notifers_){
            if(e->on_remove != nullptr){
                e->client_queue->queue([=](){
                    e->on_remove(child);
                });
            }
        }
    });
}

std::list<std::shared_ptr<ObjectAccessorImp> >
ObjectAccessorImp::children(std::function<bool (std::shared_ptr<ObjectAccessorImp>)> filter) const
{
    std::list<std::shared_ptr<ObjectAccessorImp> > child_list;

    data_->object_queue_->blockQueue([&](){
        for(auto e: data_->child_list_){
            if(filter(e)){
                child_list.push_back(e);
            }
        }
    });

    return child_list;
}

std::shared_ptr<ObjectAccessorImp> ObjectAccessorImp::firstChild(
        std::function<bool (std::shared_ptr<ObjectAccessorImp>)> filter) const
{
    std::shared_ptr<ObjectAccessorImp> first_child;

    data_->object_queue_->blockQueue([&](){
        for(auto e: data_->child_list_){
            if(filter(e)){
                first_child = e;
                return;
            }
        }
    });

    return first_child;
}


