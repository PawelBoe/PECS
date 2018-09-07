//
// Created by Pawel Boening on 05.09.18.
//

#ifndef ECS_VIEWMANAGER_H
#define ECS_VIEWMANAGER_H


#include "View.h"
#include "EntityManager.h"
#include "ComponentManager.h"

namespace pecs
{

    class ViewManager
    {
    public:
        explicit  ViewManager(EntityManager &entities, ComponentManager &components);

        ~ViewManager();

        template <typename ... Ts>
        View<Ts...>& get(Signature<Ts...> signature);

    private:
        std::unordered_map<TypeId_t, ViewBase*> _views;
        EntityManager &_entities;
        ComponentManager &_components;
    };

    template<typename... Ts>
    View<Ts...> &ViewManager::get(Signature<Ts...> signature)
    {
        if (_views.find(TypeId<Signature<Ts...>>) == _views.end())
            _views[TypeId<Signature<Ts...>>] = new View<Ts...>(_entities, _components, signature, _views);
        return *(View<Ts...>*)_views.at(TypeId<Signature<Ts...>>);
    }

}


#endif //ECS_VIEWMANAGER_H
