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

#include <Guier/Skin.hpp>
#include <Guier/Control.hpp>

namespace Guier
{

    Skin::Skin() :
        m_pParentRoot(nullptr),
        m_Loaded(false)
    {

    }

    Skin::~Skin()
    {

    }

    void Skin::set(const unsigned int item, const unsigned int state, Bitmap * bitmap, const Vector2i & position, const Vector2i & size)
    {
        ChunkItems * pItems = nullptr;

        // Create state if not found.
        auto itStates = m_ChunkStates.find(state);
        if (itStates == m_ChunkStates.end())
        {
            pItems = new ChunkItems;
            m_ChunkStates.insert({state, pItems});
        }
        else
        {
            pItems = itStates->second;
        }

        // Find bitmap
        Core::Texture * pTexture = nullptr;
        auto itBitmap = m_Bitmaps.find(bitmap);
        if (itBitmap == m_Bitmaps.end())
        {
            if (m_pParentRoot)
            {
                pTexture = m_pParentRoot->createTexture(bitmap);
            }
            m_Bitmaps.insert({bitmap, pTexture }).first;
        }
        else
        {
            pTexture = itBitmap->second;
        }

        // Find item.
        auto itItems = pItems->find(item);
        if (itItems != pItems->end())
        {
            Chunk * pChunk = itItems->second;
            delete pChunk;
        }
        
        Chunk * pChunk = new Chunk1x1(bitmap, pTexture, position, size);
        if (pTexture == nullptr)
        {
            addChunkToTextureLoading(bitmap, pChunk);
        }

        pItems->insert({ item, pChunk });
    }

    void Skin::set(const unsigned int item, const unsigned int state, Bitmap * bitmap,
        const Vector2i & leftTopPos, const Vector2i & leftTopSize, const Vector2i & rightBottomPos, const Vector2i & rightBottomSize)
    {
        ChunkItems * pItems = nullptr;

        // Create state if not found.
        auto itStates = m_ChunkStates.find(state);
        if (itStates == m_ChunkStates.end())
        {
            pItems = new ChunkItems;
            m_ChunkStates.insert({ state, pItems });
        }
        else
        {
            pItems = itStates->second;
        }

        // Find bitmap
        Core::Texture * pTexture = nullptr;
        auto itBitmap = m_Bitmaps.find(bitmap);
        if (itBitmap == m_Bitmaps.end())
        {
            if (m_pParentRoot)
            {
                pTexture = m_pParentRoot->createTexture(bitmap);
            }
            m_Bitmaps.insert({ bitmap, pTexture }).first;
        }
        else
        {
            pTexture = itBitmap->second;
        }

        // Find item.
        auto itItems = pItems->find(item);
        if (itItems != pItems->end())
        {
            Chunk * pChunk = itItems->second;
            delete pChunk;
        }

        Chunk * pChunk = new Chunk3x3(bitmap, pTexture, leftTopPos, leftTopSize, rightBottomPos, rightBottomSize);
        if (pTexture == nullptr)
        {
            addChunkToTextureLoading(bitmap, pChunk);
        }
        pItems->insert({ item, pChunk });
    }

    bool Skin::unset(const unsigned int item, const unsigned int state)
    {
        // Find chunk
        auto it = m_ChunkStates.find(state);
        if (it != m_ChunkStates.end())
        {
            ChunkItems * pChunkitems = it->second;

            auto it2 = pChunkitems->find(item);
            if (it2 != pChunkitems->end())
            {
                Chunk * pChunk = it2->second;
                removeChunkTFromTextureLoading(pChunk);
                delete pChunk;
                pChunkitems->erase(it2);
                
                if (pChunkitems->size() == 0)
                {
                    delete pChunkitems;
                    m_ChunkStates.erase(it);
                }

                return true;
            }
        }

        return false;
    }

    bool Skin::update(const unsigned int item, const unsigned int state, const Vector2i & position, const Vector2i & size)
    {
        throw std::runtime_error("Update function for Skin class is not yet implemented.");

        return false;
    }

    bool Skin::update(const unsigned int item, const unsigned int state, const Vector2i & leftTopPos, const Vector2i & leftTopSize, const Vector2i & rightBottomPos, const Vector2i & rightBottomSize)
    {
        throw std::runtime_error("Update function for Skin class is not yet implemented.");

        return false;
    }

    void Skin::load()
    {
        if (m_pParentRoot == nullptr)
        {
            throw std::runtime_error("Cannot load skin of unkown parent.");
        }

        if (m_Loaded)
        {
            return;
        }
        m_Loaded = true;

        for (auto itBitmap = m_TextureLoading.begin(); itBitmap != m_TextureLoading.end(); itBitmap++)
        {
            Bitmap * pBitmap = itBitmap->first;
            ChunkSet * pChunkSet = itBitmap->second;

            // Create texture
            Core::Texture * pTexture = m_pParentRoot->createTexture(pBitmap);

            // Set texture in bitmap map.
            auto itBitMapTextures = m_Bitmaps.find(pBitmap);
            if (itBitMapTextures == m_Bitmaps.end())
            {
                throw std::runtime_error("Trying to load missing texture.");
            }
            itBitMapTextures->second = pTexture;

            // Set texture for each chunk.
            for (auto itChunk = pChunkSet->begin(); itChunk != pChunkSet->end(); itChunk++)
            {
                Chunk * pChunk = *itChunk;
                pChunk->texture(pTexture);
            }
        }
    }

    Skin::Chunk * Skin::getChunk(const unsigned int item, const unsigned int state)
    {
        // Find chunk
        auto it = m_ChunkStates.find(state);
        if (it != m_ChunkStates.end())
        {
            ChunkItems * chunitems = it->second;

            auto it2 = chunitems->find(item);
            if (it2 != chunitems->end())
            {
                return it2->second;
            }
        }

        return nullptr;
    }

    void Skin::addChunkToTextureLoading(Bitmap * bitmap, Chunk * chunk)
    {
        ChunkSet * pChunkSet = nullptr;

        auto itBitmap = m_TextureLoading.find(bitmap);
        if (itBitmap == m_TextureLoading.end())
        {
            pChunkSet = new ChunkSet;
            m_TextureLoading.insert({bitmap, pChunkSet});
        }
        else
        {
            pChunkSet = itBitmap->second;
        }

        pChunkSet->insert(chunk);
    }

    void Skin::removeChunkTFromTextureLoading(Chunk * chunk)
    {
        Bitmap * pBitmap = chunk->bitmap();

        auto itBitmap = m_TextureLoading.find(pBitmap);
        if (itBitmap == m_TextureLoading.end())
        {
            return;
        }

        ChunkSet * pChunkSet = itBitmap->second;

        auto itChunk = pChunkSet->find(chunk);
        if (itChunk == pChunkSet->end())
        {
            return;
        }

        pChunkSet->erase(itChunk);
    }
  


    // Chunk class.
    Skin::Chunk::Chunk(Bitmap * bitmap_in, Core::Texture * texture_in) :
        m_pBitmap(bitmap_in),
        m_pTexture(texture_in)
    {
    }

    Skin::Chunk::~Chunk()
    {

    }

    Core::Texture * Skin::Chunk::texture() const
    {
        return m_pTexture;
    }
    void Skin::Chunk::texture(Core::Texture * texture_in)
    {
        m_pTexture = texture_in;
    }

    Bitmap * Skin::Chunk::bitmap() const
    {
        return m_pBitmap;
    }

    void Skin::Chunk::bitmap(Bitmap * bitmap_in)
    {
        m_pBitmap = bitmap_in;
    }


    // Chunk 1x1 class.
    Skin::Chunk1x1::Chunk1x1(Bitmap * bitmap_in, Core::Texture * texture_in,
                             const Vector2i & position, const Vector2i & size) :
        Chunk(bitmap_in, texture_in),
        m_TextureCoords{ position, size }
    {

    }

    Skin::Chunk::Type Skin::Chunk1x1::type() const
    {
        return Type::Chunk1x1;
    }

    void Skin::Chunk1x1::render(Core::Renderer::Interface * rendererInterface, const Vector2i & position, const Vector2i & size)
    {
        rendererInterface->renderRectangle(position, size, m_pTexture);
    }

    // Chunk 3x3 class.
    Skin::Chunk3x3::Chunk3x3(Bitmap * bitmap_in, Core::Texture * texture_in,
                             const Vector2i & leftTopPos, const Vector2i & leftTopSize,
                             const Vector2i & rightBottomPos, const Vector2i & rightBottomSize) :
        Chunk(bitmap_in, texture_in),
        m_TextureCoords{ leftTopPos, leftTopSize, rightBottomPos, rightBottomSize }
    {

    }

    Skin::Chunk::Type Skin::Chunk3x3::type() const
    {
        return Type::Chunk3x3;
    }

    void Skin::Chunk3x3::render(Core::Renderer::Interface * rendererInterface, const Vector2i & position, const Vector2i & size)
    {
        rendererInterface->renderRectangle(position, size, m_pTexture);
    }

}