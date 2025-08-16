#include "camera.h"

#include <iostream>

namespace engine
{
    Camera *Camera::s_main {nullptr};

    Camera::Camera(Type type)
        : type(type)
    {
        updateCamera();
    }

    void Camera::updateCamera()
    {
        glm::vec3 worldUp (0,1,0);
        
        direction = glm::vec3(cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x))
                            , sin(glm::radians(rotation.x))
                            , sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x)));
        direction = glm::normalize(direction);
        forwards = glm::normalize(glm::vec3(direction.x, 0, direction.z));
        right = glm::normalize(glm::cross(direction, worldUp));
        up = glm::normalize(glm::cross(right, direction));
    }

    glm::mat4 Camera::calculateView()
    {
        glm::mat4 view;
        
        view = glm::lookAt(position, position + direction, up);
        return view;
    }

    glm::mat4 Camera::orthoProjection()
    {
        return glm::ortho(0.f, size.x, 0.f, size.y, nearPlane, farPlane);
    }

    glm::mat4 Camera::perspectiveProjection(glm::vec2 viewport)
    {
        return glm::perspective(glm::radians(fovy), viewport.x/viewport.y, nearPlane, farPlane);
    }

    glm::mat4 Camera::cameraProjection(glm::vec2 viewport)
    {
        glm::mat4 projection;
        glm::mat4 view;
        if (type == Orthographic)
            projection = orthoProjection();
        else if (type == Perspective)
            projection = perspectiveProjection(viewport);
        
        view = calculateView();
        return projection * view;
    }

    void Camera::set_depthPlanes(float newNear, float newFar)
    {
        nearPlane = newNear;
        farPlane = newFar;
    }

    glm::vec3 Camera::get_direction() { return direction; }
    glm::vec3 Camera::get_forwards() { return forwards; }
    glm::vec3 Camera::get_right() { return right; }
    glm::vec3 Camera::get_up() { return up; }
    
    Camera *Camera::get_main() { return s_main; }
    void Camera::set_main(Camera *camera)
    {
        s_main = camera;
    }
}
