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
#include "OpenGL.h"
#include <glm/gtc/type_ptr.hpp>
#include <emscripten.h>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

std::string *glmwasm::OpenGL::vertex_shader_vc_source;

std::string *glmwasm::OpenGL::fragment_shader_vc_source;

glmwasm::Shader *glmwasm::OpenGL::vertex_shader_vc;

glmwasm::Shader *glmwasm::OpenGL::fragment_shader_vc;

glmwasm::Program *glmwasm::OpenGL::shaderProgram_vc;

GLint glmwasm::OpenGL::uni_vc_model;

GLint glmwasm::OpenGL::uni_vc_view;

GLint glmwasm::OpenGL::uni_vc_projection;

float glmwasm::OpenGL::width;

float glmwasm::OpenGL::height;

float glmwasm::OpenGL::aspectRatio;

float glmwasm::OpenGL::fov;

float glmwasm::OpenGL::near;

float glmwasm::OpenGL::far;

glm::mat4 glmwasm::OpenGL::model;

glm::mat4 glmwasm::OpenGL::projection;

void glmwasm::OpenGL::printShaderInfoLog(GLuint shaderId) {
    int infoLogLen = 0;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLen);
    if (infoLogLen > 1) {
        char infoLog[infoLogLen];
        glGetShaderInfoLog(shaderId, infoLogLen, nullptr, infoLog);
        std::cout << "Shader load error: " << infoLog << std::endl;
    }
}

void glmwasm::OpenGL::standardSetup() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LESS);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void glmwasm::OpenGL::shaderSetup() {
    vertex_shader_vc_source = new std::string("precision highp float;\n"
                                              "attribute vec2 position;\n"
                                              "attribute vec3 color;\n"
                                              "\n"
                                              "uniform mat4 model;\n"
                                              "uniform mat4 view;\n"
                                              "uniform mat4 projection;\n"
                                              "\n"
                                              "varying vec4 oColor;\n"
                                              "\n"
                                              "void main() {\n"
                                              "    oColor = vec4(color, 1);\n"
                                              "    mat4 mvp = projection * view * model;\n"
                                              "    gl_Position = mvp * vec4(position.x, position.y, 0, 1.0);\n"
                                              "}");
    fragment_shader_vc_source = new std::string("precision lowp float;\n"
                                                "varying vec4 oColor;\n"
                                                "\n"
                                                "void main() {\n"
                                                "    gl_FragColor = oColor;\n"
                                                "}");

    vertex_shader_vc = new Shader(GL_VERTEX_SHADER, vertex_shader_vc_source);
    fragment_shader_vc = new Shader(GL_FRAGMENT_SHADER, fragment_shader_vc_source);

    if (!vertex_shader_vc->verify()) {
        printShaderInfoLog(vertex_shader_vc->getShaderId());
    }
    if (!fragment_shader_vc->verify()) {
        printShaderInfoLog(fragment_shader_vc->getShaderId());
    }

    shaderProgram_vc = new Program();
    shaderProgram_vc->attachShader(*vertex_shader_vc);
    shaderProgram_vc->attachShader(*fragment_shader_vc);

    glBindAttribLocation(shaderProgram_vc->getProgramId(), 0, "position");
    glBindAttribLocation(shaderProgram_vc->getProgramId(), 1, "color");

    shaderProgram_vc->link();
    shaderProgram_vc->validate();

    if (!shaderProgram_vc->verify()) {
        std::cout << "Shader program error.";
    }

    model = glm::mat4();

    fov = static_cast<float>(45.0f * M_PI / 180.0);
    aspectRatio = width / height;
    near = 0.10f;
    far = 8192.00f;
    projection = glm::perspective(fov, aspectRatio, near, far);

    glUseProgram(shaderProgram_vc->getProgramId());

    uni_vc_model = glGetUniformLocation(shaderProgram_vc->getProgramId(), "model");
    glUniformMatrix4fv(uni_vc_model, 1, GL_FALSE, glm::value_ptr(model));

    uni_vc_view = glGetUniformLocation(shaderProgram_vc->getProgramId(), "view");
    glUniformMatrix4fv(uni_vc_view, 1, GL_FALSE, glm::value_ptr(glm::mat4()));

    uni_vc_projection = glGetUniformLocation(shaderProgram_vc->getProgramId(), "projection");
    glUniformMatrix4fv(uni_vc_projection, 1, GL_FALSE, glm::value_ptr(projection));

    glUseProgram(0);
}
