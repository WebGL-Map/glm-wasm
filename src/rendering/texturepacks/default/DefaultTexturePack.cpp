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
#include "DefaultTexturePack.h"
#include <cmath>
#include <glm/gtc/type_ptr.hpp>
#include "OpenGL.h"
#include "data/TwoDChunk.h"
#include "data/TwoDBlock.h"

void glmwasm::DefaultTexturePack::targetChunkRangeFor2d(const glm::vec3 &position, float aspectRatio, float fov, int *range) {
    float far = abs(position.z);
    float horizontalDistFar = (far * std::tan(fov)); // NOLINT
    float verticalDistFar = (far * std::tan((fov / aspectRatio))); // NOLINT
    int cxL = static_cast<int> (std::floor(position.x - horizontalDistFar)) >> 4; // NOLINT
    int czL = static_cast<int> (std::ceil(position.y - verticalDistFar)) >> 4; // NOLINT
    int cxR = static_cast<int> (std::ceil(position.x + horizontalDistFar)) >> 4; // NOLINT
    int czR = static_cast<int> (std::floor(position.y + verticalDistFar)) >> 4; // NOLINT

    range[0] = cxL;
    range[1] = czL;
    range[2] = cxR;
    range[3] = czR;
}

void glmwasm::DefaultTexturePack::init() {
    OpenGL::standardSetup();
    OpenGL::shaderSetup();
}

glmwasm::Block *glmwasm::DefaultTexturePack::createBlock(glmwasm::BlockType *blockType, int x, int y, int z) {
    return new TwoDBlock(blockType, x, y, z);
}

glmwasm::Chunk *glmwasm::DefaultTexturePack::createChunk(int x, int y, int z) {
    return new TwoDChunk(x, y, z);
}

void glmwasm::DefaultTexturePack::renderBlocks(Camera &camera, const std::map<int, std::map<int, Chunk *>> &chunkMap) {
    if (camera.update()) {
        glUseProgram(OpenGL::shaderProgram_vc->getProgramId());
        glUniformMatrix4fv(OpenGL::uni_vc_view, 1, GL_FALSE, glm::value_ptr(camera.viewMat));
    }

    int chunkRange[4];
    DefaultTexturePack::targetChunkRangeFor2d(camera.position, OpenGL::aspectRatio, OpenGL::fov, chunkRange);

    glUseProgram(OpenGL::shaderProgram_vc->getProgramId());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    for (int i = chunkRange[1]; i < chunkRange[3]; i++) {
        for (int j = chunkRange[0]; j < chunkRange[2]; j++) {
            dynamic_cast<TwoDChunk *> (chunkMap.at(i).at(j))->render();
        }
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glUseProgram(0);
}

glmwasm::DefaultTexturePack::DefaultTexturePack() = default;

glmwasm::DefaultTexturePack::~DefaultTexturePack() = default;
