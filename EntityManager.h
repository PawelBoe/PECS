//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_ENTITYMANAGER_H
#define ECS_ENTITYMANAGER_H

#include <vector>
#include <queue>
#include "Entity.h"


namespace pecs
{

    class EntityManager
    {
    public:
        EntityManager();

        Entity create();
        bool exists(Entity entity) const;
        void remove(Entity entity);

        const std::vector<Entity>& entities() const;

    private:
        EntityIndex _index_counter = 0;
        std::vector<EntityIndex> _free_list;
        std::vector<EntityVersion> _entity_version;
        std::vector<Entity> _entities;
    };

}


#endif //ECS_ENTITYMANAGER_H
