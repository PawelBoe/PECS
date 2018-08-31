//
// Created by Pawel Boening on 17/06/18.
//

#include "Entity.h"

namespace pecs
{
    Entity::Entity() :
            _id(EntityId(0) << 16U | EntityId(0))
    {

    }

    Entity::Entity(EntityIndex index, EntityVersion version) :
            _id(EntityId(index) << 16U | EntityId(version))
    {

    }

    EntityId Entity::id() const
    {
        return _id;
    }

    EntityIndex Entity::index() const
    {
        return EntityIndex(_id >> 16U);
    }

    EntityVersion Entity::version() const
    {
        return EntityVersion(_id & 0xFFFFU);
    }

}
