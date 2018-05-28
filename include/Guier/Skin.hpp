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

#include <Guier/Control.hpp>
#include <map>

namespace Guier
{

    /**
    * Forward declaratios.
    *
    */
    class Renderer;
    namespace Core
    {
        class Texture;
    }


    /**
    * Base class of skin.
    *
    * @brief All skins should inherit this class.
    *
    */
    class GUIER_API Skin
    {

    public:

        /**
        * Constructor.
        *
        */
        Skin();

        /**
        * Virtual destructor.
        *
        */
        virtual ~Skin();

        /**
        * Enumerator of skin items.
        *
        */
        enum class Item : unsigned int
        {
            Button,
            TextInput,
            Window,
            WindowButtonMinimize,
            WindowButtonMaximize,
            WindowButtonClose,

            ItemCount               ///< Any index equal or larger than ItemCount is a custom item.
        };

        /**
        * Enumerator of item types.
        *
        */
        enum class State : unsigned int
        {
            Normal,                 ///< The normal appearance of an item.
            Disabled,               ///< Disabled state. Often indicated in gray color.
            Hovering,               ///< Appearance of an item being hovered.
            Clicked,                ///< Appearance of a clicked item.

            TypeCount               ///< Any index equal or larger than TypeCount is a custom state.
        };


        /**
        * Set control dimensions.
        *
        * @param item   Id of item.
        * @param state  Id of state.
        *
        */
        void SetChunk(const unsigned int item, const unsigned int state,
            const Vector2i & position, const Vector2i & size);

        void SetChunk(const unsigned int item, const unsigned int state,
            const Vector2i & leftTopPos, const Vector2i & leftTopSize, const Vector2i & RightBottomPos, const Vector2i & RightBottomSize);

        /**
        * Create default skin.
        *
        * @return Pointer to allocated default skin.
        *
        * @throw std::runtime_error If there is no default skin available.
        *
        */
        static Skin * CreateDefaultSkin();

    private:

        class Chunk;
        typedef std::map<unsigned int, Chunk *> ChunkState;         ///< Map of chunk items, item id as key.
        typedef std::map<unsigned int, ChunkState *> Chunks;   ///< Map of chunk states, state id as key.

        Chunks m_Chunks;

        /**
        * Internal function for creating or getting chunk state map.
        *
        */
        ChunkState * GetItemState(const unsigned int state);


        /**
        * Internal base class of chunk.
        *
        */
        class Chunk
        {

        public:

            virtual ~Chunk();

            virtual void Render(Renderer * renderer, const Vector2i & position, const Vector2i & Size) = 0;

        };

        /**
        * Chunk class for dimension of 3x3 chunks.
        *
        */
        class Chunk3x3 : public Chunk
        {

        public:

            Chunk3x3(const Vector2i & leftTopPos, const Vector2i & leftTopSize,
                const Vector2i & RightBottomPos, const Vector2i & RightBottomSize);

            virtual void Render(Renderer * renderer, const Vector2i & position, const Vector2i & Size);

        private:

            const Vector2i m_TextureCoords[4];

        };

        /**
        * Chunk class for dimension of 1x1 chunks.
        *
        */
        class Chunk1x1 : public Chunk
        {

        public:

            Chunk1x1(const Vector2i & position, const Vector2i & size);

            virtual void Render(Renderer * renderer, const Vector2i & position, const Vector2i & Size);

        private:

            const Vector2i m_TextureCoords[2];

        };

    };

}