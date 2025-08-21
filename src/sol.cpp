//
// Created by michiel on 8/20/25.
//

#include <engine/sol.h>

namespace engine {
	Mesh SOL::ReadFile(std::string source)
	{
		std::filesystem::path file = std::filesystem::path(source);
		std::string fileType = file.extension().string();
		
		if (fileType == ".obj")
			return ReadObj(file.string());
	}
	
	
	Mesh SOL::ReadObj(std::string source)
	{
		// initialize all temporary storages
		std::vector<glm::vec3> vertexPositions;
		std::vector<glm::vec3> vertexNormals;
		std::vector<glm::vec2> textureCoordinates;
		
		std::vector<Vertex> resultVertices;
		std::vector<unsigned int> resultIndices;
		
		std::unordered_map<std::string, Material> mtlMaterials;
		
		Mesh mesh;
		Material usedMaterial {};
		bool usingMaterial = false;
		
		// open the file
		std::ifstream file(source);
		if (!file.is_open())
		{
			std::cerr << "Error opening file " << source << std::endl;
		}
		
		std::string line;
		
		while (getline(file, line))
		{
			std::istringstream ss(line);
			std::string prefix;
			ss >> prefix;
			
			if (prefix == "v") // vertex position
			{
				float x, y, z;
				ss >> x >> y >> z;
				vertexPositions.emplace_back(x, y, z);
			} else if (prefix == "vn") // vertex normal
			{
				float x, y, z;
				ss >> x >> y >> z;
				vertexNormals.emplace_back(x, y, z);
			} else if (prefix == "vt")
			{
				float x, y;
				ss >> x >> y;
				textureCoordinates.emplace_back(x, y);
			} else if (prefix == "f")
			{
				std::vector<Vertex> faces; // store all the newly generated vertices
				std::string face;
				while (ss >> face) // loop through all faces (v/vt/vn)
				{
					std::istringstream fs(face);
					int v, t, n;
					t = -1;
					n = -1;
					fs >> v; // read the vertex position, as this is always the first item.
					
					// check if any more items exist
					if (fs.peek() == '/')
					{
						fs.get(); // remove the '/'
						
						// check if there is a texture index
						if (fs.peek() != '/')
							fs >> t; // read the texture index
						
						// check if there is a vertex normal index
						if (fs.peek() == '/')
						{
							fs.get(); // remove the '/'
							fs >> n; // read the vertex normal
						}
					}
					
					glm::vec2 texCoord(glm::vec2(0));
					glm::vec3 normal(glm::vec3(0));
					if (t != -1)
						texCoord = textureCoordinates[t - 1];
					if (n != -1)
						normal = vertexNormals[n - 1];
					
					// create and push back the new Vertex
					Vertex vertex {
							vertexPositions[v - 1],
							normal = normal,
							texCoord = texCoord,
					};
					faces.push_back(vertex);
				}
				
				// generate a list of indices
				// this can be done by using the first (v0), last used (vL) and current (vC) index
				int vL(1);
				for (int vC = 2; vC < faces.size(); vC++)
				{
					resultIndices.push_back(resultVertices.size()); // v0
					resultIndices.push_back(resultVertices.size() + vL);
					resultIndices.push_back(resultVertices.size() + vC);
					vL = vC;
				}
				
				// push all newly generated vertices onto the result stack
				resultVertices.insert(resultVertices.end(), faces.begin(), faces.end());
			} else if (prefix == "mtllib")
			{
				std::string name;
				ss >> name;
				std::filesystem::path filePath(source);
				std::filesystem::path parentPath = filePath.parent_path();
				
				mtlMaterials = ReadMTL(parentPath.append(name).string());
				for (auto mtlMaterial : mtlMaterials)
				{
					std::cout << "Key: " << mtlMaterial.first << ", Value: " << mtlMaterial.second.specularExponent << std::endl;
				}
			} else if (prefix == "usemtl") // selecting a material
			{
				
				if (usingMaterial) // if a material has already been selected
				{
					// save the material and vertices
					// and store it into the mesh
					SubMesh subMesh (usedMaterial, resultVertices, resultIndices);
					mesh.addSubMeshSilent(subMesh);
				}
				
				usingMaterial = true;
				
				std::string name;
				ss >> name;
				usedMaterial = mtlMaterials[name];
			}
		}
		
		SubMesh subMesh (usedMaterial, resultVertices, resultIndices);
		mesh.addSubMeshSilent(subMesh);
		
		return mesh;
	}
	
	std::unordered_map<std::string, Material> SOL::ReadMTL(std::string source)
	{
		std::cout << source << std::endl;
		
		std::unordered_map<std::string, Material> materials;
		
		std::ifstream file(source);
		if (!file.is_open())
		{
			std::cerr << "Error opening file " << source << std::endl;
			return materials;
		}
		
		std::string line;
		
		std::string currentMTL;
		Material currentMaterial {};
		
		while (getline(file, line))
		{
			std::istringstream ss (line);
			std::string prefix;
			ss >> prefix;
			
			if (prefix == "newmtl")
			{
				if (!currentMTL.empty())
					materials[currentMTL] = currentMaterial;
				
				ss >> currentMTL;
			} else if (prefix == "Ka")
			{
				float r, g, b;
				ss >> r >> g >> b;
				currentMaterial.ambientColor = glm::vec3(r, g, b);
			} else if (prefix == "Kd")
			{
				float r, g, b;
				ss >> r >> g >> b;
				currentMaterial.diffuseColor = glm::vec3(r, g, b);
			} else if (prefix == "Ks")
			{
				float r, g, b;
				ss >> r >> g >> b;
				currentMaterial.specularColor = glm::vec3(r, g, b);
			} else if (prefix == "Ns")
			{
				float exponent;
				ss >> exponent;
				currentMaterial.specularExponent = exponent;
			}
		}
		
		if (!currentMTL.empty())
			materials[currentMTL] = currentMaterial;
		
		return materials;
	}
}
