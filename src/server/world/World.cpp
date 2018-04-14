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
#include "World.h"

const std::string *glmwasm::World::getUuid() const {
    return uuid;
}

std::map<int, std::map<int, glmwasm::Chunk *>> &glmwasm::World::getChunkMap() {
    return chunkMap;
}

std::map<std::string, glmwasm::Player *> &glmwasm::World::getPlayerMap() {
    return playerMap;
}

const glmwasm::Chunk *glmwasm::World::getChunkAt(const int x, const int z) const {
    const auto posIterator = chunkMap.find(x);
    if (posIterator != chunkMap.end()) {
        const auto posIterator2 = posIterator->second.find(z);
        if (posIterator2 != posIterator->second.end()) {
            return posIterator2->second;
        }
    }
    return nullptr;
}

const glmwasm::Block *glmwasm::World::getBlockAt(int x, int y, int z) const {
    const Chunk *chunkPtr = getChunkAt(x >> 4, z >> 4); // NOLINT
    if (chunkPtr != nullptr) {
        return chunkPtr->getBlockAt(getChunkBlockPosFromGlobalPos(x), y, getChunkBlockPosFromGlobalPos(z));
    }
    return nullptr;
}

int glmwasm::World::getChunkBlockPosFromGlobalPos(int i) const {
    return i < 0 ? ((i >> 4) << 4) % i : i % ((i >> 4) << 4); // NOLINT
}

const std::string *glmwasm::World::getName() const {
    return name;
}

glmwasm::World::World(const std::string *uuid, const std::string *name) : uuid(uuid), name(name) {}

glmwasm::World::~World() {
    for (auto const &kvp : chunkMap) {
        for (auto const &kvp2 : kvp.second) {
            delete kvp2.second;
        }
    }
    delete uuid;
    delete name;
}
