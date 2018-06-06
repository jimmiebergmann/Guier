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

#include <Guier/String.hpp>

namespace Guier
{

    String::String()
    {

    }

    String::String(const std::string & string) :
        m_String(string.begin(), string.end())
    {

    }

    String::String(const std::wstring & string) :
        m_String(string)
    {

    }

    String::String(const char * chars)
    {
        std::string temp = chars;
        m_String = std::wstring(temp.begin(), temp.end());
    }

    String::String(const wchar_t * chars) :
        m_String(chars)
    {
        
    }

    String::~String()
    {

    }

    std::wstring & String::get()
    {
        return m_String;
    }

    const std::wstring & String::get() const
    {
        return m_String;
    }

    void String::set(const std::string & string)
    {
        m_String = std::wstring(string.begin(), string.end());
    }

    void String::set(const std::wstring & string)
    {
        m_String = string;
    }

    void String::set(const char * chars)
    {
        std::string temp = chars;
        m_String = std::wstring(temp.begin(), temp.end());
    }

    void String::set(const wchar_t * chars)
    {
        m_String = chars;
    }

}