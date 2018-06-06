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
    class ParentRoot;
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
        ** Set or update existing chunk dimensions.
        *
        * @brief            The chunk is updated with the new bitmap if the chunk exists.
        *                   
        *
        *
        * @param item       Id of item.
        * @param state      Id of state.
        * @param texture    Pointer to texture. The skin
        * 
        * @return           True if new chunk is set or existing chunk is updated. 
        *
        */
        void set(const unsigned int item, const unsigned int state, Bitmap * bitmap, const Vector2i & position, const Vector2i & size);
        void set(const unsigned int item, const unsigned int state, Bitmap * bitmap, const Vector2i & leftTopPos, const Vector2i & leftTopSize, const Vector2i & rightBottomPos, const Vector2i & rightBottomSize);

        /**
        * Set control dimensions.
        *
        * @param item   Chunk item id to remove from skin.
        * @param state  Chunk items state id to remove from skin.
        *
        * @return true if unset, false if chunk is not found.
        *
        */
        bool unset(const unsigned int item, const unsigned int state);

        /**
        * Update existing chunk dimensions.
        *
        * @param item   Chunk item id to update.
        * @param state  Chunk items state id to update.
        *
        * @return       True if updates, false if chunk is not found.
        *
        */
        bool update(const unsigned int item, const unsigned int state, const Vector2i & position, const Vector2i & size);
        bool update(const unsigned int item, const unsigned int state, const Vector2i & leftTopPos, const Vector2i & leftTopSize, const Vector2i & rightBottomPos, const Vector2i & rightBottomSize);
        

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

            enum class Type
            {
                Chunk1x1,
                Chunk3x3
            };

            Chunk(Bitmap * bitmap, Core::Texture * texture);

            virtual ~Chunk();

            virtual Type type() const = 0;
            virtual void render(Core::Renderer::Interface * rendererInterface, const Vector2i & position, const Vector2i & size) = 0;

            /**
            * Get or set texture.
            *
            */
            Core::Texture * texture() const;
            void texture(Core::Texture * texture);

            /**
            * Get or set bitmap.
            *
            */
            Bitmap * bitmap() const;
            void bitmap(Bitmap * bitmap);

        protected:

            Core::Texture * m_pTexture;
            Bitmap * m_pBitmap;

        };

        /**
        * Chunk class for dimension of 1x1 chunks.
        *
        */
        class Chunk1x1 : public Chunk
        {

        public:

            Chunk1x1(Bitmap * bitmap, Core::Texture * texture, const Vector2i & position, const Vector2i & size);

            Type type() const;
            void render(Core::Renderer::Interface * rendererInterface, const Vector2i & position, const Vector2i & size);

        private:

            const Vector2i m_TextureCoords[2];

        };

        /**
        * Chunk class for dimension of 3x3 chunks.
        *
        */
        class Chunk3x3 : public Chunk
        {

        public:

            Chunk3x3(Bitmap * bitmap, Core::Texture * texture,
                const Vector2i & leftTopPos, const Vector2i & leftTopSize,
                const Vector2i & rightBottomPos, const Vector2i & rightBottomSize);

            Type type() const;
            void render(Core::Renderer::Interface * rendererInterface, const Vector2i & position, const Vector2i & size);

        private:

            const Vector2i m_TextureCoords[4];

        };

        /**
        * Load textures.
        *
        * @throw std::runtime_error if parent root of this skin is not yet set.
        *
        */
    public:
        void load();
    private:
        /**
        * Get chunk.
        *
        * @return   Pointer of chunk if found, else nullptr.
        *
        */
        Skin::Chunk * getChunk(const unsigned int item, const unsigned int state);

        /**
        * Add chunk to load map.
        *
        */
        void addChunkToTextureLoading(Bitmap * bitmap, Chunk * chunk);

        /**
        * Remove chunk from load map.
        *
        */
        void removeChunkTFromTextureLoading(Chunk * chunk);

        typedef std::map<unsigned int, Chunk *> ChunkItems;          ///< Map of chunk items, item id as key.
        typedef std::map<unsigned int, ChunkItems *> ChunkStates;    ///< Map of chunk states, state id as key.

        ChunkStates                         m_ChunkStates;           ///< All the chunks.
        std::map<Bitmap *, Core::Texture *> m_Bitmaps;               ///< Map of bitmap and corresonding texture.
        ParentRoot *                        m_pParentRoot;           ///< Parent root,


        typedef std::set<Chunk *>           ChunkSet;
        std::map<Bitmap *, ChunkSet*>       m_TextureLoading;       ///< Map of bitmaps without any corresonding textures.
                                                                    ///< Secondary is the chunk the bitmap is attached to.
        bool                                m_Loaded;

        friend class ParentRoot;
        friend class Core::Renderer::Interface;
        
    };

}