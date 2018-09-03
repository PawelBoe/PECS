//
// Created by Pawel Boening on 03.09.18.
//

#ifndef ECS_SIGNATURE_H
#define ECS_SIGNATURE_H


#include "ComponentManager.h"
#include "SignatureBase.h"

namespace pecs
{

    template <typename ... Ts>
    class Signature : public SignatureBase
    {
    public:
        explicit Signature(ComponentManager &components);

        bool match(Entity entity) override;

    private:
        template <typename C>
        bool _match(Entity entity);

        template <typename C1, typename C2, typename ... Cs>
        bool _match(Entity entity);

        ComponentManager &_components;
    };

    template<typename... Ts>
    Signature<Ts...>::Signature(ComponentManager &components)
            : _components(components)
    {
    }

    template<typename... Ts>
    bool Signature<Ts...>::match(Entity entity)
    {
        return _match<Ts ...>(entity);
    }

    template<typename... Ts>
    template<typename C>
    bool Signature<Ts...>::_match(Entity entity)
    {
        return _components.exists<C>(entity);
    }

    template<typename... Ts>
    template<typename C1, typename C2, typename... Cs>
    bool Signature<Ts...>::_match(Entity entity)
    {
        return _components.exists<C1>(entity) && _match<C2, Cs ...>(entity);
    }

    template <>
    class Signature <> : public SignatureBase
    {
    public:
        explicit Signature(ComponentManager &components);

        bool match(Entity entity) override;
    };

    Signature<>::Signature(ComponentManager &components)
    {
    }

    bool Signature<>::match(Entity entity)
    {
        return false;
    }

}


#endif //ECS_SIGNATURE_H
