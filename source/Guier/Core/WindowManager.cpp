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

#include <Guier/Core/WindowManager.hpp>
#include <Guier/Core/WindowImpl.hpp>
#include <Guier/Core/Semaphore.hpp>

#ifdef GUIER_PLATFORM_WINDOWS
#include <Windows.h>
#endif

namespace Guier
{

    namespace Core
    {

        WindowManager::WindowManager() :
            m_Running(false)
        {

        }

        WindowManager::~WindowManager()
        {
            stopThread();
        }


        void WindowManager::loadWindowImpl(WindowImpl * windowImpl)
        {
            std::lock_guard<std::mutex> sm_1(m_LoadMutex);
            {
                std::lock_guard<std::mutex> sm_2(m_Mutex);

                if (m_NextLoadWindow != nullptr)
                {
                    throw std::runtime_error("m_NextLoadWindow should be nulptr.");
                }
                m_NextLoadWindow = windowImpl;

                startThread();

                interruptEvents();
            }

            m_Semaphore.wait();

            if (m_NextLoadWindow != nullptr)
            {
                throw std::runtime_error("m_NextLoadWindow should be nulptr.");
            }
        }

        void WindowManager::unloadWindowImpl(WindowImpl * windowImpl)
        {
            std::lock_guard<std::mutex> sm_1(m_LoadMutex);
            std::lock_guard<std::mutex> sm_2(m_Mutex);

            auto wIt = m_Windows.find(windowImpl);
            if (wIt != m_Windows.end())
            {
                m_Windows.erase(wIt);
            }

            if (m_Windows.size() == 0)
            {
                stopThread();
            }
        }

        void WindowManager::startThread()
        {
            if (m_Running)
            {
                return;
            }

            Semaphore sem;
            m_Thread = std::thread([this, &sem]()
            {
                sem.notifyOne();

                // Message loop.
                m_Running = true;

                while(m_Running)
                {
                    handleNewWindow();
                    handleEvents();
                }

            });
            
            sem.wait();
        }

        void WindowManager::stopThread()
        {
            if (m_Running == false)
            {
                return;
            }

            m_Running = false;
            interruptEvents();
            m_Thread.join();
        }

        void WindowManager::handleEvents()
        {
            #ifdef GUIER_PLATFORM_WINDOWS
                // Go through all the window event messages
                MSG message;
                BOOL result = 0;
                while ((result = ::GetMessage(&message, NULL, 0, 0)) != 0)
                {
                    if (result == -1)
                    {
                        throw std::runtime_error("GetMessage returned -1.");
                    }
                    else
                    {
                        // A modal function is being called when you press the alt key,
                        // fix this by ignoring the alt(menu) key event.
                        if (message.message == WM_SYSCOMMAND &&
                            message.wParam == SC_KEYMENU)
                        {
                            break;
                        }

                        // Translate the dispatch the message
                        // This will call the WindowProcStatic function
                        ::TranslateMessage(&message);
                        ::DispatchMessage(&message);
                    }
                }
            #endif
        }

        void WindowManager::interruptEvents()
        {
            #if defined(GUIER_PLATFORM_WINDOWS)
                ::PostThreadMessage(::GetThreadId(m_Thread.native_handle()), WM_QUIT, 0, 0);
            #endif
        }

        void WindowManager::handleNewWindow()
        {
            std::lock_guard<std::mutex> sm(m_Mutex);

            if (m_NextLoadWindow)
            {
                m_NextLoadWindow->load();
                m_NextLoadWindow = nullptr;
                m_Semaphore.notifyOne();
            }

           
        }


    }

}
