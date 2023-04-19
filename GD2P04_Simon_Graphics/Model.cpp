#include "Model.h"
#include <iostream>

Model::Model(std::string _folderPath, std::string _fileName)
{
	FilePath = _folderPath + _fileName;

	tinyobj::ObjReaderConfig ReaderConfig;
	ReaderConfig.mtl_search_path = "";		// Path to material files

	tinyobj::ObjReader Reader;

	if (!Reader.ParseFromFile(FilePath, ReaderConfig))
	{
		if (!Reader.Error().empty()) { std::cerr << "TinyObjReader: " << Reader.Error(); 
		}
		exit(1);
	}

	if (!Reader.Warning().empty()) {
		std::cout << "TinyObjReader: " << Reader.Warning();
	}

	auto& Attrib = Reader.GetAttrib();
	auto& Shapes = Reader.GetShapes();
	auto& Materials = Reader.GetMaterials();

	for (size_t ShapeIndex = 0; ShapeIndex < Shapes.size(); ShapeIndex++)
	{
		size_t IndexOffset = 0;

		for (size_t FaceIndex = 0; FaceIndex < Shapes[ShapeIndex].mesh.num_face_vertices.size(); FaceIndex++)
		{
			size_t FaceVertexCount = size_t(Shapes[ShapeIndex].mesh.num_face_vertices[FaceIndex]);

			for (size_t VertexIndex = 0; VertexIndex < FaceVertexCount; VertexIndex++)
			{
				VertexFormat Vertex{};
				tinyobj::index_t TinyObjVertex = Shapes[ShapeIndex].mesh.indices[IndexOffset + VertexIndex];
				Vertex.Position = {
					Attrib.vertices[3 * size_t(TinyObjVertex.vertex_index) + 0],
					Attrib.vertices[3 * size_t(TinyObjVertex.vertex_index) + 1],
					Attrib.vertices[3 * size_t(TinyObjVertex.vertex_index) + 2],
				};
				if (TinyObjVertex.normal_index >= 0)
				{
					Vertex.Normal = {
						Attrib.normals[3 * size_t(TinyObjVertex.normal_index) + 0],
						Attrib.normals[3 * size_t(TinyObjVertex.normal_index) + 1],
						Attrib.normals[3 * size_t(TinyObjVertex.normal_index) + 2],
					};
				}
				if (TinyObjVertex.texcoord_index >= 0)
				{
					Vertex.TexCoord = {
						Attrib.texcoords[2 * size_t(TinyObjVertex.texcoord_index) + 0],
						Attrib.texcoords[2 * size_t(TinyObjVertex.texcoord_index) + 1],
					};
				}
				Vertices.push_back(Vertex);
			}
			IndexOffset += FaceVertexCount;

			GLuint tex = Shapes[ShapeIndex].mesh.material_ids[FaceIndex];
		}
	}

	std::string TextureFilePath = _folderPath + Materials[0].diffuse_texname;


}

Model::~Model()
{
}

void Model::Render(GLFWwindow* window)
{
	glDrawArrays(GL_TRIANGLES, 0, sizeof(VertexFormat));
}

void Model::VAO_Generate()
{
	glGenVertexArrays(1, &VAO_ID);
}

void Model::VAO_Link()
{
	glVertexAttribPointer(
		2,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(VertexFormat),
		(void*)(offsetof(VertexFormat, VertexFormat::Normal)));
	glEnableVertexAttribArray(2);

}

void Model::VAO_Bind()
{
	glBindVertexArray(VAO_ID);
}

void Model::VAO_Unbind()
{
	glBindVertexArray(0);
}

void Model::VAO_Delete()
{
	glDeleteVertexArrays(1, &VAO_ID);
}

void Model::VBO_Create()
{
	glGenBuffers(1, &VBO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
	glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(VertexFormat), &Vertices[0], GL_STATIC_DRAW);
}

void Model::VBO_Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
}

void Model::VBO_Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::VBO_Delete()
{
	glDeleteBuffers(1, &VBO_ID);
}
