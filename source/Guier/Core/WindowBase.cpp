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

#include <Guier/Core/WindowBase.hpp>
#include <Guier/Core/WindowImpl.hpp>

namespace Guier
{

    class Window;

    namespace Core
    {

        WindowBase::WindowBase() :
            m_pImpl(nullptr),
            m_Deleted(false)
        {

        }

        WindowBase::~WindowBase()
        {
        }

        WindowBase::Settings::Settings(const unsigned int p_Style, const bool p_Minimized, const bool p_Hidden) :
            style(p_Style),
            minimized(p_Minimized),
            hidden(p_Hidden)
        {

        }
        WindowBase::Settings::Settings(const bool p_Minimized, const bool p_Hidden, const unsigned int p_Style) :
            style(p_Style),
            minimized(p_Minimized),
            hidden(p_Hidden)
        {

        }

        void WindowBase::Update()
        {
            m_pImpl->Update();
        }

    }

}