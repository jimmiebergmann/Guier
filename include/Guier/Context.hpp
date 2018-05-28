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


#include <Guier/Core/ContextBase.hpp>

namespace Guier
{

    class Window;

    /**
    * The Guier Context is the very core of the library.
    * Create one or more contexts per application.
    * Added objects are owned by context and deleted when the context is unallocated.
    * The context class handles window management, skins, rendering, inputs, etc...
    *
    */
    class GUIER_API Context : public Core::ContextBase
    {

    public:

        /**
        * Constructor.  
        *
        */
        Context(const bool autoTick = true);
        Context(Renderer * renderer, Skin * skin = nullptr, const bool autoTick = true);
        Context(Skin * skin, Renderer * renderer = nullptr, const bool autoTick = true);

        /**
        * Destructor.
        *
        */
        ~Context();

        /**
        * Add window to context.
        *
        * @throw std::runtime_error     If window == nullptr.
        *
        */
        //bool Add(Window * window);

        /**
        * Add new window to context.
        * The window is now shown until calling Show() of window.
        *
        */
       /* template<typename Type, class... Args>
        std::shared_ptr<Window> Add(Args &&... args);

        /**
        * Remove window from context.
        *
        * @brief    The window is unallocating when removed.
        *
        */
       // Context & Remove(std::shared_ptr<Window> window);*/

    };

    // Include inline implementations. 
   // #include <Guier/Core/Context.inl>

}