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
#ifndef GLM_WASM_PROGRAM_H
#define GLM_WASM_PROGRAM_H

#include "Shader.h"

namespace glmwasm {

    /**
     * Represents an OpenGL shader program.
     *
     * @author Tyler Bucher
     */
    class Program {
    private:

        /**
         * The id for the gl shader.
         */
        GLuint programId;

    public:

        /**
         * Creates a new gl program.
         */
        Program();

        /**
         * Attaches a shader to this program.
         *
         * @param shader the shader to attach.
         */
        void attachShader(Shader &shader);

        /**
         * Detaches a shader from this program.
         *
         * @param shader the shader to detach.
         */
        void detachShader(Shader &shader);

        /**
         * Links the gl program.
         */
        void link() const;

        /**
         * Validates the gl program.
         */
        void validate() const;

        /**
         * @return the GL_LINK_STATUS of this shader.
         */
        bool verify() const;

        /**
         * @return the id for the gl shader.
         */
        GLuint getProgramId() const;

        /**
         * Removes this program.
         */
        virtual ~Program();
    };
}

#endif //GLM_WASM_PROGRAM_H
