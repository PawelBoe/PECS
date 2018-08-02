//
// Created by Pawel Boening on 01.08.18.
//

#ifndef ECS_COMPONENTMANAGER_H
#define ECS_COMPONENTMANAGER_H


#include <unordered_map>
#include "EntityManager.h"
#include "Component.h"

namespace pecs
{

    class ComponentManager
    {
    public:
        ComponentManager();
        ~ComponentManager();

        template <typename T>
        void add();

        template <typename T>
        void create(Entity entity);

        template <typename T>
        bool exists(Entity entity);

        template <typename T>
        T& get(Entity entity);

        template <typename T>
        void remove(Entity entity);

    private:
        template <typename T>
        Component<T>* component();

        std::unordered_map<ComponentBase::ComponentId, ComponentBase*> _components;
    };

    template<typename T>
    void ComponentManager::add()
    {
        _components[Component<T>::systemId()] = new Component<T>;
    }

    template<typename T>
    bool ComponentManager::exists(Entity entity)
    {
        return component<T>()->exists(entity);
    }

    template<typename T>
    T& ComponentManager::get(Entity entity)
    {
        return component<T>()->get(entity);
    }

    template<typename T>
    void ComponentManager::create(Entity entity)
    {
        component<T>()->create(entity);
    }

    template<typename T>
    void ComponentManager::remove(Entity entity)
    {
        component<T>()->remove(entity);
    }

    template<typename T>
    Component<T>* ComponentManager::component()
    {
        return (Component<T>*)(_components[Component<T>::systemId()]);
    }

}


#endif //ECS_COMPONENTMANAGER_H
