//
// Created by Pawel Boening on 17/06/18.
//

#include "Entity.h"

namespace pecs
{

    Entity::Entity(EntityIndex index, EntityVersion version) :
            _id(EntityId(index) << 16U | EntityId(version))
    {

    }

    EntityIndex Entity::index()
    {
        return EntityIndex(_id >> 16U);
    }

    EntityVersion Entity::version()
    {
        return EntityVersion(_id & 0xFFFFU);
    }

}
