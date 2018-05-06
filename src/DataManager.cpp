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
#include "DataManager.h"

std::vector<glmwasm::BlockType *> glmwasm::DataManager::blockTypes;

std::vector<glmwasm::BlockTrait *> glmwasm::DataManager::blockTraits;

std::vector<glmwasm::BlockType *> &glmwasm::DataManager::getBlockTypes() {
    return blockTypes;
}

std::vector<glmwasm::BlockTrait *> &glmwasm::DataManager::getBlockTraits() {
    return blockTraits;
}

bool glmwasm::DataManager::addBlockType(std::string *modId, std::string *blockId) {
    for (auto &blockType : blockTypes) {
        if (*blockType->getModId() == *modId && *blockType->getBlockId() == *blockId) {
            return false;
        }
    }
    blockTypes.push_back(new glmwasm::BlockType(modId, blockId));
    return true;
}

bool glmwasm::DataManager::addBlockTrait(std::string *name, std::string *value) {
    for (auto &blockTrait : blockTraits) {
        if (*blockTrait->getName() == *name && *blockTrait->getValue() == *value) {
            return false;
        }
    }
    blockTraits.push_back(new glmwasm::BlockTrait(name, value));
    return true;
}

void glmwasm::DataManager::removeBlockTypes() {
    for (auto &blockType : blockTypes) {
        delete blockType;
    }
    blockTypes.clear();
}

void glmwasm::DataManager::removeBlockTraits() {
    for (auto &blockTrait : blockTraits) {
        delete blockTrait;
    }
    blockTraits.clear();
}

std::pair<glmwasm::BlockType*, bool> glmwasm::DataManager::getAndOrAddBlockType(std::string *modId, std::string *blockId) {
    for (auto &blockType : blockTypes) {
        if (*blockType->getModId() == *modId && *blockType->getBlockId() == *blockId) {
            return std::make_pair(blockType, false);
        }
    }
    auto *newBlockType = new glmwasm::BlockType(modId, blockId);
    blockTypes.push_back(newBlockType);
    return std::make_pair(newBlockType, true);
}

std::pair<glmwasm::BlockTrait*, bool> glmwasm::DataManager::getAndOrAddBlockTrait(std::string *name, std::string *value) {
    for (auto &blockTrait : blockTraits) {
        if (*blockTrait->getName() == *name && *blockTrait->getValue() == *value) {
            return std::make_pair(blockTrait, false);
        }
    }
    auto *newBlockTrait = new glmwasm::BlockTrait(name, value);
    blockTraits.push_back(newBlockTrait);
    return std::make_pair(newBlockTrait, true);;
}
