/*
* MIT License
*
* Copyright(c) 2018 Jimmie Bergmann
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files(the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions :
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
*/

#pragma once

#include <Guier/Core/Build.hpp>
#include <set>

namespace Guier
{
    class Renderer;
    class Skin;
    class Window;

    class GUIER_API Context
    {

    public:

        /**
        * Constructor.  
        *
        * @param renderer   The default renderer, defined in Build.hpp, will be allocated and set if renderer == nullptr.
        *                   Context has full responsibility of renderer unallocating.
        *
        * @throw std::runtime_error If renderer == nullptr, and there is no default renderer available.
        *
        */
        Context(Renderer * renderer = nullptr, Skin * skin = nullptr);
        Context(Skin * skin);


        /**
        * Destructor.
        *
        */
        ~Context();

        /**
        * Update context.
        *
        * Handle inputs, signals, etc..
        *
        */
        void Update();

        /**
        * Render context.
        *
        * @throw std::runtime_error If current renderer == nullptr.
        *
        */
        void Render();

        /**
        * Clear context.
        *
        * @brief Clearing and unallocating any attached renderer/window.
        *
        */
        Context & Clear();

        /**
        * Add object to context.
        *
        * @brief    Adding the same object twice has no effect.
        *
        * @param renderer   Add renderer to context. Current renderer is unallocated.
        *                   If rendrer == nullptr, the default renderer, defined in Build.hpp, will be allocated and set.
        * @param skin       Add skin to contect. 
        *                   If skin == nullptr, the default skin will be allocated and set.
        * @param window     Add window to context.
        * @param show       Show window after adding to context.
        *
        */
        Context & Add(Renderer * renderer);
        Context & Add(Skin * skin);
        Context & Add(Window * window, const bool show = true);

        /**
        * Remove object from context.
        *
        * @brief    The object is not unallocating when removed,
        *           and context is no longer responsible for unallocating of the object.
        *
        */
        Context & Remove(Renderer * renderer);
        Context & Remove(Skin * skin);
        Context & Remove(Window * window);

        /**
        * Get current renderer of context.
        *
        */
        Renderer * GetRenderer() const;

        /**
        * Get current skin of context.
        *
        */
        Skin * GetSkin() const;

    private:

        bool                m_DefaultRenderer;  ///< The context is currently using the default renderer.
        bool                m_DefaultSkin;      ///< The context is currently using the default skin.
        Renderer *          m_pRenderer;        ///< Pointer to renderer. Used for allocation of other renderers.
        Skin *              m_pSkin;            ///< Pointer to skin.
        std::set<Window *>  m_Windows;          ///< Set of attached windows.

    };

}