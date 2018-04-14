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
#ifndef GLM_WASM_TWODCHUNK_H
#define GLM_WASM_TWODCHUNK_H

#include "../../../../server/world/Chunk.h"
#include "../../../api/Renderable.h"

namespace glmwasm {

    /**
     * Represents a renderable minecraft chunk.
     *
     * @author Tyler Bucher
     */
    class TwoDChunk : public Chunk, public Renderable {
    public:

        /**
         * Creates a new chunk with a position.
         *
         * @param x the x position of this chunk.
         * @param y the y position of this chunk.
         * @param z the z position of this chunk.
         */
        TwoDChunk(int x, int y, int z);

        /**
         * Renders this object.
         */
        void render() override;

        /**
         *
         */
        ~TwoDChunk() override;
    };
}

#endif //GLM_WASM_TWODCHUNK_H
