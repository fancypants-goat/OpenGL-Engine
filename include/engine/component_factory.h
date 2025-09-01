//
// Created by michiel on 8/29/25.
//

#ifndef ENGINE_COMPONENT_FACTORY_H
#define ENGINE_COMPONENT_FACTORY_H

#include <bits/stdc++.h>

namespace engine {
	class Component;
	class ComponentFactory
	{
	public:
		using CreateFn = std::function<Component* (const std::vector<std::string>)>;
		
		static void registerType(const std::string& name, CreateFn fn);
		static Component *create(const std::string &name, const std::vector<std::string> &args);
	private:
		static std::unordered_map<std::string, CreateFn>& getRegistry();
	};
}


#endif //ENGINE_COMPONENT_FACTORY_H
