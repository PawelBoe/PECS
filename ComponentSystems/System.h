//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_COMPONENTSYSTEM_H
#define ECS_COMPONENTSYSTEM_H


#include <vector>
#include "SystemBase.h"

namespace pecs
{

    template <typename T>
    class System : public SystemBase
    {
    public:
        ~System() = default;

        template <typename ... Args>
        void assign(Entity entity, Args && ... args);

        void remove(Entity entity);
        void update(EntityManager &entities,
                    MessageManager &messages, float dt);

        static SystemId systemId();
    };

    template<typename T>
    template<typename... Args>
    void System<T>::assign(Entity entity, Args &&... args)
    {
        static_cast<T*>(this)->_assign(entity, std::forward<Args>(args) ...);
    }

    template<typename T>
    void System<T>::remove(Entity entity)
    {
        static_cast<T*>(this)->_remove(entity);
    }

    template<typename T>
    void System<T>::update(EntityManager &entities,
                           MessageManager &messages, float dt)
    {
        static_cast<T*>(this)->_update(entities, messages, dt);
    }

    template<typename T>
    SystemBase::SystemId System<T>::systemId()
    {
        static SystemId systemId = system_counter++;
        return systemId;
    }

}


#endif //ECS_COMPONENTSYSTEM_H
