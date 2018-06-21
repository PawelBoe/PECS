//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_COMPONENTMANAGER_H
#define ECS_COMPONENTMANAGER_H


#include <unordered_map>
#include "ComponentSystems/ComponentSystem.h"

namespace pecs
{

    class ComponentManager
    {
    public:
        ComponentManager();
        ~ComponentManager();

        template <typename T>
        void create_component(Entity entity);
        template <typename T>
        T* get_component(Entity entity);
        template <typename T>
        void delete_component(Entity entity);

    private:
        std::unordered_map<ComponentId, ComponentSystemBase*> _componentSystems;
    };

    template<typename T>
    void ComponentManager::create_component(Entity entity)
    {
        _componentSystems[T::id]->create_component(entity);
    }

    template<typename T>
    T* ComponentManager::get_component(Entity entity)
    {
        return _componentSystems[T::id]->template get_component<T>(entity);
    }

    template<typename T>
    void ComponentManager::delete_component(Entity entity)
    {
        _componentSystems[T::id]->delete_component(entity);
    }

}


#endif //ECS_COMPONENTMANAGER_H
