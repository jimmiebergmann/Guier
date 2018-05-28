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

#include <Guier/Core/ContextBase.hpp>
#include <Guier/Window.hpp>

#if defined(GUIER_PLATFORM_WINDOWS)
#include <Guier/Core/Window/Win32WindowImpl.hpp>
#endif

namespace Guier
{

    namespace Core
    {

        bool ContextBase::Add(Window * window)
        {
            std::lock_guard<std::mutex> sm(m_TickMutex);

            return false;
        }

        bool ContextBase::Set(Renderer * renderer)
        {
            std::lock_guard<std::mutex> sm(m_TickMutex);

            return false;
        }

        void ContextBase::Tick()
        {
            std::lock_guard<std::mutex> sm(m_TickMutex);

            // ...
        }

        ContextBase::ContextBase(Context * context, Renderer * renderer, Skin * skin, const bool autoTick) :
            m_pContext(context),
            m_AutoTick(autoTick),
            m_Running(false),
            m_pRenderer(renderer),
            m_pSkin(skin)
        {
            // Try to load default renderer.
            if (m_pRenderer == nullptr)
            {
                m_pRenderer = Renderer::CreateDefaultRenderer();

                // Check if default renderer is ok.
                if (m_pRenderer == nullptr)
                {
                    throw std::runtime_error("Failed to create default renderer.");
                }
            }

            // Try to load default skin.
            if (m_pSkin == nullptr)
            {
                m_pSkin = Skin::CreateDefaultSkin();

                // Check if default skin is ok.
                if (m_pSkin == nullptr)
                {
                    throw std::runtime_error("Failed to create default skin.");
                }
            }
 
            // Flag the context as running.
            m_Running = true;

            Core::Semaphore startWindowThreadSemaphore;
            //Core::Semaphore startWindowInterruptSemaphore;

           /* m_InterruptWindowThread = std::thread([this, &startWindowInterruptSemaphore]()
            {
                startWindowInterruptSemaphore.NotifyOne();

                while (m_Running)
                {
                    m_WindowSempahore.Wait();

                    ExecuteWindowEventInterrupt();

                    if (m_Running == false)
                    {
                        return;
                    }
                }
            });*/

          /*  m_WindowThread = std::thread([this, &startWindowThreadSemaphore]()
            {
                startWindowThreadSemaphore.NotifyOne();

                while (m_Running)
                {
                    // Create windows
                    CreateWindowsInQueue();

                    // Destroy windows
                    DestroyWindowsInQueue();

                    // Handle window events.
                    // This is a modal function, using Win32 or X11.
                    // It's possible to interrupt the function by calling InterruptWindowEvents();
                    HandleWindowEvents();
                }

            });

            startWindowThreadSemaphore.Wait();
            startWindowInterruptSemaphore.Wait();*/
        }

        void ContextBase::CreateWindowsInQueue()
        {
           /* std::lock_guard<std::mutex> sm_2(m_WindowMutex);
            std::lock_guard<std::mutex> sm_1(m_WindowCreationMutex); 

            while (m_WindowCreationQueue.size())
            {
                auto front = m_WindowCreationQueue.front();
                m_WindowCreationQueue.pop();

                front->window = std::shared_ptr<Window>(new Window(front->size, front->title), &WindowSharedPointerDeleter);
                front->window->CreateImplementation(m_pContext, front->window);

                m_Windows.insert(front->window);

                front->semaphore.NotifyOne();
            }*/
        }

        void ContextBase::DestroyWindowsInQueue()
        {
            /*std::lock_guard<std::mutex> sm_2(m_WindowMutex);
            std::lock_guard<std::mutex> sm_1(m_WindowDestructionMutex);

            for (auto it = m_WindowDestructionSet.begin(); it != m_WindowDestructionSet.end(); it++)
            {
                (*it)->DestroyImplementation();
            }

            m_WindowDestructionSet.clear();*/
        }

        void ContextBase::HandleWindowEvents()
        {
            //Core::WindowBase::HandleEvents();
        }

        void ContextBase::InterruptWindowEvents()
        {
            m_WindowSempahore.NotifyOne();
        }

        void ContextBase::ExecuteWindowEventInterrupt()
        {
            #if defined(GUIER_PLATFORM_WINDOWS)
                ::PostThreadMessage(GetThreadId(m_WindowThread.native_handle()), WM_QUIT, 0, 0);
            #else
            #error Unkown platform.
            #endif
        }

        void ContextBase::ClearAllWindows()
        {
           /* std::lock_guard<std::mutex> sm_1(m_WindowMutex);
            std::lock_guard<std::mutex> sm_2(m_WindowCreationMutex);
            std::lock_guard<std::mutex> sm_3(m_WindowDestructionMutex);
            
            for (auto it = m_WindowDestructionSet.begin(); it != m_WindowDestructionSet.end(); it++)
            {
                (*it)->DestroyImplementation();
            }
            m_WindowDestructionSet.clear();

            while(m_WindowCreationQueue.size())
            {
                m_WindowCreationQueue.pop();
            }

            for (auto it = m_Windows.begin(); it != m_Windows.end(); it++)
            {
                (*it)->DestroyImplementation();
            }
            m_Windows.clear();
            */
        }

        void ContextBase::WindowSharedPointerDeleter(Window * window)
        {
            //delete window;
        }
        

    }

}