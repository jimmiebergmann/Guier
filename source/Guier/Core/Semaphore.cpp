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

#include <Guier/Core/Semaphore.hpp>

namespace Guier
{

    namespace Core
    {

        Semaphore::Semaphore() :
            m_Count(0)
        {
        }

        void Semaphore::notifyOne()
        {
            std::unique_lock<std::mutex> lock(m_Mutex);
            ++m_Count;
            m_Condition.notify_one();
        }

        void Semaphore::notifyAll()
        {
            std::unique_lock<std::mutex> lock(m_Mutex);
            m_Count = 0;
            m_Condition.notify_all();
        }

        void Semaphore::wait()
        {
            std::unique_lock<std::mutex> lock(m_Mutex);
            while (!m_Count)
            {
                m_Condition.wait(lock);
            }
            --m_Count;
        }

        bool Semaphore::tryWait()
        {
            std::unique_lock<std::mutex> lock(m_Mutex);
            if (m_Count)
            {
                --m_Count;
                return true;
            }

            return false;
        }

       /* bool Semaphore::waitFor(const unsigned int microseconds)
        {
            std::unique_lock<std::mutex> lock(m_Mutex);
            if (!m_Count)
            {
                // Ugly hack for inifinity wait time.
                if (microseconds == 4294967295)
                {
                    m_Condition.wait(lock);
                    --m_Count;
                    return true;
                }

                if (m_Condition.wait_for(lock, std::chrono::microseconds(microseconds)) == std::cv_status::no_timeout)
                {
                    --m_Count;
                    return true;
                }
            }

            return false;
        }*/

    }

}
