#ifndef EVENT_HANDLE_UTILS_H
#define EVENT_HANDLE_UTILS_H
#include <iostream>
#include <sstream>
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace {
    const char* WINDOW_TITLE = "OepnGL";
};

void ShowFPS(GLFWwindow* window)
{
    static double previous_seconds = 0.0;
    static int frame_count = 0;
    double elapse_seconds;
    double current_seconds = glfwGetTime();

    elapse_seconds = current_seconds - previous_seconds;
    if (elapse_seconds > 0.25)
    {
        previous_seconds = current_seconds;
        double fps = (double)frame_count / elapse_seconds;
        double ms_per_frame = 1000.0 / fps;

        std::ostringstream outs;
        outs.precision(3);
        outs << std::fixed << WINDOW_TITLE << "  " << "FPS: " << fps << " " << "Frame Time: " << ms_per_frame << "ms" << std::endl;
        glfwSetWindowTitle(window, outs.str().c_str());
        frame_count = 0;
    }
    frame_count++;
}

#endif
