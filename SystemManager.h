//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_SYSTEMMANAGER_H
#define ECS_SYSTEMMANAGER_H


#include <unordered_map>
#include "System.h"
#include "EntityManager.h"
#include "ComponentManager.h"

namespace pecs
{

    class SystemManager
    {
    public:
        SystemManager();
        ~SystemManager();

        template <typename T, typename ... Args>
        void add(Args && ... args);

        template <typename T>
        void update(EntityManager &entities, ComponentManager &components, float dt);

    private:
        template <typename T>
        T* system();

        std::unordered_map<SystemBase::SystemId, SystemBase*> _systems;
    };

    template<typename T, typename... Args>
    void SystemManager::add(Args &&... args)
    {
        _systems[T::systemId()] = new T(std::forward<Args>(args) ...);
    }

    template<typename T>
    void SystemManager::update(EntityManager &entities, ComponentManager &components, float dt)
    {
        system<T>()->update(entities, components, dt);
    }

    template<typename T>
    T *SystemManager::system()
    {
        return (T*)(_systems[T::systemId()]);
    }
}


#endif //ECS_SYSTEMMANAGER_H
