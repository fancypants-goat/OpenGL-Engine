//
// Created by michiel on 8/19/25.
//

#include <engine/object_loader.h>

#include <glm/glm.hpp>

namespace engine {
	ObjectLoader::ObjectLoader(std::string source)
			: source(std::move(source))
	{
	}
	
	void
	ObjectLoader::LoadVertices()
	{
		// initialize all temporary storages
		std::vector<glm::vec3> vertexPositions;
		std::vector<glm::vec3> vertexNormals;
		std::vector<glm::vec2> textureCoordinates;
		
		std::vector<Vertex> resultVertices;
		std::vector<unsigned int> resultIndices;
		
		// open the file
		std::ifstream file(source);
		
		if (!file.is_open())
		{
			std::cerr << "Error opening file " << source << std::endl;
			return;
		}
		
		// will store each line of the file
		std::string line;
		
		// loop through each line in the file
		while (getline(file, line))
		{
			std::istringstream ss(line);
			std::string prefix;
			ss >> prefix;
			
			if (prefix == VERTEX_POSITION_INDICATOR)
			{
				float x, y, z;
				ss >> x >> y >> z;
				vertexPositions.emplace_back(x, y, z);
			} else if (prefix == VERTEX_NORMAL_INDICATOR)
			{
				float x, y, z;
				ss >> x >> y >> z;
				vertexNormals.emplace_back(x, y, z);
			} else if (prefix == VERTEX_TEXTURE_COORDINATE_INDICATOR)
			{
				float x, y;
				ss >> x >> y;
				textureCoordinates.emplace_back(x, y);
			} else if (prefix == VERTEX_FACES_INDICATOR)
			{
				std::vector<std::string> parts;
				std::string part;
				while (ss >> part)
				{
					parts.push_back(part);
				}
				
				// if the line has 3 faces defined
				if (parts.size() == 3)
				{
					resultIndices.push_back(resultVertices.size());
					resultIndices.push_back(resultVertices.size() + 1);
					resultIndices.push_back(resultVertices.size() + 2);
				} else if (parts.size() == 4)
				{
					// triangle 1
					resultIndices.push_back(resultVertices.size() + 0);
					resultIndices.push_back(resultVertices.size() + 1);
					resultIndices.push_back(resultVertices.size() + 2);
					// triangle 2
					resultIndices.push_back(resultVertices.size() + 0);
					resultIndices.push_back(resultVertices.size() + 2);
					resultIndices.push_back(resultVertices.size() + 3);
				} // not handling more yet
				
				for (std::string face : parts)
				{
					std::istringstream fs(face);
					int v, t, n;
					t = -1;
					n = -1;
					fs >> v;
					
					if (fs.peek() == '/') {
						fs.get(); // consume first '/'
						if (fs.peek() != '/') {
							fs >> t; // read texture if it exists
						}
						if (fs.peek() == '/') {
							fs.get(); // consume second '/'
							fs >> n; // read normal
						}
					}
					
					glm::vec2 texCoord (glm::vec2(0));
					glm::vec3 normal (glm::vec3(0));
					if (t != -1)
						texCoord = textureCoordinates[t - 1];
					if (n != -1)
						normal = vertexNormals[n - 1];
					
					// create the Vertex and send it through
					Vertex vertex {
							vertexPositions[v - 1],
							normal = normal,
							texCoord = texCoord
					};
					resultVertices.push_back(vertex);
				}
			}
		} // while
		
		vertices = resultVertices;
		indices = resultIndices;
	}
	
	Mesh ObjectLoader::LoadAsMesh()
	{
		if (vertices.empty())
			LoadVertices(); // make sure the vertices are loaded before usage
		
		return Mesh (vertices, indices, Mesh::StorageType::Static);
	}
} // engine