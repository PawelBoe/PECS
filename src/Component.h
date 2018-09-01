//
// Created by Pawel Boening on 01.08.18.
//

#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H


#include <unordered_map>
#include <vector>
#include "ComponentBase.h"
#include "Entity.h"
#include "util/sparse_map.h"

namespace pecs
{

    template <typename T>
    class Component : public ComponentBase
    {
    public:
        ~Component() override = default;

        void create(Entity entity);

        bool exists(Entity entity) const;

        T& get(Entity entity);

        void remove(Entity entity);

        static ComponentId componentId();

    private:
        sparse_map<Entity, T, Entity::Hash> _data;
    };

    template<typename T>
    void Component<T>::create(Entity entity)
    {
        _data.add(entity, T());
    }

    template<typename T>
    bool Component<T>::exists(Entity entity) const
    {
        return  _data.search(entity) < _data.size();
    }

    template<typename T>
    T& Component<T>::get(Entity entity)
    {
        return _data.at(entity);
    }

    template<typename T>
    void Component<T>::remove(Entity entity)
    {
        _data.remove(entity);
    }

    template<typename T>
    ComponentBase::ComponentId Component<T>::componentId()
    {
        static ComponentId componentId = component_counter++;
        return componentId;
    }

}


#endif //ECS_COMPONENT_H
