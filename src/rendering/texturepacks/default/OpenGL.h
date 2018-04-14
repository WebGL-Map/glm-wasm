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
#ifndef GLM_WASM_OPENGL_H
#define GLM_WASM_OPENGL_H

#include <GLES2/gl2.h>
#include <glm/glm.hpp>
#include "../../api/shaders/Program.h"

namespace glmwasm {

    /**
     * Basic OpenGL control.
     *
     * @author Tyler Bucher
     */
    class OpenGL {
    private:

        /**
         * Prints the shader error log.
         *
         * @param shaderId the gl id of the shader.
         */
        static void printShaderInfoLog(GLuint shaderId);

    public:

        /**
         * The vertex shader source.
         */
        static std::string *vertex_shader_vc_source;

        /**
         * The fragment shader source.
         */
        static std::string *fragment_shader_vc_source;

        /**
         * The vertex shader object.
         */
        static Shader *vertex_shader_vc;

        /**
         * The fragment shader object.
         */
        static Shader *fragment_shader_vc;

        /**
         * The combined shader program object.
         */
        static Program *shaderProgram_vc;

        /**
         * The shader uniform model location.
         */
        static GLint uni_vc_model;

        /**
         * The shader uniform view location.
         */
        static GLint uni_vc_view;

        /**
         * The shader uniform projection location.
         */
        static GLint uni_vc_projection;

        /**
         * The gl context width.
         */
        static float width;

        /**
         * The gl context height.
         */
        static float height;

        /**
         * The gl context aspect ratio.
         */
        static float aspectRatio;

        /**
         * The gl context fov.
         */
        static float fov;

        /**
         * The gl context near plane.
         */
        static float near;

        /**
         * The gl context far plane.
         */
        static float far;

        /**
         * The gl context model matrix.
         */
        static glm::mat4 model;

        /**
         * The gl context projection matrix.
         */
        static glm::mat4 projection;

        /**
         * Sets up basic OpenGL states.
         */
        static void standardSetup();

        /**
         * Sets up shader information.
         */
        static void shaderSetup();
    };
}

#endif //GLM_WASM_OPENGL_H
