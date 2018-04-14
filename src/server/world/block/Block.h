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
#ifndef GLM_WASM_BLOCK_H
#define GLM_WASM_BLOCK_H

#include <vector>
#include "BlockType.h"
#include "BlockTrait.h"

namespace glmwasm {

    /**
     * Describes a 2d or a 3d block.
     *
     * @author Tyler Bucher
     */
    class Block {
    private:

        /**
         * The type of this block. This field usually helps describe how this block should be rendered.
         */
        BlockType *blockType;

        /**
         * Traits which define this block. Such as color.
         */
        std::vector<BlockTrait *> blockTraits;

    public:

        /**
         * The x position of this block.
         */
        int x = 0;

        /**
         * The y position of this block.
         */
        int y = 0;

        /**
         * The z position of this block.
         */
        int z = 0;

        /**
         * Creates a new block with a block type parameter. This constructor places this block at 0, 0, 0.
         *
         * @param blockType the type of this block.
         */
        explicit Block(BlockType *blockType);

        /**
         * Creates a new block at a position with a block type parameter.
         *
         * @param blockType the type of this block.
         * @param x the x position of this block.
         * @param y the y position of this block.
         * @param z the z position of this block.
         */
        Block(BlockType *blockType, int x, int y, int z);

        /**
         * @return the type of this block. This field usually helps describe how this block should be rendered.
         */
        glmwasm::BlockType *getBlockType() const;

        /**
         * @param blockType the new block type to set.
         */
        void setBlockType(BlockType *blockType);

        /**
         * @return traits which define this block. Such as color.
         */
        std::vector<BlockTrait *> &getBlockTraits();

        /**
         * Return true if the blockTraits vector contains the trait to check.
         *
         * @param trait the trait to check.
         *
         * @return true if the blockTraits vector contains the trait to check.
         */
        bool containsTrait(BlockTrait *trait) const;

        /**
         * Adds a trait to the blockTraits vector.
         *
         * @param trait the trait to add.
         *
         * @return true if the trait was added false otherwise.
         */
        bool addTrait(BlockTrait *trait);

        /**
         * Removes this object.
         */
        virtual ~Block();
    };
}

#endif //GLM_WASM_BLOCK_H
