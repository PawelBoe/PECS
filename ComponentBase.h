//
// Created by Pawel Boening on 01.08.18.
//

#ifndef ECS_COMPONENTBASE_H
#define ECS_COMPONENTBASE_H


namespace pecs
{

    class ComponentBase
    {
    public:
        typedef int ComponentId;
        virtual ~ComponentBase() = default;

    protected:
        static ComponentId component_counter;
    };

}


#endif //ECS_COMPONENTBASE_H
