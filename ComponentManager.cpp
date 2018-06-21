//
// Created by Pawel Boening on 17/06/18.
//

#include "ComponentManager.h"
#include "ComponentSystems/ComponentDummy.h"

namespace pecs
{

    ComponentManager::ComponentManager()
    {
        _componentSystems[ComponentDummy::id] = new ComponentSystem<ComponentDummy>;
    }

    ComponentManager::~ComponentManager()
    {
        for (auto it : _componentSystems) {
            delete it.second;
        }
        _componentSystems.clear();
    }

}
