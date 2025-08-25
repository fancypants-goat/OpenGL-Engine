//
// Created by michiel on 8/25/25.
//

#ifndef ENGINE_TIME_H
#define ENGINE_TIME_H

namespace engine {
	class Time
	{
	public:
		Time() = delete;
		
		static float runTime;
		static float timeScale;
		static float deltaTime;
		static float physicsDeltaTime;
	};
}

#endif //ENGINE_TIME_H
