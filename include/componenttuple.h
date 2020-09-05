#pragma once

#include "entity.h"
#include "components.h"

#include <tuple>

// Taken from
// https://eli.thegreenplace.net/2014/variadic-templates-in-c/

namespace component
{
    class I_ComponentTuple
    {
        public:
            virtual bool accepts(const Entity&) = 0;
    };

    template<class... Components>
    class ComponentTuple : I_ComponentTuple
    {
        private:
            std::tuple<Components*> components;

        public:
            bool accepts(const Entity&) override;
    };
};
