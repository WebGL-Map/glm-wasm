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
#ifndef GLM_WASM_BLOCKTYPE_H
#define GLM_WASM_BLOCKTYPE_H

#include <string>

namespace glmwasm {

    /**
     * Defines a type of block weather it be for a mod or for native minecraft.
     *
     * @author Tyler Bucher
     */
    class BlockType {
    private:

        /**
         * The id of the mod or base minecraft.
         */
        const std::string *modId;

        /**
         * The name or id of the block for the modId.
         */
        const std::string *blockId;

    public:

        /**
         * Creates a BlockType by passing a point of the values.
         *
         * @param modId pointer to the location of the id of the mod.
         * @param blockId pointer to the location of the id of the block.
         */
        BlockType(const std::string *modId, const std::string *blockId);

        /**
         * @return the id of the mod or base minecraft.
         */
        const std::string *getModId() const;

        /**
         * @return the name or id of the block for the modId.
         */
        const std::string *getBlockId() const;

        /**
         * This operator should only return true if the modId and blockId of both parameters equal.
         *
         * @param b the compared block type.
         *
         * @return true if the modId and blockId of both parameters equal.
         */
        bool operator==(const BlockType &b) const;

        /**
         * Removes the block type.
         */
        virtual ~BlockType();
    };
}

#endif //GLM_WASM_BLOCKTYPE_H
