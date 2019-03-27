#ifndef OBJECT_ACCESSOR_H
#define OBJECT_ACCESSOR_H

#include "object_accessor_imp.h"

template <typename T>
class ObjectAccessor
{
public:
    ObjectAccessor(std::shared_ptr<T> object, std::shared_ptr<IMsgQueue> object_queue)
    {
        imp_ = std::make_shared<ObjectAccessorImp>(typeid (T), object, object_queue);
    }

    ObjectAccessor(std::shared_ptr<ObjectAccessorImp> accessor_imp)
    {
        imp_ = accessor_imp;
    }

    ObjectAccessor()
    {}

    operator bool()
    {
        return imp_ != nullptr;
    }

    bool operator == (nullptr_t)
    {
        return imp_ == nullptr;
    }

    bool operator != (nullptr_t)
    {
        return imp_ != nullptr;
    }

    bool operator == (const ObjectAccessor<T> &other)
    {
        return imp_ == other.imp_;
    }

    bool operator != (const ObjectAccessor<T> &other)
    {
        return imp_ != other.imp_;
    }

    template<typename _DataType>
    void get(std::function<_DataType (std::shared_ptr<const T>)> object_action,
             std::function<void (const _DataType &)> client_action,
             std::shared_ptr<IMsgQueue> client_queue) const
    {
        imp_->get([=](std::shared_ptr<const void> object)
        {
            return object_action(std::reinterpret_pointer_cast<const T>(object));
        },
        [=](const std::any & data)
        {
            client_action(std::any_cast<_DataType>(data));
        },
        client_queue
        );
    }

    template<typename _DataType>
    _DataType get(std::function<_DataType (std::shared_ptr<const T>)> object_action) const
    {
        return std::any_cast<_DataType>(imp_->get([=](std::shared_ptr<const void> object)
        {
            return object_action(std::reinterpret_pointer_cast<const T>(object));
        }));
    }

    template<typename _DataType>
    void set(std::function<_DataType (std::shared_ptr<T>)> object_action,
             std::function<void (const _DataType &)> client_action,
             std::shared_ptr<IMsgQueue> client_queue)
    {
        imp_->set([=](std::shared_ptr<void> object)
        {
            return object_action(std::reinterpret_pointer_cast<T>(object));
        },
        [=](const std::any & data)
        {
            client_action(std::any_cast<_DataType>(data));
        },
        client_queue
        );
    }

    template<typename _DataType>
    _DataType set(std::function<_DataType (std::shared_ptr<T>)> object_action)
    {
        return std::any_cast<_DataType>(imp_->set([=](std::shared_ptr<void> obj){
            return object_action(std::reinterpret_pointer_cast<T>(obj));
        }));
    }

    void postGet(std::function<void (std::shared_ptr<const T>)> object_action) const
    {
        imp_->postGet([=](std::shared_ptr<const void> object){
            object_action(std::reinterpret_pointer_cast<const T>(object));
        });
    }

    void postSet(std::function<void (std::shared_ptr<T>)> object_action)
    {
        imp_->postSet([=](std::shared_ptr<void> obj){
            object_action(std::reinterpret_pointer_cast<T>(obj));
        });
    }

    template<typename _DataType>
    std::shared_ptr<void> bindObjectChangedNotifier(
                    const _DataType &init_data,
                    std::function<_DataType (std::shared_ptr<const T>)> object_action,
                    std::function<void (const _DataType &)> client_action,
                    std::shared_ptr<IMsgQueue> client_queue)
    {
        return
        imp_->bindObjectChangedNotifier(init_data,
        [](const std::any &data1, const std::any &data2)
        {
            return (std::any_cast<_DataType>(data1) == std::any_cast<_DataType>(data2));
        },
        [=](std::shared_ptr<const void> object)
        {
            return object_action(std::reinterpret_pointer_cast<const T>(object));
        },
        [=](const std::any &data)
        {
            client_action(std::any_cast<const _DataType &>(data));
        },
        client_queue
        );
    }

    template<typename _ChildObjType>
    void addChild(ObjectAccessor<_ChildObjType> child)
    {
        imp_->addChild(child.imp_);
    }

    template<typename _ChildObjType>
    void removeChild(ObjectAccessor<_ChildObjType> child)
    {
        imp_->removeChild(child.imp_);
    }

    template<typename _ChildObjType>
    std::list<ObjectAccessor<_ChildObjType>> children()
    {
        std::list<std::shared_ptr<ObjectAccessorImp>> imp_list =
        imp_->children([](std::shared_ptr<ObjectAccessorImp> child){
            return (child->type() == typeid (_ChildObjType));
        });

        std::list<ObjectAccessor<_ChildObjType>> child_list;
        std::copy(imp_list.begin(), imp_list.end(), std::back_inserter(child_list));
        return child_list;
    }

    template<typename _ChildObjType>
    ObjectAccessor<_ChildObjType> firstChild()
    {
        std::shared_ptr<ObjectAccessorImp> child =
        imp_->firstChild([](std::shared_ptr<ObjectAccessorImp> e){
            return (e->type() == typeid (_ChildObjType));
        });

        return ObjectAccessor<_ChildObjType>(child);
    }

    template<typename _ChildObjType>
    std::shared_ptr<void> bindChildChangedNotifier(
            std::function<void (ObjectAccessor<_ChildObjType>)> on_add,
            std::function<void (ObjectAccessor<_ChildObjType>)> on_remove,
            std::shared_ptr<IMsgQueue> client_queue
            )
    {
        return
        imp_->bindChildChangedNotifier(
        [=](std::shared_ptr<ObjectAccessorImp> child)
        {
            on_add(ObjectAccessor<_ChildObjType>(child));
        },

        [=](std::shared_ptr<ObjectAccessorImp> child)
        {
            on_remove(ObjectAccessor<_ChildObjType>(child));
        },

        client_queue
        );
    }

private:
    std::shared_ptr<ObjectAccessorImp> imp_;
};

#endif // OBJECT_ACCESSOR_H
