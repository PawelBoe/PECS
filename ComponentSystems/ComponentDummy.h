//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_COMPONENTDUMMY_H
#define ECS_COMPONENTDUMMY_H


#include "ComponentBase.h"

namespace pecs
{

struct ComponentDummy : public ComponentBase
{
    int x;
    int y;

    const static ComponentId id;
};

}


#endif //ECS_COMPONENTDUMMY_H
