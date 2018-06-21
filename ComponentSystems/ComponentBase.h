//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_COMPONENTBASE_H
#define ECS_COMPONENTBASE_H


#include <array>

namespace pecs
{

    enum ComponentId
    {
        BASE,
        Dummy,
    };

    struct ComponentBase
    {
        const static ComponentId id;
    };

}


#endif //ECS_COMPONENTBASE_H
