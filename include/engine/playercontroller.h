//
// Created by michiel on 8/29/25.
//

#ifndef ENGINE_PLAYERCONTROLLER_H
#define ENGINE_PLAYERCONTROLLER_H

#include "box_collider.h"
#include "component.h"

namespace engine {
	class PlayerController : public Component
	{
	public:
		PlayerController(float speed, float jumpStrength);
		
		static Component *create(const std::vector<std::string> &args);
		static bool registered;
		
		void update(GLFWwindow *window) override;
		void jump();
		
		
		float speed;
		float jumpStrength;

		BoxCollider *feetCollider;
	};
}

#endif //ENGINE_PLAYERCONTROLLER_H
