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
#ifndef GLM_WASM_PLAYER_H
#define GLM_WASM_PLAYER_H


#include <string>
#include <glm/vec3.hpp>

namespace glmwasm {

    /**
     * Represents a minecraft player.
     *
     * @author Tyler Bucher
     */
    class Player {
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
         * The position of the player.
         */
        glm::vec3 position;

    public:

        /**
         * Creates a new player with a uuid and a name.
         *
         * @param uuid the uuid of this world.
         * @param name the name of this world.
         */
        Player(const std::string *uuid, const std::string *name);

        /**
         * @return the uuid of this world.
         */
        const std::string *getUuid() const;

        /**
         * @return the name of this world.
         */
        const std::string *getName() const;

        /**
         * @return the position of the player.
         */
        const glm::vec3 &getPosition() const;

        /**
         * Deletes the current name and sets the pointer.
         *
         * @param name the new name of the player.
         */
        void setName(const std::string *name);

        /**
         * Removes this player and deletes its uuid and name.
         */
        virtual ~Player();
    };
}

#endif //GLM_WASM_PLAYER_H
