//
// Created by Pawel Boening on 01.08.18.
//

#ifndef ECS_COMPONENTBASE_H
#define ECS_COMPONENTBASE_H


#include "Entity.h"

namespace pecs
{

    class ComponentBase
    {
    public:
        virtual ~ComponentBase() = default;
        virtual void remove(Entity entity) = 0;
    };

}


#endif //ECS_COMPONENTBASE_H
