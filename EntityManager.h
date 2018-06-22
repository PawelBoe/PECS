//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_ENTITYMANAGER_H
#define ECS_ENTITYMANAGER_H

#include <vector>
#include <queue>
#include "Entity.h"

/*
 *
 * Requirements
 * - ordered
 * - tightly packed
 * - unique
 * - exists in O(1)
 * - create in O(1)
 * - remove in O(1)
 *
 */

namespace pecs
{

    class EntityManager
    {
    public:
        EntityManager();

        Entity create();
        bool exists(Entity entity);
        void remove(Entity entity);

    private:
        EntityIndex _index_counter;
        std::vector<EntityIndex> _free_list;
        std::vector<EntityVersion> _entity_version;
    };

}


#endif //ECS_ENTITYMANAGER_H
