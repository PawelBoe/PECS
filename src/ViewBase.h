//
// Created by Pawel Boening on 05.09.18.
//

#ifndef ECS_VIEWBASE_H
#define ECS_VIEWBASE_H


#include "Entity.h"

namespace pecs
{

    class ViewBase
    {
    public:
        virtual ~ViewBase() = default;

        virtual void update(Entity entity) = 0;
    };

}


#endif //ECS_VIEWBASE_H
