#pragma once

#include <NGIN/Defines.hpp>
#include <vector>
#include <unordered_map>
#include <NGIN/Meta/TypeName.hpp>
#include "Module.hpp"
#include <NGIN/Time.hpp>
#include <NGIN/Core/EventBus.hpp>
#include <NGIN/Core/Events/Quit.hpp>

namespace NGIN::Core
{
    //  class Layer;

    class Engine
    {
    public:
        NGIN_API Engine() = default;

        NGIN_API  ~Engine() = default;

        NGIN_API void Tick();


        NGIN_API EventBus& GetEventBus();

        template<typename T, typename ... Args>
        requires std::is_base_of_v<Module, T>
        void AddModule(Args&& ... args);

        template<typename T>
        requires std::is_base_of_v<Module, T>
        T* GetModule();


        NGIN_API void Quit();


        NGIN_API void Quit(const Events::Quit& event);

    private:
        std::unordered_map<String, UInt64> moduleIndexMap;
        std::vector<Module*> moduleVector;
        Time::Timer timer = Time::Timer();
        EventBus eventBus = EventBus();
        Bool shouldQuit = false;
        Bool isRunning = false;
    };


    //Template Implementations
    /// TODO: AddModule() should allocate the module from an allocator
    template<typename T, typename ... Args>
    requires std::is_base_of_v<Module, T>
    void Engine::AddModule(Args&& ... args)
    {
        const String TName = String(NGIN::Meta::TypeName<T>::Class());
        // Check if layer already exists
        if (moduleIndexMap.contains(TName))
            return;
        // Check if layer has dependencies
        if constexpr (requires { T::Dependencies(nullptr); })
            T::Dependencies(this);
        // Check if layer already exists again in case of circular dependencies
        if (moduleIndexMap.contains(TName))
            return;

        // Create layer
        moduleIndexMap[TName] = moduleVector.size();
        moduleVector.emplace_back(new T(std::forward<Args>(args)...));
        moduleVector.back()->OnInit(this);
    }

    template<typename T>
    requires std::is_base_of_v<Module, T>
    T* Engine::GetModule()
    {
        const String TName = String(NGIN::Meta::TypeName<T>::Class());
        if (!moduleIndexMap.contains(TName))
            return nullptr;
        return static_cast<T*>(moduleVector[moduleIndexMap[TName]]);
    }
}
