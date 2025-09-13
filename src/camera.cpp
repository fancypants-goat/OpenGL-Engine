#include <engine/camera.h>

#include <iostream>

namespace engine
{
    Camera* Camera::s_main{nullptr};

    Camera::Camera(Type type)
        : type(type), transform(math::vec3::zero, math::vec3::zero, math::vec3::zero)
    {
        updateCamera();
    }

    Camera::Camera()
        : type(), transform(math::vec3::zero, math::vec3::zero, math::vec3::zero)
    {
    }

    void Camera::updateCamera()
    {
        direction = math::vec3(
            sin(glm::radians(transform.globalRotation().y)) * cos(glm::radians(transform.globalRotation().x)),
            sin(glm::radians(transform.globalRotation().x)),
            -cos(glm::radians(transform.globalRotation().y)) * cos(glm::radians(transform.globalRotation().x)));

        direction.normalize();

        forwards = math::vec3(direction.x, 0, direction.z).normalized();

        right = math::cross(direction, math::vec3::up).normalized();
        up = math::cross(right, direction).normalized();
    }

    glm::mat4 Camera::calculateView() const
    {
        return glm::lookAt(transform.globalPosition().toGLM(), (transform.globalPosition() + direction).toGLM(),
                           up.toGLM());
    }

    glm::mat4 Camera::orthoProjection(glm::vec2 viewport) const
    {
        viewport = glm::normalize(viewport);

        const float width = size.x * viewport.x; /*std::cout << "Width: " << width << std::endl;*/
        const float height = size.y * viewport.y;

        return glm::ortho(-width / 2, width / 2, -height / 2, height / 2, nearPlane, farPlane);
    }

    glm::mat4 Camera::perspectiveProjection(const glm::vec2 viewport) const
    {
        return glm::perspective(glm::radians(fovy), viewport.x / viewport.y, nearPlane, farPlane);
    }

    glm::mat4 Camera::cameraProjection(const glm::vec2 viewport) const
    {
        glm::mat4 projection;
        if (type == Orthographic)
            projection = orthoProjection(viewport);
        else if (type == Perspective)
            projection = perspectiveProjection(viewport);

        const glm::mat4 view = calculateView();
        return projection * view;
    }

    void Camera::set_depthPlanes(float newNear, float newFar)
    {
        nearPlane = newNear;
        farPlane = newFar;
    }

    math::vec3 Camera::get_direction()
    {
        return direction;
    }

    math::vec3 Camera::get_forwards()
    {
        return forwards;
    }

    math::vec3 Camera::get_right()
    {
        return right;
    }

    math::vec3 Camera::get_up()
    {
        return up;
    }

    Camera* Camera::get_main()
    {
        if (s_main == nullptr)
        {
            std::cerr
                << "Tried accessing main camera, but it is not set! Try setting the main camera with Camera::set_main(*camera)."
                << std::endl;
            return new Camera(Camera::Orthographic);
        }
        return s_main;
    }

    void Camera::set_main(Camera* camera)
    {
        s_main = camera;
    }
}
