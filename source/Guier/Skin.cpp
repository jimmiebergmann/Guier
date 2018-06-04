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

#if GUIER_DEFAULT_RENDERER == GUIER_RENDERER_OPENGL
#include <Guier/Skins/DefaultSkin.hpp>
#endif

namespace Guier
{

    Skin::Skin()
    {

    }

    Skin::~Skin()
    {

    }

    bool Skin::SetChunk(const unsigned int item, const unsigned int state, const Vector2i & position, const Vector2i & size)
    {
        auto it = m_Chunks.find(state);
        if (it != m_Chunks.end())
        {
            ChunkState * pChunkState = it->second;

            auto it2 = pChunkState->find(item);
            if (it2 != pChunkState->end())
            {
                Chunk * pChunk = it2->second;
                Core::Texture * pTexture = pChunk->texture();
                delete pChunk;
                pChunkState->insert({ item, new Chunk1x1(pTexture, position, size) });

                return true;
            }
        }

        return false;
    }

    bool Skin::SetChunk(const unsigned int item, const unsigned int state, Bitmap * bitmap, const Vector2i & position, const Vector2i & size)
    {
        // Create item if unkown.
        auto it = m_Chunks.find(state);
        if (it == m_Chunks.end())
        {
            ChunkState * pNewState = new ChunkState;
            m_Chunks.insert({ state, pNewState });
            return pNewState;
        }

        // Find texture, or create one.
        Core::Texture * pTexture = nullptr;
        auto btIt = m_BitmapTextures.find(bitmap);
        if (btIt != m_BitmapTextures.end())
        {
            pTexture = btIt->second;
        }
        else
        {
            //pTexture = new Core::Texture
        }

        

       /* ChunkState * pChunkState = GetOrCreateItemState(state);

        auto it = pChunkState->find(item);
        if (it != pChunkState->end())
        {
            delete it->second;
            pChunkState->erase(it);
        }

        pChunkState->insert({ item, new Chunk1x1(nullptr, position, size) });*/

        return false;
    }

    bool Skin::SetChunk(const unsigned int item, const unsigned int state,
        const Vector2i & leftTopPos, const Vector2i & leftTopSize, const Vector2i & RightBottomPos, const Vector2i & RightBottomSize)
    {
        /*ChunkState * pChunkState = GetOrCreateItemState(state);

        auto it = pChunkState->find(item);
        if (it != pChunkState->end())
        {
            delete it->second;
            pChunkState->erase(it);
        }

        pChunkState->insert({ item, new Chunk3x3(nullptr, leftTopPos, leftTopSize, RightBottomPos, RightBottomSize) });*/

        return false;
    }

    bool Skin::SetChunk(const unsigned int item, const unsigned int state, Bitmap * bitmap,
        const Vector2i & leftTopPos, const Vector2i & leftTopSize, const Vector2i & RightBottomPos, const Vector2i & RightBottomSize)
    {
        return false;
    }

    bool Skin::UnsetChunk(const unsigned int item, const unsigned int state)
    {
        // Find chunk
        auto it = m_Chunks.find(state);
        if (it != m_Chunks.end())
        {
            ChunkState * pChunkState = it->second;

            auto it2 = pChunkState->find(state);
            if (it2 != pChunkState->end())
            {
                Chunk * pChunk = it2->second;
                delete pChunk;
                pChunkState->erase(it2);
                
                if (pChunkState->size() == 0)
                {
                    delete pChunkState;
                    m_Chunks.erase(it);
                }

                return true;
            }
        }

        return false;
    }

    Skin::Chunk * Skin::GetChunk(const unsigned int item, const unsigned int state)
    {
        // Find chunk
        auto it = m_Chunks.find(state);
        if (it != m_Chunks.end())
        {
            ChunkState * chunkState = it->second;

            auto it2 = chunkState->find(state);
            if (it2 != chunkState->end())
            {
                return it2->second;
            }
        }

        return nullptr;
    }

   /* Skin::ChunkState * Skin::GetOrCreateItemState(const unsigned int state)
    {
        // Create item if unkown.
        auto it = m_Chunks.find(state);
        if (it == m_Chunks.end())
        {
            ChunkState * pNewState = new ChunkState;
            m_Chunks.insert({state, pNewState });
            return pNewState;
        }

        return it->second;
    }*/


    Skin::Chunk::Chunk(Core::Texture * texture) :
        m_pTexture(texture)
    {
    }

    Skin::Chunk::~Chunk()
    {

    }

    Core::Texture * Skin::Chunk::texture() const
    {
        return m_pTexture;
    }
    void Skin::Chunk::texture(Core::Texture * texture)
    {
        m_pTexture = texture;
    }

    Skin::Chunk3x3::Chunk3x3(Core::Texture * texture, const Vector2i & leftTopPos, const Vector2i & leftTopSize,
        const Vector2i & RightBottomPos, const Vector2i & RightBottomSize) :
        Chunk(texture)
    {

    }

    void Skin::Chunk3x3::Render(Core::Renderer::Interface * rendererInterface, const Vector2i & position, const Vector2i & size)
    {
        rendererInterface->RenderRectangle(position, size, Color::Green);
    }

    Skin::Chunk1x1::Chunk1x1(Core::Texture * texture, const Vector2i & position, const Vector2i & size) :
        Chunk(texture)
    {

    }

    void Skin::Chunk1x1::Render(Core::Renderer::Interface * rendererInterface, const Vector2i & position, const Vector2i & size)
    {
        rendererInterface->RenderRectangle(position, size, Color::Blue);
    }

}