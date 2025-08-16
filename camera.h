#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace engine
{
    class Camera
    {
        public:
            enum Type {
                Orthographic,
                Perspective,
            } type;
            
            Camera(Type type);
            
            void updateCamera();
            
            glm::mat4 calculateView();
            glm::mat4 orthoProjection();
            glm::mat4 perspectiveProjection(glm::vec2 viewport);
            glm::mat4 cameraProjection(glm::vec2 viewport);
            
            glm::vec3 position;
            glm::vec3 rotation;
            
            glm::vec2 size;
            float fovy;
            float nearPlane;
            float farPlane;
            
            void set_depthPlanes(float nearPlane, float farPlane);
            
            glm::vec3 get_direction();
            glm::vec3 get_forwards();
            glm::vec3 get_right();
            glm::vec3 get_up();
            
            static Camera *get_main();
            static void set_main(Camera *camera);
        private:
            static Camera *s_main;
            
            glm::vec3 direction;
            glm::vec3 forwards;
            glm::vec3 right;
            glm::vec3 up;
    };
}

#endif
