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

#include <Guier/Core/Control.hpp>
#include <Guier/WindowStyle.hpp>
#include <Guier/Callback.hpp>
#include <Guier/Vector2.hpp>
#include <string>


namespace Guier
{

    class Context; ///< Forward declaration.
    
    namespace Core
    {

        /**
        * Base class of renderable window.
        *
        */
        class GUIER_API WindowBase : public ControlParent/* : public RenderTarget*/
        {

        protected:

            friend class Guier::WindowStyle; //< Friend class.

            /**
            * Constructor.
            *
            * @param constructor    Pointer to context.
            *
            * @throw std::runtime_error If context == nullptr.
            *
            */
            WindowBase(Context * context, const Vector2i & size, const std::wstring & title);

            /**
            * Destructor.
            *
            */
            ~WindowBase();

            WindowStyle             m_WindowStyle;  ///< Style of window.
            Context *               m_pContext;     ///< Current context.
            Vector2i                m_Size;         ///< Size of window.
            Vector2i                m_Position;     ///< Position of window.
            std::wstring            m_Title;        ///< Window title.

          /*  WindowImpl *            m_pImpl;            ///< Implementation of platform dependent functionality.
            std::atomic<bool>       m_Destroying;       ///< Window is being or is destroyed if true.
            mutable  std::mutex     m_ImplMutex;        ///< Implementaiton mutex.

            Vector2i                m_Size;
            std::wstring            m_Title;
            */
        private:

            virtual bool AddChild(Control * control, const Index & index) = 0;
            virtual bool RemoveChild(Control * control) = 0;
            virtual Control * RemoveChild(const Index & index) = 0;

            /**
            * Create implementation of window.
            *
            * @brief Called by Context.
            *        The Windows methods, for example Size(),
            *        will just return a dummy value if implementation is not yet created.
            *
            * @param context    Pointer of context.
            * @param window     Pointer of window.
            * @param size       Size of window.
            * @param title      Title of window.
            *
            */
           /* void CreateImplementation(Context * context, std::shared_ptr<Window> window);

            /**
            * Destroy implementation of window.
            *
            * @brief Called by Context.
            *        The Windows methods, for example Size(),
            *        will just return a dummy value if implementation is destroyed.
            *        A destroyed implementation can be recreated.
            *
            */
           // void DestroyImplementation();

            /**
            * Check or set status of window destruction.
            *
            * @return true if window is being or is destroyed.
            *
            */
           // std::atomic<bool> & Destroying();

            /**
            * Handle platform specific window events, of all windows created in Context.
            *
            */
           // static void HandleEvents();*/


        };

    }

}