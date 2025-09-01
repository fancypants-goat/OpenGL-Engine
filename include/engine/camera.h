#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "transform.h"


namespace engine
{
    class Camera
    {
        public:
            enum Type {
                Orthographic,
                Perspective,
            } type;
		
			Camera();
            Camera(Type type);
            
            void updateCamera();
            
            glm::mat4 calculateView();
            glm::mat4 orthoProjection(glm::vec2 viewport);
            glm::mat4 perspectiveProjection(glm::vec2 viewport);
            glm::mat4 cameraProjection(glm::vec2 viewport);
            
            glm::vec2 size;
            float fovy;
            float nearPlane;
            float farPlane;
			
			Transform transform;
            
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
