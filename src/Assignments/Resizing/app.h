#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "Application/application.h"
#include "Application/utils.h"
#include "glad/gl.h"

class SimpleShapeApplication : public xe::Application
{
public:
    SimpleShapeApplication(int width, int height, std::string title, bool debug) : Application(width, height, title, debug) {}

    void init() override;

    void frame() override;

    void framebuffer_resize_callback(int w, int h) override;

private:
    GLuint vao_;
    float fov;
    float aspect;
    float near;
    float far;
    glm::mat4 P;
    glm::mat4 V;
    GLuint transformation;
};