#include "camera.h"

#include <iostream>

namespace engine
{
    Camera *Camera::sMain {NULL};

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

    glm::mat4 Camera::get_view()
    {
        glm::mat4 view;
        
        view = glm::lookAt(position, position + direction, up);
        return view;
    }

    glm::mat4 Camera::get_orthoProjection()
    {
        return glm::ortho(0.f, size.x, 0.f, size.y, nearPlane, farPlane);
    }

    glm::mat4 Camera::get_perspectiveProjection(glm::vec2 viewport)
    {
        return glm::perspective(glm::radians(fovy), viewport.x/viewport.y, nearPlane, farPlane);
    }

    glm::mat4 Camera::get_cameraProjection(glm::vec2 viewport)
    {
        glm::mat4 projection;
        glm::mat4 view;
        if (type == Orthographic)
            projection = get_orthoProjection();
        else if (type == Perspective)
            projection = get_perspectiveProjection(viewport);
        
        view = get_view();
        return projection * view;
    }

    void Camera::set_depthPlanes(float nearPlane, float farPlane)
    {
        this->nearPlane = nearPlane;
        this->farPlane = farPlane;
    }

    glm::vec3 Camera::get_direction() { return direction; }
    glm::vec3 Camera::get_forwards() { return forwards; }
    glm::vec3 Camera::get_right() { return right; }
    glm::vec3 Camera::get_up() { return up; }
    
    Camera *Camera::get_main() { return sMain; }
    void Camera::set_main(Camera *camera)
    {
        sMain = camera;
    }
}
