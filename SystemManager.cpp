//
// Created by Pawel Boening on 17/06/18.
//

#include "SystemManager.h"

namespace pecs
{

    SystemManager::SystemManager(EntityManager &entity_manager, MessageManager &message_manager)
            : _entities(entity_manager),
              _messages(message_manager)
    {
    }

    SystemManager::~SystemManager()
    {
        for (auto it : _systems) {
            delete it.second;
        }
        _systems.clear();
    }

}
