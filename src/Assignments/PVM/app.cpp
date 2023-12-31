#include "app.h"

#include <iostream>
#include <vector>
#include <tuple>

#include "Application/utils.h"
#include "glm/vec2.hpp"
#include "glm/fwd.hpp"
#include "glm/detail/type_mat2x2.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/trigonometric.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

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
            0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,         //0
            0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f,         //1
            -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,        //2
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,       //3
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,        //4
    };

    std::vector<GLushort> indices = {0,1,2, 0,2,3, 3,4,0};

    // uniform color
    GLuint uniformBuffer;
    glGenBuffers(1, &uniformBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffer);
    glBufferData(GL_UNIFORM_BUFFER, 8 * sizeof(float), nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuffer);

    // color uniform data
    float strength = 1.0f;
    float color[3] = { 1.0f, 0.0f, 0.0f};

    // colors from uniforms
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float), &strength);
    glBufferSubData(GL_UNIFORM_BUFFER, 16, sizeof(float) * 3, &color);

    // transformation uniforms
    GLuint transformation;
    glGenBuffers(1, &transformation);
    glBindBuffer(GL_UNIFORM_BUFFER, transformation);
    glBufferData(GL_UNIFORM_BUFFER, 64, nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, transformation);

    // PVM
    glm::mat4 model = glm::mat4(0.5f);
    glm::mat4 view = glm::lookAt(
            glm::vec3(1.0f, 5.0f, 3.0f),             // the position of your camera, in world space
            glm::vec3(0.0f, 0.0f, 0.0f),           // where you want to look at, in world space
            glm::vec3(0.0f, 1.0f, 0.0f));             // Head is up (set to 0,-1,0 to look upside-down)

    glm::mat4 projection = glm::perspective(
            glm::radians(45.0f),                     // The vertical Field of View, in radians: the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
            1.0f,                                           // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960
            0.1f,                                           // Near clipping plane. Keep as big as possible, or you'll get precision issues.
            100.0f);                                         // Far clipping plane. Keep as little as possible.

    //glm::mat4 projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f);

    glm::mat4 PVM = projection * view * model;

    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(PVM));

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

    // Colors
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(3 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // End of vao "recording"

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