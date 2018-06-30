//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_COMPONENTSYSTEMBASE_H
#define ECS_COMPONENTSYSTEMBASE_H


#include "../Entity.h"
#include "../EntityManager.h"
#include "../MessageManager.h"

namespace pecs
{

    class SystemBase
    {
    public:
        typedef size_t SystemId;
        virtual ~SystemBase() = default;

    protected:
        static SystemId system_counter;
    };

}


#endif //ECS_COMPONENTSYSTEMBASE_H
