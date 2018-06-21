//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_COMPONENTSYSTEMBASE_H
#define ECS_COMPONENTSYSTEMBASE_H


#include "ComponentBase.h"
#include "../Entity.h"

namespace pecs
{

    class ComponentSystemBase
    {
    public:
        virtual ~ComponentSystemBase() = default;

        virtual void create_component(Entity entity) = 0;
        virtual void delete_component(Entity entity) = 0;

        template <typename T>
        T* get_component(Entity entity);

    private:
        virtual ComponentBase* _get_component(Entity entity) = 0;
    };

    template <typename T>
    T* ComponentSystemBase::get_component(Entity entity)
    {
        return (T*) _get_component(entity);
    }

}


#endif //ECS_COMPONENTSYSTEMBASE_H
