//
// Created by michiel on 8/29/25.
//

#ifndef ENGINE_SCALE_PRINTER_H
#define ENGINE_SCALE_PRINTER_H

#include <engine/component.h>

namespace engine {
	class ScalePrinter : public Component
	{
	public:
		ScalePrinter() = default;
		
		static Component *create(const std::vector<std::string> args);
		static bool registered;
		
		void update(GLFWwindow *window) override;
	};
	
	Component *ScalePrinter::create(const std::vector<std::string> args)
	{
		return new ScalePrinter();
	}
	bool ScalePrinter::registered = []{
		ComponentFactory::registerType("scaleprnt", &ScalePrinter::create);
		return true;
	}();
	
	void ScalePrinter::update(GLFWwindow *window)
	{
		std::cout << "Scale: " << transform->globalSize().x << ',' <<  transform->globalSize().y << ',' <<  transform->globalSize().z << std::endl;
	}
}

#endif //ENGINE_SCALE_PRINTER_H
