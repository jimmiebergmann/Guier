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
#include <thread>
#include <mutex>
#include <list>
#include <set>
#include <atomic>

namespace Guier
{

    namespace Core
    {

        class WindowImpl;

        class GUIER_API WindowManager
        {

        public:

            /**
            * Constructor.
            *
            */
            WindowManager();

            /**
            * Destructor.
            *
            */
            ~WindowManager();

            /**
            * Call this function to load window implementation.
            *
            * @brief    All windows should be created in the same thread.
            *
            */
            void loadWindowImpl(WindowImpl * windowImpl);

            /**
            * Call this function to unload window implementation.
            *
            * @brief    All windows should be created in the same thread.
            *
            *
            */
            void unloadWindowImpl(WindowImpl * windowImpl);

        private:

            void startThread();
            void stopThread();
            void handleEvents();
            void interruptEvents();
            void handleNewWindow();

            std::thread         m_Thread;
            std::mutex          m_Mutex;
            std::mutex          m_LoadMutex;
            Semaphore           m_Semaphore;
            
            std::atomic<bool>       m_Running;
            std::set<WindowImpl*>   m_Windows;
            WindowImpl*             m_NextLoadWindow;




        };

    }

}