//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_ENTITYCOMPONENTSYSTEM_H
#define ECS_ENTITYCOMPONENTSYSTEM_H


#include <unordered_map>
#include "EntityManager.h"
#include "MessageManager.h"
#include "SystemManager.h"

namespace pecs
{

    class EntityComponentSystem
    {
    public:
        EntityComponentSystem();

    protected:
        EntityManager _entities;
        MessageManager _messages;
        SystemManager _systems;
    };

}


#endif //ECS_ENTITYCOMPONENTSYSTEM_H
