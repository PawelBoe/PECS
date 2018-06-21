//
// Created by Pawel Boening on 17/06/18.
//

#include "EntityComponentSystem.h"

namespace pecs
{

    Entity EntityComponentSystem::create_entity()
    {
        return _entityManager.create_entity();
    }

    bool EntityComponentSystem::exists_entity(Entity entity)
    {
        return _entityManager.exists_entity(entity);
    }

    void EntityComponentSystem::delete_entity(Entity entity)
    {
        _entityManager.remove_entity(entity);
    }

}
