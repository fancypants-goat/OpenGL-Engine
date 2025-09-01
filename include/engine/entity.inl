
namespace engine {
	template<typename T>
	T *Entity::addComponent(T *component)
	{
		if (!std::is_base_of<Component, T>::value)
		{
			std::cerr << typeid(T).name() << " does not inherit Component class!" << std::endl;
			return component;
		}
		
		component->entity = this;
		component->transform = &transform;
		m_components.push_back(component);
		
		return component;
	}
	
	
	template<typename T>
	T *Entity::getComponent(bool includeDisabled)
	{
		for (auto &c : m_components)
			if (auto casted = dynamic_cast<T *>(c))
				if (includeDisabled || casted->enabled)
					return casted;
		
		return nullptr;
	}
}