#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Application/application.h"
#include "Application/utils.h"
#include "glad/gl.h"
#include "camera.h"

class SimpleShapeApplication : public xe::Application
{
public:
    SimpleShapeApplication(int width, int height, std::string title, bool debug) : Application(width, height, title, debug) {}

    void init() override;

    void frame() override;

    void framebuffer_resize_callback(int w, int h) override;

    void set_camera(Camera *camera) { camera_ = camera; }

    Camera *camera() const { return camera_; }

private:
    GLuint vao_;
    float fov;
    float aspect;
    float near;
    float far;
    glm::mat4 P;
    glm::mat4 V;
    Camera *camera_;
    GLuint transformation;

    void scroll_callback(double xoffset, double yoffset) override;
};