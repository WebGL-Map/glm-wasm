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
#include "Player.h"

const std::string *glmwasm::Player::getUuid() const {
    return uuid;
}

const std::string *glmwasm::Player::getName() const {
    return name;
}

const glm::vec3 &glmwasm::Player::getPosition() const {
    return position;
}

void glmwasm::Player::setName(const std::string *name) {
    delete this->name;
    this->name = name;
}

glmwasm::Player::Player(const std::string *uuid, const std::string *name) : uuid(uuid), name(name) {}

glmwasm::Player::~Player() {
    delete this->uuid;
    delete this->name;
}
