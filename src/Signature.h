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
        bool match(ComponentManager &components, Entity entity) override;

    private:
        template <typename C>
        bool _match(ComponentManager &components, Entity entity);

        template <typename C1, typename C2, typename ... Cs>
        bool _match(ComponentManager &components, Entity entity);
    };

    template<typename... Ts>
    bool Signature<Ts...>::match(ComponentManager &components, Entity entity)
    {
        return _match<Ts ...>(components, entity);
    }

    template<typename... Ts>
    template<typename C>
    bool Signature<Ts...>::_match(ComponentManager &components, Entity entity)
    {
        return components.exists<C>(entity);
    }

    template<typename... Ts>
    template<typename C1, typename C2, typename... Cs>
    bool Signature<Ts...>::_match(ComponentManager &components, Entity entity)
    {
        return components.exists<C1>(entity) && _match<C2, Cs ...>(components, entity);
    }

    template <>
    class Signature <> : public SignatureBase
    {
    public:
        bool match(ComponentManager &components, Entity entity) override
        {
            return true;
        }
    };

}


#endif //ECS_SIGNATURE_H
