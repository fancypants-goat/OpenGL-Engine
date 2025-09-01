//
// Created by michiel on 8/29/25.
//
#include "engine/component_factory.h"


namespace engine {
	std::unordered_map<std::string, ComponentFactory::CreateFn>& ComponentFactory::getRegistry() {
		static std::unordered_map<std::string, CreateFn> registry;
		return registry;
	}
	
	void ComponentFactory::registerType(const std::string &name,
										std::function<Component *(const std::vector<std::string>)> fn)
	{
		getRegistry()[name] = fn;
	}
	
	Component *
	ComponentFactory::create(const std::string &name, const std::vector<std::string> &args)
	{
		auto item = getRegistry().find(name);
		
		if (item != getRegistry().end())
			return item->second(args);
		else
			std::cerr << "No registered component with name '" << name
					  << "'. Register component type using ComponentFactory::registerType()!"
					  << std::endl;
		
		return nullptr;
	}
	
}

