//
// Created by Pawel Boening on 01.08.18.
//

#include "ComponentManager.h"

namespace pecs
{

    ComponentManager::ComponentManager()
    {

    }

    ComponentManager::~ComponentManager()
    {
        for (auto it : _components) {
            delete it.second;
        }
        _components.clear();
    }

}
