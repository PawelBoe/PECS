//
// Created by Pawel Boening on 31.08.18.
//

#ifndef ECS_VIEW_H
#define ECS_VIEW_H


#include "util/TypeId.h"
#include "util/sparse_set.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Signature.h"
#include "ComponentManager.h"

namespace pecs
{

    class ViewBase
    {
    public:
        virtual ~ViewBase() = default;

    private:
        friend class ViewFactory;
        virtual void update(Entity entity) = 0;
    };

    template <typename ... Ts>
    class View : public ViewBase
    {
    public:
        View(EntityManager &entities, ComponentManager &components, Signature<Ts...> signature)
                : _entities(entities), _components(components), _signature(signature)
        {
            for (auto e : entities) {
                update(e);
            }
        }

        template <typename T>
        void create(Entity entity)
        {
            _components.create<T>(entity);
            _dirty(entity);
        }

        Entity create()
        {
            Entity entity = _entities.create();
            _dirty(entity);
            return entity;
        }

        template <typename T>
        void remove(Entity entity)
        {
            _components.remove<T>(entity);
            _dirty(entity);
        }

        void remove(Entity entity)
        {
            _entities.remove(entity);
            _dirty(entity);
        }

        template <typename T>
        T& component(Entity entity)
        {
            return _components.get<T>(entity);
        }

        using iterator = Entity*;
        const iterator begin() const
        {
            return _view_entities.begin();
        }

        const iterator end() const
        {
            return _view_entities.end();
        }

    private:
        void update(Entity entity) override
        {
            if (_signature.match(_components, entity)) {
                _view_entities.add(entity);
            } else {
                _view_entities.remove(entity);
            }
        }

        void _dirty(Entity entity)
        {

        }

        EntityManager &_entities;
        ComponentManager &_components;
        Signature<Ts...> _signature;
        sparse_set<Entity, Entity::Hash> _view_entities;
    };

    class ViewFactory
    {
    public:
        explicit  ViewFactory(EntityManager &entities, ComponentManager &components)
                : _entities(entities), _components(components)
        {

        }

        ~ViewFactory()
        {
            for (auto view : _views) {
                delete view.second;
            }
        }

        template <typename ... Ts>
        void create(Signature<Ts...> signature)
        {
            if (_views.find(TypeId<Signature<Ts...>>) == _views.end())
                _views[TypeId<Signature<Ts...>>] = new View<Ts...>(_entities, _components, signature);
        }

        template <typename ... Ts>
        View<Ts...>& view(Signature<Ts...> signature)
        {
            return *(View<Ts...>*)_views.at(TypeId<Signature<Ts...>>);
        }

        void dirty(Entity entity)
        {
            for (auto view : _views) {
                view.second->update(entity);
            }
        }

    private:
        std::unordered_map<TypeId_t, ViewBase*> _views;
        EntityManager &_entities;
        ComponentManager &_components;
    };


}


#endif //ECS_VIEW_H
