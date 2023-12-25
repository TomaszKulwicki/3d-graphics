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
            //base (x,y,z)
            -0.5f, 0.0f, -0.5f, 1.0f, 0.0f, 0.0f,   // 0
            0.5f, 0.0f, -0.5f, 1.0f, 0.0f, 0.0f,    // 1
            0.5f, 0.0f,  0.5f, 1.0f, 0.0f, 0.0f,    // 2
            -0.5f, 0.0f,  0.5f, 1.0f, 0.0f, 0.0f,   // 3

            //first side
            -0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 1.0f,   // 4
            0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 1.0f,    // 5
            0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,     // 6 top

            //second side
            0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f,    // 7
            0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f,     // 8
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,     // 9 top

            //third side
            0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f,     // 10
            -0.5f, 0.0f, 0.5f, 1.0f, 0.0f, 0.0f,    // 11
            0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,     // 12 top

            //last side
            -0.5f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f,     // 13
            -0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f,    // 14
            0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,      // 15 top

    };

    std::vector<GLushort> indices = {0,1,3,
                                     1,2,3,

                                     4,6,5,
                                     7,9,8,
                                     10,12,11,
                                     13,15,14
    };

    int w, h;
    std::tie(w, h) = frame_buffer_size();
    aspect = (float)w/h;
    fov = glm::pi<float>() / 4.0f;
    near = 0.1f;
    far = 100.0f;
    P = glm::perspective(fov, aspect, near, far);
    V = glm::lookAt(
            glm::vec3(2.0f, 2.0f, 3.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 1.0f, 0.0f)
    );


    GLuint uniformBuffer;
    glGenBuffers(1, &uniformBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffer);
    glBufferData(GL_UNIFORM_BUFFER, 8 * sizeof(float), nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuffer);

    // color uniform data
    float strength = 1.0f;
    float color[3] = { 1.0f, 1.0f, 1.0f};

    // colors from uniforms
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float), &strength);
    glBufferSubData(GL_UNIFORM_BUFFER, 16, sizeof(float) * 3, &color);

    // transformation uniforms
    glGenBuffers(1, &transformation);
    glBindBuffer(GL_UNIFORM_BUFFER, transformation);
    glBufferData(GL_UNIFORM_BUFFER, 64, nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, transformation);

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

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(3 * sizeof(GLfloat)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // End of vao "recording"

    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);
    glViewport(0, 0, w, h);

    glUseProgram(program);
}

//This functions is called every frame and does the actual rendering.
void SimpleShapeApplication::frame() {

    glm::mat4 M(1.0f);
    auto PVM = P * V * M;

    glBindBuffer(GL_UNIFORM_BUFFER, transformation);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4),&PVM[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
}

void SimpleShapeApplication::framebuffer_resize_callback(int w, int h) {
    Application::framebuffer_resize_callback(w, h);
    glViewport(0,0,w,h);
    aspect = (float) w / h;
    P = glm::perspective(fov, aspect, near, far);
}