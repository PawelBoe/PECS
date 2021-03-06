//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_ENTITYCOMPONENTSYSTEM_H
#define ECS_ENTITYCOMPONENTSYSTEM_H


#include <unordered_map>
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"
#include "ViewManager.h"

namespace pecs
{

    class EntityComponentSystem
    {
    public:
        EntityComponentSystem();

        template<typename T, typename ... Args>
        void assign_system(Args && ... args);

        template<typename T>
        void assign_component();

        template <typename T, typename ... Args>
        void update(Args &&... args);

    private:
        EntityManager _entities;
        ComponentManager _components;
        SystemManager _systems;
        ViewManager _views;

    protected:
        View<>& _data;
    };

    template<typename T, typename ... Args>
    void EntityComponentSystem::assign_system(Args && ... args)
    {
        _systems.assign<T>(std::forward<Args>(args) ...);
    }

    template<typename T>
    void EntityComponentSystem::assign_component()
    {
        _components.assign<T>();
    }

    template<typename T, typename ... Args>
    void EntityComponentSystem::update(Args &&... args)
    {
        _systems.update<T>(_views.get(T::signature), std::forward<Args>(args) ...);
    }

}


#endif //ECS_ENTITYCOMPONENTSYSTEM_H
