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
#ifndef GLM_WASM_DATAMANAGER_H
#define GLM_WASM_DATAMANAGER_H

#include <string>
#include <map>
#include <vector>
#include "server/world/block/BlockType.h"
#include "server/world/block/BlockTrait.h"

namespace glmwasm {

    /**
     * Holds global data to reduce memory.
     */
    class DataManager {
    private:

        /**
         * The list of available block types for this server.
         */
        static std::vector<glmwasm::BlockType *> blockTypes;

        /**
         * The list of block traits for all blocks.
         */
        static std::vector<BlockTrait *> blockTraits;

    public:

        /**
         * @return the list of available block types for this server.
         */
        static std::vector<BlockType *> &getBlockTypes();

        /**
         * @return the list of block traits for all blocks.
         */
        static std::vector<BlockTrait *> &getBlockTraits();

        /**
         * Attempts to add a new block type to the vector. Does not add duplicates.
         *
         * @param modId the id of the mod.
         * @param blockId the id of the block.
         *
         * @return true if the block type was added false otherwise.
         */
        static bool addBlockType(std::string *modId, std::string *blockId);

        /**
         * Attempts to get and or add a new block type to the vector. Does not add duplicates.
         *
         * @param modId the id of the mod.
         * @param blockId the id of the block.
         *
         * @return the fetched or newly added block type.
         */
        static std::pair<BlockType*, bool> getAndOrAddBlockType(std::string *modId, std::string *blockId);

        /**
         * Removes and de-allocates all block types.
         */
        static void removeBlockTypes();

        /**
         * Attempts to add a new block trait to the vector. Does not add duplicates.
         *
         * @param name the name of the trait.
         * @param value the value of the trait.
         *
         * @return true if the block trait was added false otherwise.
         */
        static bool addBlockTrait(std::string *name, std::string *value);

        /**
         * Attempts to get and or add a new block trait to the vector. Does not add duplicates.
         *
         * @param name the name of the trait.
         * @param value the value of the trait.
         *
         * @return the fetched or newly added block trait.
         */
        static std::pair<BlockTrait*, bool> getAndOrAddBlockTrait(std::string *name, std::string *value);

        /**
         * Removes and de-allocates all block traits.
         */
        static void removeBlockTraits();
    };
}

#endif //GLM_WASM_DATAMANAGER_H
