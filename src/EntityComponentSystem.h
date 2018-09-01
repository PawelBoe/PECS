//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_ENTITYCOMPONENTSYSTEM_H
#define ECS_ENTITYCOMPONENTSYSTEM_H


#include <unordered_map>
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

namespace pecs
{

    class EntityComponentSystem
    {
    public:
        EntityComponentSystem();

        template <typename T>
        void update(float dt);

    protected:
        EntityManager _entities;
        ComponentManager _components;
        SystemManager _systems;
    };

    template<typename T>
    void EntityComponentSystem::update(float dt)
    {
        _systems.update<T>(_entities, _components, dt);
    }

}


#endif //ECS_ENTITYCOMPONENTSYSTEM_H
