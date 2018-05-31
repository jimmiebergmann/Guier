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

#include <Guier/Core/RenderTarget.hpp>
#include <Guier/Control.hpp>
#include <Guier/WindowStyle.hpp>
#include <Guier/Callback.hpp>
#include <Guier/Vector2.hpp>
#include <Guier/String.hpp>


namespace Guier
{

    /**
    * Forward declarations.
    *
    */
    class Context;
    class Renderer;    
    
    namespace Core
    {

        class WindowImpl;
        class ContextBase;

        /**
        * Base class of renderable window.
        *
        */
        class GUIER_API WindowBase : public RenderTarget, public Parent
        {

        protected:

            /**
            * Constructor.
            *
            * @throw std::runtime_error If context == nullptr.
            *
            */
            WindowBase(Context * context, const Vector2i & size, const String & title);

            /**
            * Destructor.
            *
            */
            ~WindowBase();

            WindowImpl *            m_pImpl;        ///< Implementation of platform dependent functionality.
            WindowStyle             m_WindowStyle;  ///< Style of window.
            Context *               m_pContext;     ///< Current context.
            Vector2i                m_Size;         ///< Size of window.
            Vector2i                m_Position;     ///< Position of window.
            String                  m_Title;        ///< Window title.

           
        private:

            virtual bool AddChild(Control * child, const Index & index) = 0;
            virtual bool RemoveChild(Control * child) = 0;
            virtual Control * RemoveChild(const Index & index) = 0;

            /**
            * Load window, Internally create platform specific code.
            *
            * @param renderer      Renderer used. If nullptr, use available system renderer.
            *
            */
            bool Load(Renderer * renderer);

            /**
            * Handle platform specific window events, of all windows created in Context.
            *
            */
            static void HandleEvents();

            /**
            * Friend classs
            *
            */
            friend class ContextBase;
            friend class Guier::Context;
            friend class Guier::WindowStyle;

            

        };

    }

}