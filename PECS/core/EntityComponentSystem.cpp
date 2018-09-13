//
// Created by Pawel Boening on 17/06/18.
//

#include "EntityComponentSystem.h"

namespace pecs
{

    EntityComponentSystem::EntityComponentSystem()
            : _views(_entities, _components), _data(_views.get(Signature<>()))
    {
    }

}
