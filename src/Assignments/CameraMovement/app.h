#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Application/application.h"
#include "Application/utils.h"
#include "glad/gl.h"
#include "camera.h"
#include "camera_controler.h"

class SimpleShapeApplication : public xe::Application
{
public:
    SimpleShapeApplication(int width, int height, std::string title, bool debug) : Application(width, height, title, debug) {}

    void init() override;

    void frame() override;



    void set_camera(Camera *camera) { camera_ = camera; }

    Camera *camera() const { return camera_; }

    ~SimpleShapeApplication() {
        if (camera_) {
            delete camera_;
        }
    }

    void set_controler(CameraControler *controler) { controler_ = controler; }

private:
    GLuint vao_;
    float fov;
    float aspect;
    float near;
    float far;
    glm::mat4 P;
    glm::mat4 V;
    Camera * camera_;
    GLuint transformation;
    CameraControler * controler_;

    void scroll_callback(double xoffset, double yoffset) override;

    void framebuffer_resize_callback(int w, int h) override;

    void cursor_position_callback(double x, double y);

    void mouse_button_callback(int button, int action, int mods);
};