//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_COMPONENTSYSTEM_H
#define ECS_COMPONENTSYSTEM_H


#include <vector>
#include "SystemBase.h"
#include "Entity.h"
#include "EntityManager.h"
#include "ComponentManager.h"

namespace pecs
{

    template <typename T>
    class System : public SystemBase
    {
    public:
        ~System() override = default;

        void update(EntityManager &entities, ComponentManager &components, float dt);

        static SystemId systemId();
    };

    template<typename T>
    void System<T>::update(EntityManager &entities, ComponentManager &components, float dt)
    {
        static_cast<T*>(this)->_update(entities, components, dt);
    }

    template<typename T>
    SystemBase::SystemId System<T>::systemId()
    {
        static SystemId systemId = system_counter++;
        return systemId;
    }

}


#endif //ECS_COMPONENTSYSTEM_H
