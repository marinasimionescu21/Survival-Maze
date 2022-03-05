#pragma once

#include "utils/glm_utils.h"


namespace transform3D
{
    // Translate matrix
    inline glm::mat4 Translate(float translateX, float translateY, float translateZ)
    {
        // TODO(student): Implement the translation matrix
        return glm::mat4(1,0,0,0, 0,1,0,0, 0,0,1,0, translateX,translateY,translateZ,1);

    }

    // Scale matrix
    inline glm::mat4 Scale(float scaleX, float scaleY, float scaleZ)
    {
        // TODO(student): Implement the scaling matrix
        return glm::mat4(scaleX,0,0,0, 0,scaleY,0,0, 0,0,scaleZ,0, 0,0,0,1);

    }

    // Rotate matrix relative to the OZ axis
    inline glm::mat4 RotateOZ(float radians)
    {
        // TODO(student): Implement the rotation matrix
        return glm::mat4(cos(radians),sin(radians),0,0, -sin(radians),cos(radians),0,0, 0,0,1,0, 0,0,0,1);

    }

    // Rotate matrix relative to the OY axis
    inline glm::mat4 RotateOY(float radians)
    {
        // TODO(student): Implement the rotation matrix
        return glm::mat4(cos(radians),0,-sin(radians),0, 0,1,0,0, sin(radians),0,cos(radians),0, 0,0,0,1);

    }

    // Rotate matrix relative to the OX axis
    inline glm::mat4 RotateOX(float radians)
    {
        // TODO(student): Implement the rotation matrix
        return glm::mat4(1,0,0,0, 0,cos(radians),sin(radians),0, 0,-sin(radians),cos(radians),0, 0,0,0,1);

    }

    inline glm::mat3 Translate2D(float translateX, float translateY)
    {
        return glm::mat3(
            1.f, 0.f, 0.f,
            0.f, 1.f, 0.f,
            translateX, translateY, 1
        );
    }

    // Scale matrix
    inline glm::mat3 Scale2D(float scaleX, float scaleY)
    {
        {
            return glm::mat3(
                scaleX, 0.f, 0.f,
                0.f, scaleY, 0.f,
                0.f, 0.f, 1.f
            );
        }
    }
}   // namespace transform3D
