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
#include <string>

namespace Guier
{

    /**
    * String class, based of wide string, but allows single byte strings as well.
    * This class is only used for parameter passing, to allow both wide and single byte strings as parameters.
    *
    */
    class GUIER_API String
    {

    public:

        /**
        * Constructor.
        *
        */
        String();
        String(const std::string & string);
        String(const std::wstring & string);
        String(const char * chars);
        String(const wchar_t * chars);

        /**
        * Destructor.
        *
        */
        ~String();

        /**
        * Get wide string.
        *
        */
        std::wstring & get();
        const std::wstring & get() const;

        /**
        * Set string.
        *
        */
        void set(const std::string & string);
        void set(const std::wstring & string);
        void set(const char * chars);
        void set(const wchar_t * chars);

    private:

        std::wstring m_String;

    };

}