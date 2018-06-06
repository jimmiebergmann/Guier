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

#include <mutex>

namespace Guier
{

    namespace Core
    {

        /**
        * @breif Helper class for thread safe variables.
        *
        */
        template<typename T>
        class Safe
        {

        public:

            /**
            * @breif Default constructor.
            *
            */
            Safe()
            {
            }

            /**
            * @breif Assignment constructor.
            *
            */
            Safe(const T & value_in) :
                value(value_in)
            {
            }

            /**
            * @breif Copy constructor.
            *
            */
            Safe(const Safe & safe) :
                value(safe.get())
            {
            }

            /**
            * @breif Destructor.
            *
            */
            ~Safe()
            {
            }

            /**
            * @breif Thread safe function for obtaining value.
            *
            * @return Value.
            *
            */
            const T get()
            {
                std::lock_guard<std::mutex> gm(mutex);
                return value;
            }

            /**
            * @breif Thread safe function for assigning value.
            *
            */
            void Set(const T & value_in)
            {
                std::lock_guard<std::mutex> gm(mutex);
                value = value_in;
            }

            /**
            * @breif Thread safe operation for obtaining value.
            *
            */
            const T & operator () ()
            {
                std::lock_guard<std::mutex> gm(mutex);
                return value;
            }

            /**
            * @breif Thread safe operation for assigning value.
            *
            */
            Safe & operator = (const T & value_in)
            {
                std::lock_guard<std::mutex> gm(mutex);
                value = value_in;
                return *this;
            }

            /**
            * @breif Thread safe operation for assigning value from another Safe class.
            *
            */
            Safe & operator = (const Safe & safe)
            {
                std::lock_guard<std::mutex> gm(mutex);
                value = safe.get();
                return *this;
            }

            /**
            * @breif Thread safe operation for comparing value.
            *
            */
            bool operator == (const T & value_in)
            {
                std::lock_guard<std::mutex> gm(mutex);
                return value == value_in;
            }

            bool operator != (const T & value_in)
            {
                std::lock_guard<std::mutex> gm(mutex);
                return value != value_in;
            }

            T			value; ///< Template value.
            std::mutex	mutex; ///< Mutex locking in thread safe methods.

        };

    }
}

