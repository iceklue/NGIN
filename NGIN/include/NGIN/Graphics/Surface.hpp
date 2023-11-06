//
// Created by Maximiliam Berggren on 04/10/2023.
//

#pragma once
// NGIN Include(s)
#include <NGIN/Defines.hpp>
// STL Include(s)
// Other Include(s)

namespace NGIN::Graphics
{
    /// @class Surface
    /// @brief Interface for a rendering target surface.
    class NGIN_API Surface
    {
    public:
        /// @brief Virtual destructor to ensure proper cleanup for derived classes.
        virtual ~Surface() = default;

        /// @brief Retrieves the native handle of the surface.
        /// @return A pointer to the native surface handle.
        [[nodiscard]] virtual void* GetNativeHandle() const = 0;

        /// @brief Gets the dimensions of the surface.
        /// @param[out] width The width of the surface.
        /// @param[out] height The height of the surface.
        virtual void GetDimensions(UInt32& outWidth, UInt32& outHeight) const = 0;

        /// @brief Sets the dimensions of the surface.
        /// @param[in] width The new width of the surface.
        /// @param[in] height The new height of the surface.
        virtual void SetDimensions(UInt32 width, UInt32 height) = 0;

        /// @brief  Binds the surface for rendering.
        virtual void Bind() = 0;
        /// @brief Unbinds the surface from rendering.
        virtual void Unbind() = 0;
        /// @brief Clears the surface.
        virtual void Clear() = 0;
        /// @brief Presents the surface.
        /// This is only applicable for surfaces that are double/triple buffered.
        virtual void Present() = 0;
    };
}


