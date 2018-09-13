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
        Entity entity;

        if (_unused.empty()) {
            EntityIndex index = _index_counter++;
            entity = Entity(index, 0);
            _used.add(entity);
        } else {
            entity = _unused.back();
            _unused.pop_back();
            _used.add(entity);
        }

        return entity;
    }

    bool EntityManager::exists(Entity entity) const
    {
        auto idx = _used.search(entity);

        if (idx >= _used.size())
            return false;

        return _used.data()[idx].version() == entity.version();
    }

    void EntityManager::remove(Entity entity)
    {
        if (exists(entity)) {
            _used.remove(entity);
            Entity removed_entity(entity.index(), static_cast<EntityVersion>(entity.version() + 1));
            _unused.push_back(removed_entity);
        }
    }

    EntityManager::iterator EntityManager::begin() const
    {
        return _used.begin();
    }

    EntityManager::iterator EntityManager::end() const
    {
        return _used.end();
    }

}
