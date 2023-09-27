#pragma once
#include <NGIN/Defines.hpp>

namespace NGIN::Core
{
    class Module
    {
    public:
        Module() = default;
        virtual ~Module() = default;

    protected:
        friend class Engine;
        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnPreTick(const F64 deltaTime) {}
        virtual void OnTick(const F64 deltaTime) {}
        virtual void OnPostTick(const F64 deltaTime) {}

        Engine* enginePtr = nullptr;

    };
}