//
// Created by Pawel Boening on 03.09.18.
//

#ifndef ECS_SIGNATUREBASE_H
#define ECS_SIGNATUREBASE_H


#include "Entity.h"

namespace pecs
{

    class SignatureBase
    {
    public:
        virtual ~SignatureBase() = default;
        virtual bool match(Entity entity) = 0;
    };

}


#endif //ECS_SIGNATUREBASE_H
