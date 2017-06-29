#pragma once

#include "ref.h"
#include "glm.hpp"

namespace engine
{
	struct Vertex {
		int Position;
		int TexCoord;
		int Normal;

		Vertex() {
			Position = 0;
			TexCoord = 0;
			Normal = 0;
		}
	};

	class ObjLoader
	{
	public:
		ObjLoader();
		~ObjLoader();

		void Load(std::string objFileName);

		std::vector<glm::vec3>& GetMeshVertices() { return meshVertices; }
		std::vector<glm::vec2>& GetMeshTexCoords() { return meshTexCoords; }
		std::vector<glm::vec3>& GetMeshNormals() { return meshNormals; }
		std::vector<glm::vec3>& GetMeshBiTangents() { return meshBiTangents; }
		std::vector<glm::vec3>& GetMeshTangents() { return meshTangents; }

	private:
		//store raw data read out of a file
		std::vector<glm::vec3> objFileVerts;
		std::vector<glm::vec3> objFileNormals;
		std::vector<glm::vec2> objFileTexCoords;
		std::vector<Vertex> vertices;

		//extracts bits of an obj file into the above std::vectors
		void ReadObjFileData(FILE* objFile);

		void BuildMeshDataVectors();
		void ComputeTangentBasis();

		std::vector<glm::vec3> meshVertices;
		std::vector<glm::vec2> meshTexCoords;
		std::vector<glm::vec3> meshNormals;
		std::vector<glm::vec3> meshBiTangents;
		std::vector<glm::vec3> meshTangents;

		//reads a string like "3//5" and returns a VNP with 3 & 5 in it
		Vertex ExtractFaceVertexData(std::string& s);
	};

}