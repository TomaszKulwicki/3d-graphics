#define STB_IMAGE_IMPLEMENTATION  1

#include "app.h"
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include "Application/utils.h"
#include "Engine/mesh_loader.cpp"
#include "Engine/Mesh.cpp"
#include "Engine/texture.cpp"
#include "ObjectReader/obj_reader.cpp"

#include "Engine/PhongMaterial.h"

void SimpleShapeApplication::init() {
    set_camera(new Camera);
    set_controler(new CameraControler(camera()));
    auto program = xe::utils::create_program(
            {{GL_VERTEX_SHADER,   std::string(PROJECT_DIR) + "/shaders/base_vs.glsl"},
             {GL_FRAGMENT_SHADER, std::string(PROJECT_DIR) + "/shaders/base_fs.glsl"}});

    if (!program) {
        std::cerr << "Invalid program" << std::endl;
        exit(-1);
    }

    xe::PhongMaterial::init();
    xe::ColorMaterial::init();

    auto pyramid = xe::load_mesh_from_obj(std::string(ROOT_DIR) + "/Models/square.obj", std::string(ROOT_DIR) + "/Models");

    add_submesh(pyramid);

    int w, h;
    std::tie(w, h) = frame_buffer_size();
    aspect = (float)w/h;
    fov = glm::pi<float>() / 4.0f;
    near = 0.1f;
    far = 100.0f;

    camera_ -> look_at(
                glm::vec3(2.0f, 3.0f, 3.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f));
    camera_ -> perspective(fov, aspect, near, far);

    // transformation uniforms
    glGenBuffers(1, &transformation);
    glBindBuffer(GL_UNIFORM_BUFFER, transformation);
    glBufferData(GL_UNIFORM_BUFFER, 600, nullptr, GL_STATIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, transformation);

    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);
    glViewport(0, 0, w, h);

    glUseProgram(program);
}

//This functions is called every frame and does the actual rendering.
void SimpleShapeApplication::frame() {

    glm::mat4 M(1.0f);
    auto PVM = camera_->projection() * camera_->view() * M;
    auto VM = camera_->view();
    auto R = glm::mat3(VM);
    auto N = glm::mat3(glm::cross(R[1], R[2]), glm::cross(R[2], R[0]), glm::cross(R[0], R[1]));

    glBindBuffer(GL_UNIFORM_BUFFER, transformation);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &PVM);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &VM);
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), sizeof(glm::vec3), &N[0]);
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4) + sizeof(glm::vec4), sizeof(glm::vec3), &N[1]);
    glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4) + 2 * sizeof(glm::vec4), sizeof(glm::vec3), &N[2]);
//    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4),&PVM[0]);
//    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &VM[0]);
//    glBufferSubData(GL_UNIFORM_BUFFER, 2*sizeof(glm::mat4), sizeof(glm::mat3), &N[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    for (auto m: meshes_) {
        m->draw();
    }

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

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