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
#include "Server.h"

std::string *glmwasm::Server::getName() const {
    return name;
}

std::string *glmwasm::Server::getIp() const {
    return ip;
}

std::string *glmwasm::Server::getPort() const {
    return port;
}

std::map<std::string, glmwasm::World *> &glmwasm::Server::getWorldMap() {
    return worldMap;
}

std::map<std::string, glmwasm::Player *> &glmwasm::Server::getPlayerMap() {
    return playerMap;
}

glmwasm::Server::Server(std::string *name, std::string *ip, std::string *port) : name(name), ip(ip), port(port) {}

glmwasm::Server::~Server() {
    delete name;
    delete ip;
    delete port;

    for (auto const &kvp : worldMap) {
        delete kvp.second;
    }
    for (auto const &kvp : playerMap) {
        delete kvp.second;
    }
}
