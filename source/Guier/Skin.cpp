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

    void Skin::SetChunk(const unsigned int item, const unsigned int state,
        const Vector2i & position, const Vector2i & size)
    {
        ChunkState * pChunkState = GetItemState(state);

        auto it = pChunkState->find(item);
        if (it != pChunkState->end())
        {
            delete it->second;
            pChunkState->erase(it);
        }

        pChunkState->insert({ item, new Chunk1x1(position, size) });
    }

    void Skin::SetChunk(const unsigned int item, const unsigned int state,
        const Vector2i & leftTopPos, const Vector2i & leftTopSize, const Vector2i & RightBottomPos, const Vector2i & RightBottomSize)
    {
        ChunkState * pChunkState = GetItemState(state);

        auto it = pChunkState->find(item);
        if (it != pChunkState->end())
        {
            delete it->second;
            pChunkState->erase(it);
        }

        pChunkState->insert({ item, new Chunk3x3(leftTopPos, leftTopSize, RightBottomPos, RightBottomSize) });
    }

    Skin * Skin::CreateDefaultSkin()
    {
        #if defined(GUIER_DEFAULT_SKIN)
            return new Skins::DefaultSkin;
        #else
            throw std::runtime_error("Missing default skin.");
        #endif;

        return nullptr;
    }

    Skin::ChunkState * Skin::GetItemState(const unsigned int state)
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
    }

    Skin::Chunk::~Chunk()
    {

    }

    Skin::Chunk3x3::Chunk3x3(const Vector2i & leftTopPos, const Vector2i & leftTopSize,
        const Vector2i & RightBottomPos, const Vector2i & RightBottomSize)
    {

    }

    void Skin::Chunk3x3::Render(Renderer * renderer, const Vector2i & position, const Vector2i & Size)
    {

    }

    Skin::Chunk1x1::Chunk1x1(const Vector2i & position, const Vector2i & size)
    {

    }

    void Skin::Chunk1x1::Render(Renderer * renderer, const Vector2i & position, const Vector2i & Size)
    {

    }

}