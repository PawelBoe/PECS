//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_ENTITYMANAGER_H
#define ECS_ENTITYMANAGER_H

#include <vector>
#include <queue>
#include "Entity.h"
#include "PSSET/sparse_set.h"


namespace pecs
{

    class EntityManager
    {
    public:
        EntityManager();

        Entity create();
        bool exists(Entity entity) const;
        void remove(Entity entity);

        using iterator = Entity*;
        iterator begin() const;
        iterator end() const;

    private:
        EntityIndex _index_counter = 0;
        psset::sparse_set<Entity, Entity::Hash> _used;
        std::vector<Entity> _unused;
    };

}


#endif //ECS_ENTITYMANAGER_H
