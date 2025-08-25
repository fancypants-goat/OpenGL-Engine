//
// Created by michiel on 8/14/25.
//

#ifndef ENGINE_MESH_H
#define ENGINE_MESH_H

#include <engine/submesh.h>

namespace engine {
	
	class Mesh
	{
	public:
		Mesh(Material material, std::vector<Vertex> vertices,
			 std::vector<unsigned int> indices = {});
		
		explicit Mesh(SubMesh mesh);
		
		Mesh();
		
		void initialize();
		
		void upload();
		
		void addSubMesh(SubMesh subMesh);
		
		std::vector<SubMesh> get_SubMeshes();
	
	private:
		std::vector<SubMesh> m_subMeshes;
	};
	
} // engine

#endif //ENGINE_MESH_H
