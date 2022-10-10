//
// Created by Andres on 27/06/22.
//

#include "Model.h"

#include <iostream>

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tiny_gltf.h"
#include "Components/renderer.h"
#include <glad/glad.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

std::pair<GLuint, std::map<int, GLuint>> bindModel(tinygltf::Model& model);
bool loadModel(tinygltf::Model& model, std::string& path);
void bindModelNodes(std::map<int, GLuint>& vbos, tinygltf::Model& model, tinygltf::Node& node);
void bindMesh(std::map<int, GLuint>& vbos, tinygltf::Model& model, tinygltf::Mesh& mesh);

void unwindMesh(std::vector<meshComponent>& meshes, std::pair<GLuint, std::map<int, GLuint>>& vaos, tinygltf::Model& model, tinygltf::Mesh& mesh)
{
	for (size_t i = 0; i < mesh.primitives.size(); i++)
	{
		tinygltf::Primitive primitive = mesh.primitives[i];
		tinygltf::Accessor indexAccessor = model.accessors[primitive.indices];

		for (auto& attrib : primitive.attributes) {
			tinygltf::Accessor accessor = model.accessors[attrib.second];

			int vaa = -1;
			if (attrib.first.compare("POSITION") == 0) vaa = 0;
			if (attrib.first.compare("NORMAL") == 0) vaa = 1;
			if (attrib.first.compare("TEXCOORD_0") == 0) vaa = 2;


			int vbo = vaos.second.at(accessor.bufferView);
			int ebo = vaos.second.at(indexAccessor.bufferView);
			meshComponent mc = {
					vaos.first,
					vbo,
					ebo,
					vaa,
					primitive.mode,
					indexAccessor.count,
					indexAccessor.componentType,
					indexAccessor.byteOffset
			};

			meshes.push_back(mc);

		}

		
	}
}

void unwindModelNodes(std::vector<meshComponent>& meshes, std::pair<GLuint, std::map<int, GLuint>>& vaos, tinygltf::Model& model, tinygltf::Node& node)
{
	if ((node.mesh >= 0) && (node.mesh < model.meshes.size())) {
		unwindMesh(meshes, vaos, model, model.meshes[node.mesh]);
	}

	for (size_t i = 0; i < node.children.size(); i++)
	{
		unwindModelNodes(meshes, vaos, model, model.nodes[node.children[i]]);
	}
}

void unwind(std::vector<meshComponent>& meshes, std::pair<GLuint, std::map<int, GLuint>>& vaos, tinygltf::Model& model)
{
	tinygltf::Scene& scene = model.scenes[model.defaultScene];
	for (size_t i = 0; i < scene.nodes.size(); i++)
	{
		unwindModelNodes(meshes, vaos, model, model.nodes[scene.nodes[i]]);
	}
}

ModelSystem::ModelSystem() {
	std::string path = "./models/astronautA.glb";
	tinygltf::Model m;
	if (!loadModel(m, path)) {
		// what to do when can't load model?
	}
	std::pair<GLuint, std::map<int,GLuint>> vaos = bindModel(m);

	unwind(this->meshes, vaos, m);

	return;
}

bool loadModel(tinygltf::Model& model, std::string& path) {
	tinygltf::TinyGLTF loader;
	std::string err;
	std::string warn;

	bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, path);

	if (!warn.empty()) {
		printf("Warn: %s\n", warn.c_str());
	}

	if (!err.empty()) {
		printf("Err: %s\n", err.c_str());
	}

	if (!ret) {
		printf("Failed to parse glTF\n");
	}

	return true;
}

std::pair<GLuint, std::map<int, GLuint>> bindModel(tinygltf::Model& model) {
	std::map<int, GLuint> vbos;
	GLuint vao; // 

	glGenVertexArrays(1, &vao);//
	glBindVertexArray(vao);

	const tinygltf::Scene& scene = model.scenes[model.defaultScene];
	for (size_t i = 0; i < scene.nodes.size(); ++i) {
		assert((scene.nodes[i] >= 0) && (scene.nodes[i] < model.nodes.size()));
		bindModelNodes(vbos, model, model.nodes[scene.nodes[i]]);
	}

	return { vao , vbos};
}

void bindModelNodes(std::map<int, GLuint>& vbos, tinygltf::Model& model, tinygltf::Node& node) {
	if ((node.mesh >= 0) && (node.mesh < model.meshes.size())) {
		bindMesh(vbos, model, model.meshes[node.mesh]);
	}

	for (size_t i = 0;i<node.children.size();++i)
	{
		assert((node.children[i] >= 0) && (node.children[i] < model.nodes.size()));
		bindModelNodes(vbos, model, model.nodes[node.children[i]]);
	}
}

void bindMesh(std::map<int, GLuint>& vbos, tinygltf::Model& model, tinygltf::Mesh& mesh) 
{
	for (size_t i = 0; i < model.bufferViews.size();++i)
	{
		const tinygltf::BufferView & bufferView = model.bufferViews[i];
		if (bufferView.target == 0) {
			continue;
		}

		const tinygltf::Buffer& buffer = model.buffers[bufferView.buffer];
		std::cout << "bufferview.target " << bufferView.target << std::endl;

		GLuint vbo;
		glGenBuffers(1, &vbo);
		vbos[i] = vbo;
		glBindBuffer(bufferView.target, vbo);

		std::cout << "buffer.data.size = " << buffer.data.size()
			<< ", bufferview.byteOffset = " << bufferView.byteOffset
			<< std::endl;

		glBufferData(bufferView.target, bufferView.byteLength, &buffer.data.at(0) + bufferView.byteOffset, GL_STATIC_DRAW);
	}

	for (size_t i = 0; i < mesh.primitives.size(); ++i)
	{
		tinygltf::Primitive primitive = mesh.primitives[i];
		tinygltf::Accessor indexAccessor = model.accessors[primitive.indices];

		for (auto& attrib : primitive.attributes)
		{
			tinygltf::Accessor accessor = model.accessors[attrib.second];
			int byteStride = accessor.ByteStride(model.bufferViews[accessor.bufferView]);
			glBindBuffer(GL_ARRAY_BUFFER, vbos[accessor.bufferView]);

			int size = 1;
			if (accessor.type != TINYGLTF_TYPE_SCALAR) {
				size = accessor.type;
			}

			int vaa = -1;
			if (attrib.first.compare("POSITION") == 0) vaa = 0;
			if (attrib.first.compare("NORMAL") == 0) vaa = 1;
			if (attrib.first.compare("TEXCOORD_0") == 0) vaa = 2;
			if (vaa > -1) {
				glEnableVertexAttribArray(vaa);
				glVertexAttribPointer(vaa, size, accessor.componentType,
					accessor.normalized ? GL_TRUE : GL_FALSE,
					byteStride, BUFFER_OFFSET(accessor.byteOffset));
			}
			else
			{
				std::cout << "vaa missing: " << attrib.first << std::endl;
			}
		}

		if (model.textures.size() > 0)
		{
			// throw exception handle images later?
			tinygltf::Texture& tex = model.textures[0];
		}
	}
}

ModelSystem::~ModelSystem() {

}

void ModelSystem::Initialize(entt::registry& registry)
{
	for (meshComponent mc : meshes)
	{
		auto entity = registry.create();
		auto& entt = registry.emplace<rendererComponent>(entity);
		entt.VAO = mc.vao;
		entt.VBO = mc.vbo;
		entt.EBO = mc.ebo;
		entt.VAA = mc.vaa;
		entt.mode = mc.mode;
		entt.triangleCount = mc.count;
		entt.type = mc.type;
		entt.offset = mc.offset;
	}
	
}
