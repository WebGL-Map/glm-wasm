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
#ifndef GLM_WASM_WORLD_H
#define GLM_WASM_WORLD_H

#include <string>
#include <map>
#include "Chunk.h"
#include "../Player.h"

namespace glmwasm {

    /**
     * Represents a minecraft world.
     *
     * @author Tyler Bucher
     */
    class World {
    private:

        /**
         * The uuid of this world.
         */
        const std::string *uuid;

        /**
         * The name of this world.
         */
        const std::string *name;

        /**
         * The spawn point of the world.
         */
        glm::vec3 spawnPoint;

        /**
         * States if this world is the default world.
         */
        bool idefault;

        /**
         * The list of chunks this world has.
         */
        std::map<int, std::map<int, Chunk *>> chunkMap;

        /**
         * A list of players for this world.
         */
        std::map<std::string, Player *> playerMap;

    public:

        /**
         * Creates a new world with a uuid and a name.
         *
         * @param uuid the uuid of this world.
         * @param name the name of this world.
         * @param x the x position of the spawn point.
         * @param y the y position of the spawn point.
         * @param z the z position of the spawn point.
         */
        World(const std::string *uuid, const std::string *name, bool isDefault, float x, float y, float z);

        /**
         * @return the uuid of this world.
         */
        const std::string *getUuid() const;

        /**
         * @return the name of this world.
         */
        const std::string *getName() const;

        /**
         * @return true if this world is the default world false other wise.
         */
        bool isDefault() const;

        /**
         * @return the spawn point of the world.
         */
        const glm::vec3 &getSpawnPoint() const;

        /**
         * @return the list of chunks this world has.
         */
        std::map<int, std::map<int, Chunk *>> &getChunkMap();

        /**
         * @return the list of players for this world.
         */
        std::map<std::string, Player *> &getPlayerMap();

        /**
         * @param x the x position of the chunk.
         * @param z the z position of the chunk.
         *
         * @return the chunk at the location of the cords.
         */
        const Chunk *getChunkAt(int x, int z) const;

        /**
         * @param x the x position of the block.
         * @param y the y position of the block.
         * @param z the z position of the block.
         *
         * @return the block at the location of the cords.
         */
        const Block *getBlockAt(int x, int y, int z) const;

        /**
         * @param i the position to convert.
         *
         * @return the converted block position.
         */
        int getChunkBlockPosFromGlobalPos(int i) const;

        /**
         * Removes this world an all of its chunks.
         */
        virtual ~World();
    };
}

#endif //GLM_WASM_WORLD_H
