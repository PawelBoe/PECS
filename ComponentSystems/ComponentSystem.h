//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_COMPONENTSYSTEM_H
#define ECS_COMPONENTSYSTEM_H


#include <vector>
#include "ComponentSystemBase.h"

namespace pecs
{

    template <typename T>
    class ComponentSystem : public ComponentSystemBase
    {
    public:
        ~ComponentSystem() override = default;

        void create_component(Entity entity) override;
        void delete_component(Entity entity) override;

    private:
        ComponentBase* _get_component(Entity entity) override;

        std::vector<T> m_data;
    };

    template<typename T>
    void ComponentSystem<T>::create_component(Entity entity)
    {
        // TODO implement entity registration for component T
    }

    template<typename T>
    void ComponentSystem<T>::delete_component(Entity entity)
    {
        // TODO implement entity removal for component T
    }

    template<typename T>
    ComponentBase *ComponentSystem<T>::_get_component(Entity entity)
    {
        if (entity.index() < m_data.size()) {
            return &m_data[entity.index()];
        }

        return nullptr;
    }

}


#endif //ECS_COMPONENTSYSTEM_H
