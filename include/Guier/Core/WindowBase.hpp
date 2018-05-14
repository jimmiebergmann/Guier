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
#include <Guier/Vector2.hpp>
#include <string>
#include <memory>
#include <atomic>
#include <mutex>

namespace Guier
{
    class Context;
    class Window;
    
    namespace Core
    {
        class ContextBase;
        class WindowImpl;

        /**
        * Base class of renderable window.
        *
        */
        class GUIER_API WindowBase : public RenderTarget
        {

        public:

            /**
            * Friend classes.
            *
            */
            friend class Guier::Context;
            friend class ContextBase;

            /**
            * Styles of window.
            *
            */
            struct Styles
            {
                enum eStyle
                {
                    None = 0,
                    TitleBar = 1, ///< Includes border.
                    Border = 2,
                    Close = 4,
                    Minimize = 8,
                    Maximize = 16,
                    Resize = 32,
                    HideInTaskbar = 64,

                    Default = 63
                };
            };

            /**
            * Constructor.
            *
            */
            WindowBase(const Vector2i & size, const std::wstring & title);

            /**
            * Destructor.
            *
            */
            virtual ~WindowBase();

        protected:

            WindowImpl *            m_pImpl;            ///< Implementation of platform dependent functionality.
            std::atomic<bool>       m_Destroying;       ///< Window is being or is destroyed if true.
            mutable  std::mutex     m_ImplMutex;        ///< Implementaiton mutex.

            Vector2i                m_Size;
            std::wstring            m_Title;

        private:

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
            void CreateImplementation(Context * context, std::shared_ptr<Window> window);

            /**
            * Destroy implementation of window.
            *
            * @brief Called by Context.
            *        The Windows methods, for example Size(),
            *        will just return a dummy value if implementation is destroyed.
            *        A destroyed implementation can be recreated.
            *
            */
            void DestroyImplementation();

            /**
            * Check or set status of window destruction.
            *
            * @return true if window is being or is destroyed.
            *
            */
            std::atomic<bool> & Destroying();

            /**
            * Handle platform specific window events, of all windows created in Context.
            *
            */
            static void HandleEvents();


        };

    }

}