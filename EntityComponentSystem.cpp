//
// Created by Pawel Boening on 17/06/18.
//

#include "EntityComponentSystem.h"

namespace pecs
{

    EntityComponentSystem::EntityComponentSystem()
            : _systems(_entities, _messages)
    {

    }
}
