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
#ifndef GLM_WASM_TWODBLOCK_H
#define GLM_WASM_TWODBLOCK_H

#include "../../../api/Renderable.h"
#include "../../../../server/world/block/Block.h"

namespace glmwasm {

    /**
     * Represents a graphically 2d block.
     *
     * @author Tyler Bucher
     */
    class TwoDBlock : public Block, public Renderable {
    private:

        /**
         * The vertex data.
         */
        int vertexData[18];

        /**
         * The gl handle id.
         */
        unsigned int vertexHandler;

        /**
         * The color data.
         */
        float colorData[16];

        /**
         * The gl handle id.
         */
        unsigned int colorHandler;

    public:

        /**
         * Creates a new block at a position with a block type parameter.
         *
         * @param blockType the type of this block.
         * @param x the x position of this block.
         * @param y the y position of this block.
         * @param z the z position of this block.
         */
        TwoDBlock(BlockType *blockType, int x, int y, int z);

        /**
         * Renders this object.
         */
        void render() override;

        /**
         * Removes this block
         */
        ~TwoDBlock() override;
    };
}

#endif //GLM_WASM_TWODBLOCK_H
