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
#include <emscripten.h>
#include "DataManager.h"
#include "./server/Server.h"
#include "Camera.h"
#include "rendering/api/TexturePack.h"
#include "rendering/texturepacks/default/DefaultTexturePack.h"
#include "rendering/texturepacks/default/OpenGL.h"
#include <iostream>
#include <cstring>
#include <glm/gtc/matrix_transform.hpp>

static glmwasm::Camera camera;
static glmwasm::DefaultTexturePack texturePack;
static std::vector<glmwasm::Server *> serverList;
static glmwasm::Server *selectedServer = nullptr;
static glmwasm::World *selectedWorld = nullptr;

/**
 * The main function to be called when the wasm module is loaded.
 *
 * @return 0.
 */
int main() {
    std::cout << "glm-wasm client loaded." << std::endl;
    return 0;
}

/**
 * Gets a block type from two c strings.
 *
 * @param cStrModId the mod id.
 * @param cStrBlockId the block id.
 *
 * @return the block type.
 */
glmwasm::BlockType *getBlockTypeFromStrings(const char *cStrModId, const char *cStrBlockId) {
    auto *modId = new std::string(cStrModId);
    auto *blockId = new std::string(cStrBlockId);
    auto uPair = glmwasm::DataManager::getAndOrAddBlockType(modId, blockId);
    if (!uPair.second) {
        delete modId;
        delete blockId;
    }
    return uPair.first;
}

/**
 * Gets a block type from one c string.
 *
 * @param fullCStr the full block type c str.
 *
 * @return the block type.
 */
glmwasm::BlockType *getBlockTypeFromCStr(char *fullCStr) {
    std::string fullStr(fullCStr);
    auto pos = fullStr.find(':');
    std::string strModId = fullStr.substr(0, pos);
    fullStr.erase(0, pos + 1);
    pos = fullStr.find('[');
    std::string strBlockId = fullStr.substr(0, pos);
    fullStr.erase(0, pos + 1);
    return getBlockTypeFromStrings(strModId.c_str(), strBlockId.c_str());
}

/**
 * Gets a block trait from two c strings.
 *
 * @param cStrName the name of the trait.
 * @param cStrValue the value of the trait.
 *
 * @return the block trait.
 */
glmwasm::BlockTrait *getBlockTraitFromStrings(const char *cStrName, const char *cStrValue) {
    auto *name = new std::string(cStrName);
    auto *value = new std::string(cStrValue);
    auto uPair = glmwasm::DataManager::getAndOrAddBlockTrait(name, value);
    if (!uPair.second) {
        delete name;
        delete value;
    }
    return uPair.first;
}

/**
 * Gets a block trait from one c string.
 *
 * @param fullCStr the full block trait c str.
 *
 * @return the block trait.
 */
glmwasm::BlockTrait *getBlockTraitFromCStr(const char *fullCStr) {
    std::string fullStr(fullCStr);
    auto pos = fullStr.find('=');
    std::string strName = fullStr.substr(0, pos);
    fullStr.erase(0, pos + 1);
    std::string strValue = fullStr;
    return getBlockTraitFromStrings(strName.c_str(), strValue.c_str());
}

/**
 * Sets a blocks list of block traits.
 *
 * @param block the block to modify.
 * @param fullCStr the full list of block trait c strings.
 */
void setBlockTraitsFromCStr(glmwasm::Block *block, char *fullCStr) {
    block->getBlockTraits().clear();
    std::string fullStr(fullCStr);
    unsigned int pos = 0;
    std::string fullTrait;
    while ((pos = fullStr.find(',')) != std::string::npos) {
        fullTrait = fullStr.substr(0, pos);
        block->addTrait(getBlockTraitFromCStr(fullTrait.c_str()));
        fullStr.erase(0, pos + 1);
    }
    fullTrait = fullStr.substr(0, fullStr.size() - 1);
    block->addTrait(getBlockTraitFromCStr(fullTrait.c_str()));
}

extern "C" {

/**
 * Attempts to add a server to this map client. Does not add duplicates.
 *
 * @param cStrName the conical name of the server.
 * @param cStrIp the ip address of the remote server.
 * @param cStrPort the port of the remote server.
 *
 * @return true if the server was added false otherwise.
 */
bool EMSCRIPTEN_KEEPALIVE addServer(char *cStrName, char *cStrIp, char *cStrPort) {
    for (auto &server : serverList) {
        if (std::strcmp(server->getIp()->c_str(), cStrIp) == 0 &&
            std::strcmp(server->getPort()->c_str(), cStrPort) == 0) {
            return false;
        }
    }
    auto *name = new std::string(cStrName);
    auto *ip = new std::string(cStrIp);
    auto *port = new std::string(cStrPort);
    serverList.push_back(new glmwasm::Server(name, ip, port));
    return true;
}

/**
 * Attempts to remove a server form the server list.
 *
 * @param cStrIp the ip address of the remote server.
 * @param cStrPort the port of the remote server.
 *
 * @return true if the server was deleted false otherwise.
 */
bool EMSCRIPTEN_KEEPALIVE removeServer(char *cStrIp, char *cStrPort) {
    for (auto it = serverList.begin(); it != serverList.end(); ++it) {
        if (std::strcmp((*it)->getIp()->c_str(), cStrIp) == 0 &&
            std::strcmp((*it)->getPort()->c_str(), cStrPort) == 0) {
            if (selectedServer == *it) {
                selectedServer = nullptr;
            }
            delete *it;
            serverList.erase(it);
            return true;
        }
    }
    return false;
}

/**
 * Attempts to select a server in the server list.
 *
 * @param cStrIp the ip address of the remote server.
 * @param cStrPort the port of the remote server.
 *
 * @return true if the server was selected false otherwise.
 */
bool EMSCRIPTEN_KEEPALIVE selectServer(char *cStrIp, char *cStrPort) {
    for (auto &server : serverList) {
        if (std::strcmp(server->getIp()->c_str(), cStrIp) == 0 &&
            std::strcmp(server->getPort()->c_str(), cStrPort) == 0) {
            selectedServer = server;
            return true;
        }
    }
    return false;
}

/**
 * Attempts to add a world to a server.
 *
 * @param cStrIp the ip address of the remote server.
 * @param cStrPort the port of the remote server.
 * @param cStrUuid the uuid of the world.
 * @param cStrName the name of the world.
 *
 * @return true if the world was added false otherwise.
 */
bool EMSCRIPTEN_KEEPALIVE addWorld(char *cStrIp, char *cStrPort, char *cStrUuid, char *cStrName) {
    for (auto &server : serverList) {
        if (std::strcmp(server->getIp()->c_str(), cStrIp) == 0 &&
            std::strcmp(server->getPort()->c_str(), cStrPort) == 0) {
            for (auto &world : server->getWorldMap()) {
                if (std::strcmp(world.first.c_str(), cStrUuid) != 0) {
                    auto *uuid = new std::string(cStrUuid);
                    auto *name = new std::string(cStrName);
                    auto *newWorld = new glmwasm::World(uuid, name);
                    auto returnVal = server->getWorldMap().emplace(*uuid, newWorld);
                    if (!returnVal.second) {
                        delete newWorld;
                        return false;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Attempts to remove a world from a server.
 *
 * @param cStrIp the ip address of the remote server.
 * @param cStrPort the port of the remote server.
 * @param cStrUuid the uuid of the world.
 *
 * @return true if the world was removed false otherwise.
 */
bool EMSCRIPTEN_KEEPALIVE removeWorld(char *cStrIp, char *cStrPort, char *cStrUuid) {
    for (auto &server : serverList) {
        if (std::strcmp(server->getIp()->c_str(), cStrIp) == 0 &&
            std::strcmp(server->getPort()->c_str(), cStrPort) == 0) {
            std::string tUUid(cStrUuid);
            auto it = server->getWorldMap().find(tUUid);
            if (it != server->getWorldMap().end()) {
                if (selectedWorld == it->second) {
                    selectedWorld = nullptr;
                }
                delete it->second;
                server->getWorldMap().erase(it);
                return true;
            }
        }
    }
    return false;
}

/**
 * Attempts to select a given world.
 *
 * @param cStrIp the ip address of the remote server.
 * @param cStrPort the port of the remote server.
 * @param cStrUuid the uuid of the world.
 *
 * @return true if the world was selected false otherwise.
 */
bool EMSCRIPTEN_KEEPALIVE selectWorld(char *cStrIp, char *cStrPort, char *cStrUuid) {
    for (auto &server : serverList) {
        if (std::strcmp(server->getIp()->c_str(), cStrIp) == 0 &&
            std::strcmp(server->getPort()->c_str(), cStrPort) == 0) {
            for (auto &world : server->getWorldMap()) {
                if (std::strcmp(world.first.c_str(), cStrUuid) != 0) {
                    selectedWorld = world.second;
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Adds or updates a chunk.
 *
 * @param cStrIp the ip address of the remote server.
 * @param cStrPort the port of the remote server.
 * @param cStrUuid the uuid of the world.
 * @param x the x position of the chunk.
 * @param z the z position of the chunk.
 * @param heightMap the array of heights for the blocks.
 * @param blockInfo a list of strings which represent block info.
 *
 * @return true if the chunk was added or updated false otherwise.
 */
bool EMSCRIPTEN_KEEPALIVE addOrUpdateChunk(char *cStrIp, char *cStrPort, char *cStrUuid, int x, int z, int *heightMap, char **blockInfo) {
    for (auto &server : serverList) {
        if (std::strcmp(server->getIp()->c_str(), cStrIp) == 0 &&
            std::strcmp(server->getPort()->c_str(), cStrPort) == 0) {
            for (auto &world : server->getWorldMap()) {
                if (std::strcmp(world.first.c_str(), cStrUuid) != 0) {
                    glmwasm::Chunk *uChunk = nullptr;
                    if (world.second->getChunkMap()[x][z] == nullptr) {
                        uChunk = new glmwasm::Chunk(x, 0, z);
                        world.second->getChunkMap()[x][z] = uChunk;
                    } else {
                        uChunk = world.second->getChunkMap()[x][z];
                    }
                    int hIndex = 0;
                    int biIndex = 0;
                    for (int i = 0; i < 1; ++i) { // y height
                        for (int j = 0; j < 16; ++j) { // z
                            for (int k = 0; k < 16; ++k) { // x
                                glmwasm::Block *uBlock = nullptr;
                                if (uChunk->getBlockMap()[k][i][j] == nullptr) {
                                    uBlock = texturePack.createBlock(getBlockTypeFromCStr(blockInfo[biIndex]),
                                                                     uChunk->getX() + k, heightMap[hIndex++],
                                                                     uChunk->getZ() + j);
                                    setBlockTraitsFromCStr(uBlock, blockInfo[biIndex++]);
                                    uChunk->getBlockMap()[k][i][j] = uBlock;
                                } else {
                                    uBlock = uChunk->getBlockMap()[k][i][j];
                                    uBlock->setBlockType(getBlockTypeFromCStr(blockInfo[biIndex]));
                                    uBlock->y = heightMap[hIndex++];
                                    setBlockTraitsFromCStr(uBlock, blockInfo[biIndex++]);
                                }
                            }
                        }
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Moves the camera some distance.
 *
 * @param x the x displacement.
 * @param y the y displacement.
 * @param z the z displacement.
 */
void EMSCRIPTEN_KEEPALIVE moveCamera(float x, float y, float z) {
    camera.position.x += x;
    camera.position.y += y;
    camera.position.z += z;
    camera.dirty = true;
}


/**
 * Allows javascript to add block types.
 *
 * @param cStrModId the mod id in c string form.
 * @param cStrBlockId the block id in c string form.
 *
 * @return true if the block type was added false otherwise.
 */
bool EMSCRIPTEN_KEEPALIVE addBlockType(char *cStrModId, char *cStrBlockId) {
    auto *modId = new std::string(cStrModId);
    auto *blockId = new std::string(cStrBlockId);
    bool result = glmwasm::DataManager::addBlockType(modId, blockId);
    if (!result) {
        delete modId;
        delete blockId;
    }
    return result;
}

/**
 * Allows javascript to add block traits.
 *
 * @param cStrName the trait name in c string form.
 * @param cStrValue the trait value in c string form.
 *
 * @return true if the block trait was added false otherwise.
 */
bool EMSCRIPTEN_KEEPALIVE addBlockTrait(char *cStrName, char *cStrValue) {
    auto *name = new std::string(cStrName);
    auto *value = new std::string(cStrValue);
    bool result = glmwasm::DataManager::addBlockTrait(name, value);
    if (!result) {
        delete name;
        delete value;
    }
    return result;
}

/**
 * Initializes OpenGL.
 *
 * @param width the width of the canvas.
 * @param height the height of the canvas.
 */
void EMSCRIPTEN_KEEPALIVE initGl(float width, float height) {
    glmwasm::OpenGL::width = width;
    glmwasm::OpenGL::height = height;
    texturePack.init();
}

/**
 * Changes the current projection matrix.
 *
 * @param width the width of the canvas.
 * @param height the height of the canvas.
 */
void EMSCRIPTEN_KEEPALIVE resizeClient(float width, float height) {
    glmwasm::OpenGL::width = width;
    glmwasm::OpenGL::height = height;
    glmwasm::OpenGL::aspectRatio = width / height;
    glmwasm::OpenGL::projection = glm::perspective(
            glmwasm::OpenGL::fov,
            glmwasm::OpenGL::aspectRatio,
            glmwasm::OpenGL::near,
            glmwasm::OpenGL::far
    );
}

/**
 * Renders blocks to the screen.
 */
void EMSCRIPTEN_KEEPALIVE render() {
    if (selectedServer != nullptr && selectedWorld != nullptr) {
        texturePack.renderBlocks(camera, selectedWorld->getChunkMap());
    }
}

/**
 * Removes created objects.
 */
void EMSCRIPTEN_KEEPALIVE cleanUp() {
    for (auto &server : serverList) {
        delete server;
    }
    glmwasm::DataManager::removeBlockTraits();
    glmwasm::DataManager::removeBlockTypes();
}
}