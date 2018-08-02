//
// Created by Pawel Boening on 17/06/18.
//

#ifndef ECS_COMPONENTSYSTEMBASE_H
#define ECS_COMPONENTSYSTEMBASE_H


namespace pecs
{

    class SystemBase
    {
    public:
        typedef int SystemId;
        virtual ~SystemBase() = default;

    protected:
        static SystemId system_counter;
    };

}


#endif //ECS_COMPONENTSYSTEMBASE_H
