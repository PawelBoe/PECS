//
// Created by Pawel Boening on 31.08.18.
//

#ifndef ECS_VIEW_H
#define ECS_VIEW_H


#include "util/sparse_set.h"
#include "Entity.h"

namespace pecs
{

    class View
    {
    public:

        using iterator = View*;
        iterator begin() const;
        iterator end() const;

    private:
        sparse_set<Entity, Entity::Hash> _entities;

    };

}


#endif //ECS_VIEW_H
