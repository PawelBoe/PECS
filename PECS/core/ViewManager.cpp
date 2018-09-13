//
// Created by Pawel Boening on 05.09.18.
//

#include "ViewManager.h"

namespace pecs
{

    pecs::ViewManager::~ViewManager()
    {
        for (auto view : _views) {
            delete view.second;
        }
    }

    ViewManager::ViewManager(EntityManager &entities,
                             ComponentManager &components)
            : _entities(entities), _components(components)
    {

    }

}
