//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_SYSTEMMANAGER_H
#define ECS_SYSTEMMANAGER_H


#include <unordered_map>
#include "util/TypeId.h"
#include "System.h"
#include "EntityManager.h"
#include "ComponentManager.h"

namespace pecs
{

    class SystemManager
    {
    public:
        SystemManager();
        ~SystemManager();

        template <typename T, typename ... Args>
        void assign(Args && ... args);

        template <typename T, typename ... Args>
        void update(ViewBase &view, Args &&... args);

    private:
        template <typename T>
        T* system();

        std::unordered_map<TypeId_t, SystemBase*> _systems;
    };

    template<typename T, typename... Args>
    void SystemManager::assign(Args &&... args)
    {
        if (_systems.find(TypeId<T>) == _systems.end())
            _systems[TypeId<T>] = new T(std::forward<Args>(args) ...);
    }

    template<typename T, typename ... Args>
    void SystemManager::update(ViewBase &view, Args && ... args)
    {
        system<T>()->update(view, std::forward<Args>(args) ...);
    }

    template<typename T>
    T* SystemManager::system()
    {
        return static_cast<T*>(_systems.at(TypeId<T>));
    }
}


#endif //ECS_SYSTEMMANAGER_H
