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
#include <Guier/Core/Semaphore.hpp>
#include <Guier/Vector2.hpp>
#include <set>
#include <queue>
#include <memory>
#include <thread>
#include <atomic>
#include <Guier/Renderer.hpp>
#include <Guier/Skin.hpp>

namespace Guier
{

    class Context;
    class Renderer;
    class Skin;
    class Window;

    namespace Core
    {
        class ContextBase;
        class WindowBase;


        struct WindowCreation
        {
            WindowCreation(const Vector2i & p_Size = { 800, 600 }, const std::wstring & p_Title = L"") :
                size(p_Size), title(p_Title)
            {

            }
            WindowCreation(const std::wstring & p_Title, const Vector2i & p_Size = { 800, 600 }) :
                size(p_Size), title(p_Title)
            {

            }
            WindowCreation(const int p_SizeX, const int p_SizeY, const std::wstring & p_Title = L"") :
                size(p_SizeX, p_SizeY), title(p_Title)
            {

            }
            WindowCreation(const std::wstring & p_Title, const int p_SizeX, const int p_SizeY) :
                size(p_SizeX, p_SizeY), title(p_Title)
            {

            }

            Vector2i                size;
            std::wstring            title;
            Semaphore               semaphore;
            std::shared_ptr<Window> window;
        };

        /**
        * Context base class.
        *
        */
        class GUIER_API ContextBase
        {

        public:

            /**
            * Add window to context.
            *
            * @return True if window is added, else false.
            *
            */
            bool Add(Window * window);

            /**
            * Set renderer.
            *
            * @return True if renderer has been changed, else false.
            *
            */
            bool Set(Renderer * renderer);

            /**
            * Tick the context.
            *
            * @brief Do not call, if auto tick is true. The system will handle it for you.

            *
            */
            void Tick();

        protected:

            /**
            * Default constructor.
            *
            */
            ContextBase(Context * context, Renderer * renderer, Skin * skin, const bool autoTick);

            void CreateWindowsInQueue();
            void DestroyWindowsInQueue();

            void HandleWindowEvents();
            void InterruptWindowEvents();
            void ExecuteWindowEventInterrupt();

            void ClearAllWindows();


            static void WindowSharedPointerDeleter(Window * window);

            std::atomic<bool>                   m_Running;              ///< Threads are running.
            std::thread                         m_WindowThread;           ///< Running thread.
            std::thread                         m_InterruptWindowThread;  ///< Thread for interruping window events.
            Core::Semaphore                     m_WindowSempahore;    ///< Semaphore for ticking thread, for example when redrawing.
            
            //Skin *                              m_pSkin;            ///< Pointer to skin.
            std::set<std::shared_ptr<Window>>   m_Windows;          ///< Set of attached windows.

            std::mutex                          m_WindowMutex;

            std::mutex                          m_WindowCreationMutex;
            std::queue<WindowCreation*>         m_WindowCreationQueue;

            std::mutex                          m_WindowDestructionMutex;
            std::set<std::shared_ptr<Window>>   m_WindowDestructionSet;


            //std::set<Control *>                 m_ControlRedraw;

        private:

            Context * const                     m_pContext;         ///< Pointer to inheriting context.
            const bool                          m_AutoTick;         ///< Should the context start a new thread and automatically tick when possible?.
            Semaphore                           m_TickSemaphore;    ///< Tick trigger.
            std::mutex                          m_TickMutex;        ///< Tick mutex.
            Renderer *                          m_pRenderer;        ///< Pointer to renderer.
            Skin *                              m_pSkin;        ///< Pointer to skin.

        };

    }

}