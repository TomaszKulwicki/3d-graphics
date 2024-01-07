#define STB_IMAGE_IMPLEMENTATION  1

#include "app.h"
#include <iostream>
#include <vector>
#include <tuple>
#include "3rdParty/stb/stb_image.h"
#include "Application/utils.h"
#include "glm/fwd.hpp"
#include "glm/detail/type_mat2x2.hpp"
#include "glm/ext/scalar_constants.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Engine/mesh_loader.h"

void SimpleShapeApplication::init() {
    set_camera(new Camera);
    set_controler(new CameraControler(camera()));
    // A utility function that reads the shader sources, compiles them and creates the program object
    // As everything in OpenGL we reference program by an integer "handle".
    auto program = xe::utils::create_program(
            {{GL_VERTEX_SHADER,   std::string(PROJECT_DIR) + "/shaders/base_vs.glsl"},
             {GL_FRAGMENT_SHADER, std::string(PROJECT_DIR) + "/shaders/base_fs.glsl"}});

    if (!program) {
        std::cerr << "Invalid program" << std::endl;
        exit(-1);
    }

    xe::ColorMaterial::init();

    auto pyramid = xe::load_mesh_from_obj(std::string(ROOT_DIR) + "/Models/blue_marble.obj", std::string(ROOT_DIR) + "/Models");

    add_submesh(pyramid);

//    stbi_set_flip_vertically_on_load(true);
//    GLint width, height, channels;
//    auto texture_file = std::string(ROOT_DIR) + "/Models/multicolor.png";
//    auto img = stbi_load(texture_file.c_str(), &width, &height, &channels, 0);
//    if (!img) {
//        std::cerr << "Error" << std::endl;
//    }
//    GLuint textures_ptr;
//    glGenTextures(1, &textures_ptr);
//    glBindTexture(GL_TEXTURE_2D, textures_ptr);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glBindTexture(GL_TEXTURE_2D, 0);

//    std::vector<GLfloat> vertices = {
//            //base (x,y,z)
//            -0.5f, 0.0f, -0.5f, 0.191f, 0.5f,  // 0
//            0.5f, 0.0f, -0.5f, 0.5f, 0.191f,   // 1
//            0.5f, 0.0f, 0.5f, 0.809f, 0.5f,   //  2
//
//            0.5f, 0.0f, 0.5f, 0.809f, 0.5f,   // 3
//            -0.5f, 0.0f, 0.5f, 0.5f, 0.809f,  // 4
//            -0.5f, 0.0f, -0.5f, 0.191f, 0.5f,  // 5
//
//            //first side
//            0.5f, 0.0f, -0.5f, 0.5f, 0.191f,    // 6
//            -0.5f, 0.0f, -0.5f, 0.191f, 0.5f,  // 7
//            0.0f, 1.0f, 0.0f, 0.0f, 0.0f,     // 8
//
//            //second side
//            0.5f, 0.0f, 0.5f, 0.809f, 0.5f,    // 9
//            0.5f, 0.0f, -0.5f, 0.5f, 0.191f,   // 10
//            0.0f, 1.0f, 0.0f, 1.0f, 0.0f,    // 11
//
//            //third side
//            -0.5f, 0.0f, 0.5f, 0.5f, 0.809f,   // 12
//            0.5f, 0.0f, 0.5f, 0.809f, 0.5f,    // 13
//            0.0f, 1.0f, 0.0f, 1.0f, 1.0f,    // 14
//
//            //last side
//            -0.5f, 0.0f, -0.5f, 0.191f, 0.5f,    // 15
//            -0.5f, 0.0f, 0.5f, 0.5f, 0.809f,    // 16
//            0.0f, 1.0f, 0.0f, 0.0f, 1.0f,      // 17
//    };

//    std::vector<GLushort> indices = {0,1,2,
//                                     3,4,5,
//
//                                     6,7,8,
//                                     9,10,11,
//                                     12,13,14,
//                                     15,16,17,
//    };

    //auto pyramid = new xe::Mesh;

//    pyramid->allocate_vertex_buffer(vertices.size() * sizeof(GLfloat), GL_STATIC_DRAW);
//    pyramid->load_vertices(0, vertices.size() * sizeof(GLfloat), vertices.data());
//    pyramid->vertex_attrib_pointer(0, 3, GL_FLOAT, 5 * sizeof(GLfloat), 0);
//    pyramid->vertex_attrib_pointer(1, 2, GL_FLOAT, 5 * sizeof(GLfloat), 3 * sizeof(GLfloat));
//
//    pyramid->allocate_index_buffer(indices.size() * sizeof(GLfloat), GL_STATIC_DRAW);
//    pyramid->load_indices(0, indices.size() * sizeof(GLfloat), indices.data());
//
//    pyramid->add_submesh(0, 3, new xe::ColorMaterial(   textures_ptr, 0) );
//    pyramid->add_submesh(3, 6, new xe::ColorMaterial(   textures_ptr, 1) );
//    pyramid->add_submesh(6, 9, new xe::ColorMaterial(   textures_ptr, 2) );
//    pyramid->add_submesh(9, 12, new xe::ColorMaterial(  textures_ptr, 3) );
//    pyramid->add_submesh(12, 18, new xe::ColorMaterial( textures_ptr, 4) );

//    add_submesh(pyramid);

    int w, h;
    std::tie(w, h) = frame_buffer_size();
    aspect = (float)w/h;
    fov = glm::pi<float>() / 4.0f;
    near = 0.1f;
    far = 100.0f;

    camera_ -> look_at(
                glm::vec3(2.0f, 2.0f, 3.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f));
    camera_ -> perspective(fov, aspect, near, far);

    // transformation uniforms
    glGenBuffers(1, &transformation);
    glBindBuffer(GL_UNIFORM_BUFFER, transformation);
    glBufferData(GL_UNIFORM_BUFFER, 64, nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, transformation);

//    // indices
//    GLuint indicesId;
//    glGenBuffers(1, &indicesId);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesId);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//    // Generating the buffer and loading the vertex data into it.
//    GLuint v_buffer_handle;
//    glGenBuffers(1, &v_buffer_handle);
//    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);
//    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // This setups a Vertex Array Object (VAO) that  encapsulates the state of all vertex buffers needed for rendering
//    glGenVertexArrays(1, &vao_);
//    glBindVertexArray(vao_);
//    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesId);

    // This indicates that the data for attribute 0 should be read from a vertex buffer.
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0));
//
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(float)));

//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);

    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);
    glViewport(0, 0, w, h);

    glUseProgram(program);
}

//This functions is called every frame and does the actual rendering.
void SimpleShapeApplication::frame() {

    glm::mat4 M(1.0f);
    auto PVM = camera_->projection() * camera_->view() * M;

    glBindBuffer(GL_UNIFORM_BUFFER, transformation);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4),&PVM[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    for (auto m: meshes_) {
        m->draw();
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    //glBindVertexArray(vao_);
    //glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, nullptr);
    //glBindVertexArray(0);

}

void SimpleShapeApplication::framebuffer_resize_callback(int w, int h) {
    Application::framebuffer_resize_callback(w, h);
    glViewport(0,0,w,h);
    aspect = (float) w / h;
    P = glm::perspective(fov, aspect, near, far);
}

void SimpleShapeApplication::scroll_callback(double xoffset, double yoffset) {
    Application::scroll_callback(xoffset, yoffset);
    camera()->zoom(yoffset / 20.0f);
}

void SimpleShapeApplication::cursor_position_callback(double x, double y) {
    Application::cursor_position_callback(x, y);
    if (controler_) {
        controler_->mouse_moved(x, y);
    }
}

void SimpleShapeApplication::mouse_button_callback(int button, int action, int mods) {
    Application::mouse_button_callback(button, action, mods);
    if (controler_) {
        double x, y;
        glfwGetCursorPos(window_, &x, &y);
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            controler_->LMB_pressed(x, y);
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
            controler_->LMB_released(x, y);
    }
}