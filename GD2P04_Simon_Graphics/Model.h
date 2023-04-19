#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define TINYOBJLOADER_IMPLEMENTATION
#include <TinyOBJ/tiny_obj_loader.h>


struct VertexFormat
{
public:
	glm::vec3 Position{};
	glm::vec2 TexCoord{};
	glm::vec3 Normal{};

	VertexFormat() {};
	VertexFormat(glm::vec3 _pos, glm::vec2 _texC, glm::vec3 _norm)
	{
		Position = _pos;
		TexCoord = _texC;
		Normal = _norm;
	}
};

class Model
{
public:
	Model(std::string _folderPath, std::string _fileName);
	~Model();
	void Render(GLFWwindow* window);

	// VAO
	void SetVAO_ID(GLuint _id) { VAO_ID = _id; };
	GLuint GetVAO_ID() { return VAO_ID; };
	void VAO_Generate();
	void VAO_Link();
	void VAO_Bind();
	void VAO_Unbind();
	void VAO_Delete();

	// VBO
	void VBO_Create();
	void VBO_Bind();
	void VBO_Unbind();
	void VBO_Delete();

private:

	GLuint VAO_ID{};
	GLuint VBO_ID{};
	std::vector<VertexFormat> Vertices{};
	std::vector<GLuint> Textures{};
	std::string FilePath{};

};

