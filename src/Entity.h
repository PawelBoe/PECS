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
        struct Hash
        {
            unsigned int operator()(Entity const& e) const
            {
                return e.index();
            }
        };

        Entity();
        Entity(EntityIndex index, EntityVersion version);

        EntityId id() const;
        EntityIndex index() const;
        EntityVersion version() const;

        bool operator==(const Entity &rhs) const;
        bool operator!=(const Entity &rhs) const;

    private:
        EntityId _id;
    };

}


#endif //ECS_ENTITY_H
