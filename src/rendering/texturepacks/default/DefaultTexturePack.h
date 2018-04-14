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
#ifndef GLM_WASM_DEFAULTTEXTUREPACK_H
#define GLM_WASM_DEFAULTTEXTUREPACK_H

#include "../../api/TexturePack.h"
#include "../../../server/world/block/Block.h"

namespace glmwasm {

    /**
     * Represents a texture pack for this map.
     *
     * @author Tyler Bucher
     */
    class DefaultTexturePack : public TexturePack {
    public:

        /**
         * Default constructor.
         */
        DefaultTexturePack();

        /**
         * Gets the chunks to be d
         *
         * @param position the position of the camera.
         * @param aspectRatio the aspect ratio of the camera.
         * @param fov the fov of the camera.
         * @param range the set range.
         */
        static void targetChunkRangeFor2d(const glm::vec3 &position, float aspectRatio, float fov, int *range);

        /**
         * Initializes this texture pack.
         */
        void init() override;

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
        Block *createBlock(BlockType *blockType, int x, int y, int z) override;

        /**
         * Creates a new chunk at the given position.
         *
         * @param x the x position of the chunk.
         * @param y the y position of the chunk.
         * @param z the z position of the chunk.
         *
         * @return the newly created chunk.
         */
        Chunk *createChunk(int x, int y, int z) override;

        /**
         * Renders some amount of blocks.
         *
         * @param camera the camera to use as a delimiter.
         * @param chunkMap the map of chunks to get data from.
         */
        void renderBlocks(Camera &camera, const std::map<int, std::map<int, Chunk *>> &chunkMap) override;

        /**
         * Removes this texture pack.
         */
        virtual ~DefaultTexturePack();
    };
}

#endif //GLM_WASM_DEFAULTTEXTUREPACK_H
