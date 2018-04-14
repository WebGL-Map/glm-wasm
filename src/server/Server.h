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
#ifndef GLM_WASM_SERVER_H
#define GLM_WASM_SERVER_H

#include <string>
#include "world/World.h"

namespace glmwasm {

    /**
     * Represents a server. Holds information about players and worlds.
     *
     * @author Tyler Bucher
     */
    class Server {
    private:

        /**
         * The name of the server.
         */
        std::string *name;

        /**
         * The ip address of the server.
         */
        std::string *ip;

        /**
         * The port of the server.
         */
        std::string *port;

        /**
         * The list of worlds this server has.
         */
        std::map<std::string, World *> worldMap;

        /**
         * The list of players on this server.
         */
        std::map<std::string, Player *> playerMap;

    public:

        /**
         * Creates a new server with basic info.
         *
         * @param name the name of the server.
         * @param ip the ip address of the server.
         * @param port the port of the server.
         */
        Server(std::string *name, std::string *ip, std::string *port);

        /**
         * @return the name of the server.
         */
        std::string *getName() const;

        /**
         * @return the ip address of the server.
         */
        std::string *getIp() const;

        /**
         * @return the port of the server.
         */
        std::string *getPort() const;

        /**
         * @return the list of worlds this server has.
         */
        std::map<std::string, World *> &getWorldMap();

        /**
         * @return the list of players on this server.
         */
        std::map<std::string, Player *> &getPlayerMap();

        /**
         * Removes this server.
         */
        virtual ~Server();
    };
}

#endif //GLM_WASM_SERVER_H
