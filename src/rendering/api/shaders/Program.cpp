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
#include "Program.h"

glmwasm::Program::Program() {
    programId = glCreateProgram();
}

void glmwasm::Program::attachShader(glmwasm::Shader &shader) {
    glAttachShader(programId, shader.getShaderId());
}

void glmwasm::Program::detachShader(glmwasm::Shader &shader) {
    glDetachShader(programId, shader.getShaderId());
}

void glmwasm::Program::link() const {
    glLinkProgram(programId);
}

void glmwasm::Program::validate() const {
    glValidateProgram(programId);
}

bool glmwasm::Program::verify() const {
    int status = 0;
    glGetProgramiv(programId, GL_LINK_STATUS, &status);
    return status != 0;
}

GLuint glmwasm::Program::getProgramId() const {
    return programId;
}

glmwasm::Program::~Program() {
    glDeleteProgram(programId);
}
