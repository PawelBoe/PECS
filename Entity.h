//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_ENTITY_H
#define ECS_ENTITY_H


#include <cstdint>

namespace pecs
{

    typedef uint16_t EntityIndex;
    typedef uint16_t EntityVersion;
    typedef uint32_t EntityId;

    class Entity
    {
    public:
        Entity(EntityIndex index, EntityVersion version);

        EntityIndex index();
        EntityVersion version();

    private:
        EntityId _id;
    };

}


#endif //ECS_ENTITY_H
