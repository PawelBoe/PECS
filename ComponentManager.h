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
        bool exists(Entity entity) const;

        template <typename T>
        T& get(Entity entity);

        template <typename T>
        void remove(Entity entity);

    private:
        template <typename T>
        Component<T>* component();
        template <typename T>
        const Component<T>* component() const;

        std::unordered_map<ComponentBase::ComponentId, ComponentBase*> _components;
    };

    template<typename T>
    void ComponentManager::add()
    {
        if (_components.find(Component<T>::componentId()) == _components.end())
            _components[Component<T>::componentId()] = new Component<T>;
    }

    template<typename T>
    bool ComponentManager::exists(Entity entity) const
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
        return (Component<T>*)(_components.at(Component<T>::componentId()));
    }

    template<typename T>
    const Component<T>* ComponentManager::component() const
    {
        return (Component<T>*)(_components.at(Component<T>::componentId()));
    }

}


#endif //ECS_COMPONENTMANAGER_H
