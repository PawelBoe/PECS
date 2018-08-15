//
// Created by Pawel Boening on 01.08.18.
//

#ifndef ECS_COMPONENT_H
#define ECS_COMPONENT_H


#include <unordered_map>
#include <vector>
#include "ComponentBase.h"
#include "Entity.h"

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

        static ComponentId systemId();

    private:
        size_t _index_counter = 0;
        std::vector<T> _data;
        std::vector<size_t> _free_list;
        std::unordered_map<EntityId, size_t> _lookup;
    };

    template<typename T>
    void Component<T>::create(Entity entity)
    {
        size_t index;
        if (_free_list.empty()) {
            index = _index_counter++;
            _data.emplace_back();
        } else {
            index = _free_list.back();
            _free_list.pop_back();
        }

        _lookup[entity.id()] = index;
    }

    template<typename T>
    bool Component<T>::exists(Entity entity) const
    {
        return _lookup.find(entity.id()) != _lookup.end();
    }

    template<typename T>
    T& Component<T>::get(Entity entity)
    {
        return _data.at(_lookup.at(entity.id()));
    }

    template<typename T>
    void Component<T>::remove(Entity entity)
    {
        if (exists(entity)) {
            _free_list.push_back(_lookup.at(entity.id()));
            _lookup.erase(entity.id());
        }
    }

    template<typename T>
    ComponentBase::ComponentId Component<T>::systemId()
    {
        static ComponentId systemId = component_counter++;
        return systemId;
    }

}


#endif //ECS_COMPONENT_H
