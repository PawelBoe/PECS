//
// Created by Pawel Boening on 31.08.18.
//

#ifndef ECS_VIEW_H
#define ECS_VIEW_H


#include "ViewBase.h"
#include "util/TypeId.h"
#include "util/sparse_set.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "Signature.h"

namespace pecs
{

    template <typename ... Ts>
    class View : public ViewBase
    {
    public:
        View(EntityManager &entities, ComponentManager &components, Signature<Ts...> signature, std::unordered_map<TypeId_t, ViewBase*> &views);

        Entity create();
        void remove(Entity entity);

        template <typename T>
        void add(Entity entity);
        template <typename T>
        void remove(Entity entity);
        template <typename T>
        T& get(Entity entity);

        using iterator = Entity*;
        const iterator begin() const;
        const iterator end() const;

        void update(Entity entity) override;

    private:
        void _dirty(Entity entity);

        EntityManager &_entities;
        ComponentManager &_components;
        Signature<Ts...> _signature;
        std::unordered_map<TypeId_t, ViewBase*> &_views;
        sparse_set<Entity, Entity::Hash> _view_entities;
    };

    template<typename... Ts>
    View<Ts...>::View(EntityManager &entities, ComponentManager &components,
                      Signature<Ts...> signature,
                      std::unordered_map<TypeId_t, ViewBase *> &views)
            : _entities(entities), _components(components), _signature(signature), _views(views)
    {
        for (auto e : entities) {
            update(e);
        }
    }

    template<typename... Ts>
    Entity View<Ts...>::create()
    {
        Entity entity = _entities.create();
        _dirty(entity);
        return entity;
    }

    template<typename... Ts>
    void View<Ts...>::remove(Entity entity)
    {
        _entities.remove(entity);
        _components.remove(entity);
        _dirty(entity);
    }

    template<typename... Ts>
    template<typename T>
    void View<Ts...>::add(Entity entity)
    {
        _components.add<T>(entity);
        _dirty(entity);
    }

    template<typename... Ts>
    template<typename T>
    void View<Ts...>::remove(Entity entity)
    {
        _components.remove<T>(entity);
        _dirty(entity);
    }

    template<typename... Ts>
    template<typename T>
    T &View<Ts...>::get(Entity entity)
    {
        return _components.get<T>(entity);
    }

    template<typename... Ts>
    typename View<Ts...>::iterator const View<Ts...>::begin() const
    {
        return _view_entities.begin();
    }

    template<typename... Ts>
    typename View<Ts...>::iterator const View<Ts...>::end() const
    {
        return _view_entities.end();
    }

    template<typename... Ts>
    void View<Ts...>::update(Entity entity)
    {
        if (_signature.match(_components, entity)) {
            _view_entities.add(entity);
        } else {
            _view_entities.remove(entity);
        }
    }

    template<typename... Ts>
    void View<Ts...>::_dirty(Entity entity)
    {
        for (auto view : _views) {
            view.second->update(entity);
        }
    }

    template <>
    class View<> : public ViewBase
    {
    public:
        View(EntityManager &entities, ComponentManager &components,
             Signature<> signature,
             std::unordered_map<TypeId_t, ViewBase *> &views)
                : _entities(entities), _components(components), _views(views)
        {
        }

        Entity create()
        {
            Entity entity = _entities.create();
            _dirty(entity);
            return entity;
        }

        void remove(Entity entity)
        {
            _entities.remove(entity);
            _components.remove(entity);
            _dirty(entity);
        }

        template <typename T>
        void add(Entity entity)
        {
            _components.add<T>(entity);
            _dirty(entity);
        }

        template <typename T>
        void remove(Entity entity)
        {
            _components.remove<T>(entity);
            _dirty(entity);
        }

        template <typename T>
        T& get(Entity entity)
        {
            return _components.get<T>(entity);
        }

        using iterator = Entity*;

        const iterator begin() const
        {
            return _entities.begin();
        }

        const iterator end() const
        {
            return _entities.end();
        }

        void update(Entity entity) override
        {
        }

    private:
        void _dirty(Entity entity)
        {
            for (auto view : _views) {
                view.second->update(entity);
            }
        }

        EntityManager &_entities;
        ComponentManager &_components;
        std::unordered_map<TypeId_t, ViewBase*> &_views;
    };


}


#endif //ECS_VIEW_H
