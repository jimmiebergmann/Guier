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

#include <Guier/Context.hpp>
#include <Guier/Renderer.hpp>
#include <Guier/Window.hpp>
#include <Guier/Skin.hpp>

namespace Guier
{

    Context::Context() :
        ContextBase(this)
    {
        if (m_pRenderer == nullptr)
        {
            throw std::runtime_error("Failed to create renderer.");
        }

        m_Running = true;

        Core::Semaphore startWindowThreadSemaphore;
        Core::Semaphore startWindowInterruptSemaphore;

        m_InterruptWindowThread = std::thread([this, &startWindowInterruptSemaphore]()
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
        });

        m_WindowThread = std::thread([this, &startWindowThreadSemaphore]()
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
        startWindowInterruptSemaphore.Wait();
    }

    Context::~Context()
    {
        m_Running = false;
        m_WindowSempahore.NotifyOne();
        m_InterruptWindowThread.join();
        m_WindowThread.join();

        ClearAllWindows();

        delete m_pRenderer;
    }

    Context & Context::Remove(std::shared_ptr<Window> window)
    {
        if (window->Destroying())
        {
            return *this;
        }
        
        {
            std::lock_guard<std::mutex> sm_1(m_WindowMutex);

            // Find window and make sure it exists.
            auto it = m_Windows.find(window);
            if (it == m_Windows.end())
            {
                return *this;
            }

            window->Destroying() = true;

            // Push and notify window thread.
            // The windows are added to a creation queue, in order to initialize the windows in the same thread.
            {
                std::lock_guard<std::mutex> sm_2(m_WindowDestructionMutex);
                m_WindowDestructionSet.insert(*it);
            }

            // Call removed signal.
            (*it)->Removed();

            // Remove window from set.
            m_Windows.erase(it);

            // Interrupt window event loop.
            InterruptWindowEvents();
        }

        return *this;
    }

}