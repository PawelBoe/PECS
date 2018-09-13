//
// Created by Pawel Boening on 17/06/18.
//

#include "SystemManager.h"

namespace pecs
{

    SystemManager::SystemManager()
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
