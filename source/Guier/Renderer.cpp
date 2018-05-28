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

#include <Guier/Renderer.hpp>

#if GUIER_DEFAULT_RENDERER == GUIER_RENDERER_OPENGL
#include <Guier/Renderers/OpenGL/OpenGLRenderer.hpp>
#endif

namespace Guier
{

    Renderer::~Renderer()
    {

    }

    Renderer * Renderer::CreateDefaultRenderer()
    {
        #if GUIER_DEFAULT_RENDERER == GUIER_RENDERER_OPENGL
             return new Renderers::OpenGLRenderer;
        #else
            throw std::runtime_error("Missing default renderer.");
        #endif;

        return nullptr;
    }

    Renderer::Renderer()
    {

    }
}