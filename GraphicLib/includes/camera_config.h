#pragma once

#ifndef CAMERA_CONFIG_H
#define CAMERA_CONFIG_H

#include "glm/glm.hpp"
enum KEY_TYPE
{
    KEY_W = 0,
    KEY_S,
    KEY_A,
    KEY_D,
    UNDEFINED
};


const float ROTATE_SENSITIVITY = 0.25f;
const float PAN_BY_MOUSE_SENSITIVITY = 0.0025f;
const float PAN_BY_KEY_SENSITIVITY = 0.1f;
const glm::vec3 WORLD_UP_DIRECTION = glm::vec3(0.0f, 1.0f, 0.0f);


#endif 

