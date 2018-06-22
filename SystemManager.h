//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_COMPONENTMANAGER_H
#define ECS_COMPONENTMANAGER_H


#include <unordered_map>
#include "ComponentSystems/System.h"
#include "EntityManager.h"
#include "MessageManager.h"

namespace pecs
{

    class SystemManager
    {
    public:
        SystemManager(EntityManager &entity_manager, MessageManager &message_manager);
        ~SystemManager();

        template <typename T, typename ... Args>
        void add(Args && ... args);

        template <typename T>
        T* system();

        template <typename T, typename ... Args>
        void assign(Entity entity, Args && ... args);

        template <typename T>
        void remove(Entity entity);

        template <typename T>
        void update(float dt);

    private:
        EntityManager &_entities;
        MessageManager &_messages;
        std::unordered_map<SystemBase::SystemId, SystemBase*> _systems;
    };

    template<typename T, typename... Args>
    void SystemManager::add(Args &&... args)
    {
        _systems[T::systemId()] = new T(std::forward<Args>(args) ...);
    }

    template<typename T>
    T *SystemManager::system()
    {
        return (T*)(_systems[T::systemId()]);
    }

    template<typename T, typename... Args>
    void SystemManager::assign(Entity entity, Args &&... args)
    {
        system<T>()->assign(entity, std::forward<Args>(args) ...);
    }

    template<typename T>
    void SystemManager::remove(Entity entity)
    {
        system<T>()->remove(entity);
    }

    template<typename T>
    void SystemManager::update(float dt)
    {
        system<T>()->update(_entities, _messages, dt);
    }

}


#endif //ECS_COMPONENTMANAGER_H
