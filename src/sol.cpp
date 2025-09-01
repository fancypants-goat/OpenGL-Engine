//
// Created by michiel on 8/20/25.
//

#include <engine/sol.h>

#include <engine/resources.h>

#include <engine/camera.h>
#include <engine/component_factory.h>

namespace engine {
	Mesh SOL::readMeshFile(std::string source)
	{
		std::filesystem::path file = std::filesystem::path(Resources::get(source));
		std::string fileType = file.extension().string();
		
		if (fileType == ".obj")
			return readObj(file.string());
	}
	
	Mesh SOL::readObj(std::string source)
	{
		source = Resources::get(source);
		
		// initialize all temporary storages
		std::vector<glm::vec3> vertexPositions;
		std::vector<glm::vec3> vertexNormals;
		std::vector<glm::vec2> textureCoordinates;
		
		std::vector<Vertex> resultVertices;
		std::vector<unsigned int> resultIndices;
		unsigned int minIndex(0);
		unsigned int maxIndex(1);
		
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
					
					auto texCoord(glm::vec2(0));
					auto normal(glm::vec3(0));
					if (t != -1)
						texCoord = textureCoordinates[t - 1];
					if (n != -1)
						normal = vertexNormals[n - 1];
					
					// create and push back the new Vertex
					Vertex vertex {
							vertexPositions[v - 1],
							normal,
							texCoord,
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
				
				auto newMaterials = readMTL(parentPath.append(name).string());
				mtlMaterials.insert(newMaterials.begin(), mtlMaterials.end());
			} else if (prefix == "usemtl") // selecting a material
			{
				
				if (usingMaterial) // if a material has already been selected
				{
					// save the material and vertices
					// and store it into the mesh
					
					// get the vertices used for this mesh:
					SubMesh subMesh(usedMaterial, resultVertices, resultIndices);
					mesh.addSubMesh(subMesh);
					
					resultIndices.erase(resultIndices.begin(), resultIndices.end());
					resultVertices.erase(resultVertices.begin(), resultVertices.end());
				}
				
				usingMaterial = true;
				
				std::string name;
				ss >> name;
				usedMaterial = mtlMaterials[name];
			}
		}
		
		SubMesh subMesh(usedMaterial, resultVertices, resultIndices);
		mesh.addSubMesh(subMesh);
		
		return mesh;
	}
	
	std::unordered_map<std::string, Material> SOL::readMTL(std::string source)
	{
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
			std::istringstream ss(line);
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
			} else if (prefix == "d")
			{
				ss >> currentMaterial.alpha;
			} else if (prefix == "Tr") // 'd' but inverted: 1 - d
			{
				float alpha;
				ss >> alpha;
				currentMaterial.alpha = 1 - alpha;
			} else if (prefix == "Tf") // transparency color. ignore for now.
			{}
			else if (prefix == "Ni") // index of refraction. ignore for now
			{}
			else if (prefix == "illum") // illumination models. fucking raytracing shit
			{}
		}
		
		if (!currentMTL.empty())
			materials[currentMTL] = currentMaterial;
		
		return materials;
	}
	
	
	Scene *SOL::readScene(std::string source)
	{
		Scene *scene = new Scene();
		
		RawSceneData rawData = readSceneRaw(source);
		
		scene->m_rootEntities = rawData.rootEntities;
		scene->m_drawables = rawData.drawables;
		scene->m_tokenizedEntities = rawData.tokenizedEntities;
		scene->m_tokenizedDrawables = rawData.tokenizedDrawables;
		scene->name = rawData.name;
		
		return scene;
	}
	
	std::vector<std::string> SOL::tokenizeArgs(std::string line)
	{
		std::vector<std::string> tokens;
		std::string current;
		bool inGroup = false;
		
		for (char c : line)
		{
			if (c == '(')
			{
				inGroup = true;
				current += c;
			} else if (c == ')' && inGroup)
			{
				inGroup = false;
				current += c;
				tokens.push_back(current);
				current = "";
			} else if (c == ' ' && !inGroup && current != "")
			{
				tokens.push_back(current);
				current = "";
			} else if (c != ' ')
			{
				current += c;
			}
		}
		
		if (current != "")
			tokens.push_back(current);
		
		return tokens;
	}
	
	glm::vec3 SOL::readVec3(std::istringstream &ss)
	{
		glm::vec3 vector;
		// remove all whitespaces
		while (ss && std::isspace(ss.peek())) ss.get();
		
		if (ss.peek() == '(') // a vector (defined to be vec3)
		{
			ss.get();
			ss >> vector.x;
			ss.ignore(1, ',');
			ss >> vector.y;
			ss.ignore(1, ',');
			ss >> vector.z;
			ss.ignore(1, ')');
		} else
		{
			float scalar;
			ss >> scalar;
			vector = glm::vec3(scalar);
		};
		return vector;
	}
	
	std::string SOL::readStringLiteral(std::istringstream &ss)
	{
		while (ss && std::isspace(ss.peek())) ss.get(); // skip spaces
		
		if (ss.peek() != '"')
		{
			throw std::runtime_error("Expected opening quote for string literal");
		}
		ss.get(); // consume opening quote
		
		std::string result;
		std::getline(ss, result, '"'); // read until closing quote
		
		return result;
	}
	
	glm::vec3 SOL::parseVec3(std::string toParse)
	{
		if (toParse[0] == '(')
		{
			std::remove(toParse.begin(), toParse.end(), '(');
			std::vector<std::string> parts;
			std::stringstream ss(toParse);
			std::string item;
			
			while (std::getline(ss, item, ','))
			{
				parts.push_back(item);
			}
			
			return glm::vec3(std::stof(parts[0]), std::stof(parts[1]), std::stof(parts[2]));
		} else
		{
			return glm::vec3(std::stof(toParse));
		}
	}
	
	SOL::RawSceneData SOL::readSceneRaw(std::string source)
	{
		enum class ObjectType
		{
			None,
			Entity,
			Renderer,
			Camera,
		};
		
		
		source = Resources::get(source);
		
		RawSceneData rawSceneData;
		
		ObjectType currentType;
		
		std::string currentID;
		
		bool enabledObject = true;
		
		// entity stuff
		std::string parentID;
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 size;
		glm::vec3 color;
		std::vector<std::vector<std::string>> components;
		
		// renderer stuff
		std::string vertPath;
		std::string fragPath;
		std::string meshPath;
		std::string texturePath;
		std::vector<std::string> entityIDs;
		
		// camera stuff
		bool isMain = false;
		std::string cameraType;
		glm::vec3 camPosition;
		glm::vec3 camRotation;
		float fovy;
		glm::vec2 orthoSize;
		float near = 0.1;
		float far = 100;
		
		// open the file
		std::ifstream file(source);
		if (!file.is_open())
		{
			std::cerr << "Error opening file " << source << std::endl;
		}
		
		std::string line;
		int lineNum = 1;
		
		while (getline(file, line))
		{
			
			std::istringstream ss(line);
			std::string prefix;
			ss >> prefix;
			
			if (line.empty() || prefix[0] == '#')
			{
				lineNum++;
				continue;
			}
			
			// scene thing
			if (prefix == "scene")
			{
				ss >> rawSceneData.name;
			}
				// CAMERA ATTRIBUTES
			else if (prefix == "cam")
			{
				ss >> currentID >> cameraType;
				camPosition = readVec3(ss);
				camRotation = readVec3(ss);
				
				currentType = ObjectType::Camera;
			} else if (prefix == "fov" && currentType == ObjectType::Camera)
			{
				ss >> fovy;
			} else if (prefix == "size" && currentType == ObjectType::Camera)
			{
				ss >> size.x >> size.y;
			} else if (prefix == "near" && currentType == ObjectType::Camera)
			{
				ss >> near;
			} else if (prefix == "far" && currentType == ObjectType::Camera)
			{
				ss >> far;
			} else if (prefix == "depth" && currentType == ObjectType::Camera)
			{
				ss >> near >> far;
			}
				// OBJECT ATTRIBUTES
			else if (prefix == "o")
			{
				ss >> currentID;
				
				position = readVec3(ss);
				rotation = readVec3(ss);
				size = readVec3(ss);
				
				currentType = ObjectType::Entity;
			} else if (prefix == "p" && currentType == ObjectType::Entity)
			{
				ss >> parentID;
			} else if (prefix == "color" && currentType == ObjectType::Entity)
			{
				ss >> color.x >> color.y >> color.z;
			} else if (prefix == "add" && currentType == ObjectType::Entity)
			{
				auto tokens = tokenizeArgs(line.substr(3));
				components.push_back(tokens);
			}
				// RENDERER ATTRIBUTES
			else if (prefix == "r")
			{
				std::string id;
				ss >> id;
				
				auto r = MeshRenderer();
				currentID = id;
				currentType = ObjectType::Renderer;
			} else if (prefix == "mesh" && currentType == ObjectType::Renderer)
			{
				meshPath = Resources::get(readStringLiteral(ss));
			} else if (prefix == "vert" && currentType == ObjectType::Renderer)
			{
				vertPath = Resources::get(readStringLiteral(ss));
			} else if (prefix == "frag" && currentType == ObjectType::Renderer)
			{
				fragPath = Resources::get(readStringLiteral(ss));
			} else if (prefix == "t" && currentType == ObjectType::Renderer)
			{
				texturePath = Resources::get(readStringLiteral(ss));
			} else if (prefix == "add" && currentType == ObjectType::Renderer)
			{
				std::string entityID;
				ss >> entityID;
				entityIDs.push_back(entityID);
			}
				// GLOBAL ATTRIBUTES
			else if (prefix == "init")
			{
				if (currentType == ObjectType::Renderer)
				{
					auto m = new MeshRenderer(readMeshFile(meshPath),
											  new Shader(vertPath, fragPath),
											  texturePath != ""? new Texture(texturePath)
															   : nullptr);
					m->enabled = enabledObject;
					
					for (const auto &id : entityIDs)
					{
						m->addEntity(rawSceneData.tokenizedEntities[id]);
					}
					
					rawSceneData.tokenizedDrawables[currentID] = m;
					rawSceneData.drawables.push_back(m);
				} else if (currentType == ObjectType::Entity)
				{
					auto e = new Entity(position, rotation, size);
					e->color = color;
					e->isActive = enabledObject;
					e->name = currentID;
					rawSceneData.tokenizedEntities[currentID] = e;
					
					if (parentID.empty())
						rawSceneData.rootEntities.push_back(rawSceneData.tokenizedEntities[currentID]);
					else
						e->transform.set_parent(rawSceneData.tokenizedEntities[parentID]);
					
					for (auto &tokens : components)
					{
						e->addComponent(ComponentFactory::create(tokens[0],
																 std::vector<std::string>(
																		 tokens.begin() + 1,
																		 tokens.end())));
					}
				} else if (currentType == ObjectType::Camera)
				{
					Camera::Type type;
					if (cameraType == "perspective")
						type = Camera::Perspective;
					else if (cameraType == "ortho" || cameraType == "orthographic")
						type = Camera::Orthographic;
					else
					{
						std::cerr << "No valid camera type given in camera " << currentID
								  << ". Must be either perspective or ortho(graphic)" << std::endl;
						type = Camera::Orthographic;
					}
					
					auto c = new Camera(type);
					c->fovy = fovy;
					c->size = orthoSize;
					c->transform.position = camPosition;
					c->transform.rotation = camRotation;
					c->set_depthPlanes(near, far);
					if (isMain) Camera::set_main(c);
				}
				
				color = glm::vec3(1);
				parentID = "";
				components.clear();
				
				vertPath = "";
				fragPath = "";
				meshPath = "";
				texturePath = "";
				entityIDs.clear();
				
				currentID = "";
				currentType = ObjectType::None;
				enabledObject = true;
			} else if (prefix == "tag")
			{
				std::string tag;
				ss >> tag;
				
				if (tag == "main" && currentType == ObjectType::Camera)
					isMain = true;
				else if (tag == "enabled" && currentType != ObjectType::Camera)
					enabledObject = true;
				else if (tag == "disabled" && currentType != ObjectType::Camera)
					enabledObject = false;
			} else if (prefix == "include")
			{
				std::string path = readStringLiteral(ss);
				std::filesystem::path sourceRoot = std::filesystem::path(source).parent_path();
				
				std::filesystem::path pathInSourceRoot = sourceRoot / path;
				if (exists(pathInSourceRoot))
					path = pathInSourceRoot.string();
				else
					path = Resources::get(path);
				
				RawSceneData included = readSceneRaw(path);
				
				rawSceneData.tokenizedEntities.insert(included.tokenizedEntities.begin(),
													  included.tokenizedEntities.end());
				rawSceneData.tokenizedDrawables.insert(included.tokenizedDrawables.begin(),
													   included.tokenizedDrawables.end());
				rawSceneData.rootEntities.insert(rawSceneData.rootEntities.end(), included.rootEntities.begin(),
												 included.rootEntities.end());
				rawSceneData.drawables.insert(rawSceneData.drawables.end(), included.drawables.begin(),
											  included.drawables.end());
			} else
			{
				std::cerr << "Unknown attribute in " << source << " in line " << lineNum << ": "
						  << line << std::endl;
			}
			
			lineNum++;
		}
		
		return rawSceneData;
	}
}
