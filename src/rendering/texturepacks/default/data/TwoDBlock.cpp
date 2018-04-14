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
#include <GLES2/gl2.h>
#include "TwoDBlock.h"

glmwasm::TwoDBlock::TwoDBlock(glmwasm::BlockType *blockType, int x, int y, int z) : Block(blockType, x, y, z) {
    // Vertex data
    // First triangle
    vertexData[0] = x;
    vertexData[1] = 0;
    vertexData[2] = z;
    vertexData[3] = x;
    vertexData[4] = 0;
    vertexData[5] = z + 1;
    vertexData[6] = x + 1;
    vertexData[7] = 0;
    vertexData[8] = z;
    // Second Triangle
    vertexData[9] = x;
    vertexData[10] = 0;
    vertexData[11] = z + 1;
    vertexData[12] = x + 1;
    vertexData[13] = 0;
    vertexData[14] = z + 1;
    vertexData[15] = x + 1;
    vertexData[16] = 0;
    vertexData[17] = z;
    glGenBuffers(1, &vertexHandler);
    glBindBuffer(GL_ARRAY_BUFFER, vertexHandler);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLint), vertexData, GL_STATIC_DRAW);
    // Color Data
    colorData[0] = 1;
    colorData[1] = 0;
    colorData[2] = 0;
    colorData[3] = 1;
    colorData[4] = 0;
    colorData[5] = 1;
    colorData[6] = 0;
    colorData[7] = 1;
    colorData[8] = 0;
    colorData[9] = 0;
    colorData[10] = 1;
    colorData[11] = 1;
    colorData[12] = 1;
    colorData[13] = 1;
    colorData[14] = 1;
    colorData[15] = 1;
    glGenBuffers(1, &colorHandler);
    glBindBuffer(GL_ARRAY_BUFFER, colorHandler);
    glBufferData(GL_ARRAY_BUFFER, 16 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);
}

void glmwasm::TwoDBlock::render() {
    glBindBuffer(GL_ARRAY_BUFFER, vertexHandler);
    glVertexAttribPointer(0, 3, GL_INT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, colorHandler);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}

glmwasm::TwoDBlock::~TwoDBlock() = default;
