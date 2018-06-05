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
#include <Guier/Bitmap.hpp>
#include <Guier/Core/Renderer.hpp>
#include <map>
#include <set>

namespace Guier
{

    /**
    * Forward declaratios.
    *
    */
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
        ** @brief Set or update existing chunk dimensions.
        *
        *
        * @param item       Id of item.
        * @param state      Id of state.
        * @param texture    Pointer to texture. The skin
        * 
        * @return False if not passing any texture and the chunk is not yet set.
        *         False if bitmap == nullptr,
        *         else false.
        *
        */
        bool SetChunk(const unsigned int item, const unsigned int state, const Vector2i & position, const Vector2i & size);
        bool SetChunk(const unsigned int item, const unsigned int state, Bitmap * bitmap, const Vector2i & position, const Vector2i & size);
        bool SetChunk(const unsigned int item, const unsigned int state, const Vector2i & leftTopPos, const Vector2i & leftTopSize, const Vector2i & RightBottomPos, const Vector2i & RightBottomSize);
        bool SetChunk(const unsigned int item, const unsigned int state, Bitmap * bitmap, const Vector2i & leftTopPos, const Vector2i & leftTopSize, const Vector2i & RightBottomPos, const Vector2i & RightBottomSize);

        /**
        * Set control dimensions.
        *
        * @param item   Chunk item id to remove from skin.
        * @param state  Chunk items state id to remove from skin.
        *
        * @return true if removed, false if item-state is not found in skin.
        *
        */
        bool UnsetChunk(const unsigned int item, const unsigned int state);

    private:

        /**
        * Skin chunk class.
        *
        * @param Controller's skinning information are stored in chunks.
        *
        */
        class Chunk
        {

        public:

            Chunk(Core::Texture * texture);

            virtual ~Chunk();

            virtual void Render(Core::Renderer::Interface * rendererInterface, const Vector2i & position, const Vector2i & size) = 0;

            /**
            * Get or set texture.
            *
            */
            Core::Texture * texture() const;
            void texture(Core::Texture * texture);

        private:

            Core::Texture * m_pTexture;

        };

        /**
        * Get chunk.
        *
        * @return   Pointer of chunk if found or if default skin is available, else nullptr.
        *
        */
        Skin::Chunk * GetChunk(const unsigned int item, const unsigned int state);

        typedef std::map<unsigned int, Chunk *> ChunkState;     ///< Map of chunk items, item id as key.
        typedef std::map<unsigned int, ChunkState *> Chunks;    ///< Map of chunk states, state id as key.

        Chunks                              m_Chunks;                   ///< All the chunks of .... PLEASE FIX THE NAMING OF ChunkState AND Chunks...
        std::map<Bitmap *, Core::Texture *> m_BitmapTextures;

        /**
        * Internal function for creating or getting chunk state map.
        *
        */
 ///       ChunkState * GetOrCreateItemState(const unsigned int state);

        friend class Core::Renderer::Interface;

        /**
        * Chunk class for dimension of 3x3 chunks.
        *
        */
        class Chunk3x3 : public Chunk
        {

        public:

            Chunk3x3(Core::Texture * texture,
                const Vector2i & leftTopPos, const Vector2i & leftTopSize,
                const Vector2i & RightBottomPos, const Vector2i & RightBottomSize);

            virtual void Render(Core::Renderer::Interface * rendererInterface, const Vector2i & position, const Vector2i & size);

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

            Chunk1x1(Core::Texture * texture, const Vector2i & position, const Vector2i & size);

            virtual void Render(Core::Renderer::Interface * rendererInterface, const Vector2i & position, const Vector2i & size);

        private:

            const Vector2i m_TextureCoords[2];

        };

    };

}