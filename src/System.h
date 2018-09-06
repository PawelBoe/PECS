//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_COMPONENTSYSTEM_H
#define ECS_COMPONENTSYSTEM_H


#include "SystemBase.h"
#include "Signature.h"
#include "View.h"

namespace pecs
{

    template <typename Derived, typename ... Components>
    class System : public SystemBase
    {
    public:
        ~System() override = default;

        void update(ViewBase &view, float dt);
        static Signature<Components...> signature; // TODO inline BUG!!
    };

    template<typename Derived, typename ... Components>
    Signature<Components...> System<Derived, Components...>::signature;

    template<typename Derived, typename ... Components>
    void System<Derived, Components...>::update(ViewBase &view, float dt)
    {
        static_cast<Derived*>(this)->_update(static_cast<View<Components...>&>(view), dt);
    }

}


#endif //ECS_COMPONENTSYSTEM_H
