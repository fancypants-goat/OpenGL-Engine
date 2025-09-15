#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "transform.h"
#include "math/vec3.h"


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
            explicit Camera(Type type);
            
            void updateCamera();
            
            glm::mat4 calculateView() const;
            glm::mat4 orthoProjection(glm::vec2 viewport) const;
            glm::mat4 perspectiveProjection(glm::vec2 viewport) const;
            glm::mat4 cameraProjection(glm::vec2 viewport) const;
            
            glm::vec2 size;
            float fovy;
            float nearPlane;
            float farPlane;
			
			Transform transform;
            
            void set_depthPlanes(float nearPlane, float farPlane);
            
            math::vec3 get_direction();
            math::vec3 get_forwards();
            math::vec3 get_right();
            math::vec3 get_up();
            
            static Camera *get_main();
            static void set_main(Camera *camera);
        private:
            static Camera *s_main;
            
            math::vec3 direction;
            math::vec3 forwards;
            math::vec3 right;
            math::vec3 up;
    };
}

#endif
