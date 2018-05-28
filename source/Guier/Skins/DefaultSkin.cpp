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

#include <Guier/Skins/DefaultSkin.hpp>

namespace Guier
{

    namespace Skins
    {

        DefaultSkin::DefaultSkin()
        {
            SetChunk(static_cast<unsigned int>(Item::Button), static_cast<unsigned int>(State::Normal),
                Vector2i(0, 0), Vector2i(2, 2), Vector2i(6, 6), Vector2i(2, 2));

            SetChunk(static_cast<unsigned int>(Item::TextInput), static_cast<unsigned int>(State::Normal),
                Vector2i(10, 0), Vector2i(2, 2), Vector2i(19, 6), Vector2i(2, 2));
        }

        DefaultSkin::~DefaultSkin()
        {

        }

    }
}