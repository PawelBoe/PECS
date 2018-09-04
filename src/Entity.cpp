//
// Created by Pawel Boening on 17/06/18.
//

#include "Entity.h"

namespace pecs
{
    Entity::Entity()
            : _id(EntityId(0) << 8U | EntityId(0))
    {

    }

    Entity::Entity(EntityIndex index, EntityVersion version)
            : _id(EntityId(index) << 8U | EntityId(version))
    {

    }

    EntityId Entity::id() const
    {
        return _id;
    }

    EntityIndex Entity::index() const
    {
        return EntityIndex(_id >> 8U);
    }

    EntityVersion Entity::version() const
    {
        return EntityVersion(_id & 0xFFU);
    }

    bool Entity::operator==(const Entity &rhs) const
    {
        return _id == rhs._id;
    }

    bool Entity::operator!=(const Entity &rhs) const
    {
        return !(rhs == *this);
    }

}
