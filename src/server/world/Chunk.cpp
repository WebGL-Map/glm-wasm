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
#include "Chunk.h"

std::map<int, std::map<int, std::map<int, glmwasm::Block *>>> &glmwasm::Chunk::getBlockMap() {
    return blockMap;
}

const int glmwasm::Chunk::getX() const {
    return x;
}

const int glmwasm::Chunk::getY() const {
    return y;
}

const int glmwasm::Chunk::getZ() const {
    return z;
}

const glmwasm::Block *glmwasm::Chunk::getBlockAt(int x, int y, int z) const {
    const auto posIterator = blockMap.find(x);
    if (posIterator != blockMap.end()) {
        const auto posIterator2 = posIterator->second.find(y);
        if (posIterator2 != posIterator->second.end()) {
            const auto posIterator3 = posIterator2->second.find(z);
            if (posIterator3 != posIterator2->second.end()) {
                return posIterator3->second;
            }
        }
    }
    return nullptr;
}

glmwasm::Chunk::Chunk(const int x, const int y, const int z)
        : x(x), y(y), z(z) {}

glmwasm::Chunk::~Chunk() {
    for (auto const& kvp : blockMap) {
        for (auto const& kvp2 : kvp.second) {
            for (auto const& kvp3 : kvp2.second) {
                delete kvp3.second;
            }
        }
    }
}
