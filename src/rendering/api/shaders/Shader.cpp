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
#include "Shader.h"

glmwasm::Shader::Shader(const GLenum &type, const std::string *source) : type(type), source(source) {
    shaderId = glCreateShader(type);
    if(shaderId != 0) {
        const GLchar* sourceString[1];
        sourceString[0] = source->c_str();
        GLint sourceStringLength[1];
        sourceStringLength[0] = source->length();

        glShaderSource(shaderId, 1, sourceString, sourceStringLength);
        glCompileShader(shaderId);
    }
}

bool glmwasm::Shader::verify() const {
    int status = 0;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
    return status != 0;
}

const GLenum glmwasm::Shader::getType() const {
    return type;
}

const std::string *glmwasm::Shader::getSource() const {
    return source;
}

GLuint glmwasm::Shader::getShaderId() const {
    return shaderId;
}

glmwasm::Shader::~Shader() {
    delete source;
    glDeleteShader(shaderId);
}