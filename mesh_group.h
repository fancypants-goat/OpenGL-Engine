//
// Created by michiel on 8/14/25.
//

#ifndef ENGINE_MESH_GROUP_H
#define ENGINE_MESH_GROUP_H

#include "mesh.h"
#include "transform.h"
#include <glm/glm.hpp>
#include <vector>

namespace engine {
	
	class MeshGroup
	{
	public:
		MeshGroup(Mesh *mesh, std::vector<Transform> transforms);
		explicit MeshGroup(Mesh *mesh);
		
		void addTransform(Transform transform);
		void upload();
		void draw();
	private:
		void initialize();
		
		Mesh *m_mesh;
		std::vector<Transform> m_transforms;
		
		unsigned int m_vbo;
	};
	
} // engine

#endif //ENGINE_MESH_GROUP_H
