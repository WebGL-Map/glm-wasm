/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Tyler Bucher
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef GLM_WASM_TEXTUREPACK_H
#define GLM_WASM_TEXTUREPACK_H

#include "../../Camera.h"
#include "../../server/world/Chunk.h"

namespace glmwasm {

    /**
     * Represents a texture pack for this map.
     *
     * @author Tyler Bucher
     */
    class TexturePack {
    public:

        /**
         * Initializes this texture pack.
         */
        virtual void init() = 0;

        /**
         * Creates a block to be rendered.
         *
         * @param blockType the type of this block.
         * @param x the x position of the block.
         * @param y the y position of the block.
         * @param z the z position of the block.
         *
         * @return the pointer to the newly created block.
         */
        virtual Block *createBlock(BlockType *blockType, int x, int y, int z) = 0;

        /**
         * Creates a new chunk at the given position.
         *
         * @param x the x position of the chunk.
         * @param y the y position of the chunk.
         * @param z the z position of the chunk.
         *
         * @return the newly created chunk.
         */
        virtual Chunk *createChunk(int x, int y, int z) = 0;

        /**
         * Renders some amount of blocks.
         *
         * @param camera the camera to use as a delimiter.
         * @param chunkMap the map of chunks to get data from.
         */
        virtual void renderBlocks(Camera &camera, const std::map<int, std::map<int, Chunk *>> &chunkMap) = 0;
    };
}

#endif //GLM_WASM_TEXTUREPACK_H
