//
// Created by Pawel Boening on 17/06/18.
//

#include "EntityManager.h"

namespace pecs
{

    EntityManager::EntityManager()
    {

    }

    Entity EntityManager::create()
    {
        EntityIndex index;

        if (_free_list.empty()) {
            index = _index_counter++;
            _entity_version.push_back(1);
        } else {
            index = _free_list.back();
            _free_list.pop_back();
        }

        return {index, _entity_version[index]};
    }

    bool EntityManager::exists(Entity entity) const
    {
        return _entity_version[entity.index()] == entity.version();
    }

    void EntityManager::remove(Entity entity)
    {
        if (exists(entity)) {
            EntityIndex index = entity.index();
            _entity_version[index] += 1;
            _free_list.push_back(index);
        }
    }

    const std::vector<Entity> &EntityManager::entities() const
    {
        return _entities;
    }

}
