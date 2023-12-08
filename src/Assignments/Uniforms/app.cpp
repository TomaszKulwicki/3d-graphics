#include "app.h"

#include <iostream>
#include <vector>
#include <tuple>

#include "Application/utils.h"
#include "glm/vec2.hpp"
#include "glm/fwd.hpp"
#include "glm/detail/type_mat2x2.hpp"
#include "glm/ext/scalar_constants.hpp"

void SimpleShapeApplication::init() {
    // A utility function that reads the shader sources, compiles them and creates the program object
    // As everything in OpenGL we reference program by an integer "handle".
    auto program = xe::utils::create_program(
            {{GL_VERTEX_SHADER,   std::string(PROJECT_DIR) + "/shaders/base_vs.glsl"},
             {GL_FRAGMENT_SHADER, std::string(PROJECT_DIR) + "/shaders/base_fs.glsl"}});

    if (!program) {
        std::cerr << "Invalid program" << std::endl;
        exit(-1);
    }

    std::vector<GLfloat> vertices = {
            0.5f, 0.0f, 0.0f, 255.0f, 0.0f, 0.0f,   //0
            0.0f, 0.5f, 0.0f, 255.0f, 0.0f, 0.0f,   //1
            -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,    //2

            -0.5f, -0.5f, 0.0f, 255.0f, 255.0f, 0.0f, //3

            0.5f, -0.5f, 0.0f, 255.0f, 0.0f, 0.0f,    //4
            };

    std::vector<GLushort> indices = {0,1,2, 0,2,3, 3,4,0};

    // uniform color
    GLuint uniformBuffer;
    glGenBuffers(1, &uniformBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffer);
    glBufferData(GL_UNIFORM_BUFFER, 8 * sizeof(float), nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuffer);

    // color uniform data
    float strength = 0.8f;
    float color[3] = { 0.0f, 0.0f, 1.0f};

    // colors from uniforms
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float), &strength);
    glBufferSubData(GL_UNIFORM_BUFFER, 16, sizeof(float) * 3, &color);

    // transformation uniforms
    GLuint transformation;
    glGenBuffers(1, &transformation);
    glBindBuffer(GL_UNIFORM_BUFFER, transformation);
    glBufferData(GL_UNIFORM_BUFFER, 64, nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, transformation);

    // buffer data loading
    float theta = 1.0*glm::pi<float>()/6.0f;
    auto cs = std::cos(theta);
    auto ss = std::sin(theta);
    glm::mat2 rotation{cs,ss,-ss,cs};
    glm::vec2 translation{0.0,  -0.25};
    glm::vec2 scale{0.5, 0.5};
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec2), &scale);
    glBufferSubData(GL_UNIFORM_BUFFER, 8, sizeof(glm::vec2), &translation);
    glBufferSubData(GL_UNIFORM_BUFFER, 16, sizeof(glm::vec2), &rotation[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, 32, sizeof(glm::vec2), &rotation[1]);

    // indices
    GLuint indicesId;
    glGenBuffers(1, &indicesId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Generating the buffer and loading the vertex data into it.
    GLuint v_buffer_handle;
    glGenBuffers(1, &v_buffer_handle);
    OGL_CALL(glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle));
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // This setups a Vertex Array Object (VAO) that  encapsulates the state of all vertex buffers needed for rendering
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesId);

    // This indicates that the data for attribute 0 should be read from a vertex buffer.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(0));

    // Add colors
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(3 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    //end of vao "recording"

    // Setting the background color of the rendering window,
    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);

    // This setups an OpenGL vieport of the size of the whole rendering window.
    auto[w, h] = frame_buffer_size();
    glViewport(0, 0, w, h);

    glUseProgram(program);
}

//This functions is called every frame and does the actual rendering.
void SimpleShapeApplication::frame() {
    // Binding the VAO will setup all the required vertex buffers.
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
}
