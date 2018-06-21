//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_ENTITYCOMPONENTSYSTEM_H
#define ECS_ENTITYCOMPONENTSYSTEM_H


#include <unordered_map>
#include "EntityManager.h"
#include "MessageManager.h"
#include "ComponentManager.h"

namespace pecs
{

    class EntityComponentSystem
    {
    public:
        Entity create_entity();
        bool exists_entity(Entity entity);
        void delete_entity(Entity entity);

        template <typename T>
        void create_component(Entity entity);
        template <typename T>
        T* get_component(Entity entity);
        template <typename T>
        void delete_component(Entity entity);

        void update();

    private:
        EntityManager _entityManager;
        MessageManager _messageManager;
        ComponentManager _componentManager;
    };

    template<typename T>
    void EntityComponentSystem::create_component(Entity entity)
    {
        _componentManager.create_component<T>(entity);
    }

    template<typename T>
    T* EntityComponentSystem::get_component(Entity entity)
    {
        return _componentManager.template get_component<T>(entity);
    }

    template<typename T>
    void EntityComponentSystem::delete_component(Entity entity)
    {
        _componentManager.delete_component<T>(entity);
    }

}


#endif //ECS_ENTITYCOMPONENTSYSTEM_H
