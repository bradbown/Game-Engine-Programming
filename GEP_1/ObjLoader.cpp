#include "ObjLoader.h"
#include <sstream>

namespace engine
{

	ObjLoader::ObjLoader() {

	}

	ObjLoader::~ObjLoader() {

	}

	void ObjLoader::Load(std::string objFileName) {

		FILE * objFile;

		fopen_s(&objFile, objFileName.c_str(), "r");

		if (NULL == objFile)
			printf("Could not open obj file: %s\n", objFileName);

		//rips the raw data out of the obj file and stores it in various std::vectors
		ReadObjFileData(objFile);

		//builds vertex and normal std::vectors based on the above
		BuildMeshDataVectors();
		ComputeTangentBasis();

		fclose(objFile);
	}

	void ObjLoader::ReadObjFileData(FILE* objFile) {

		char buffer[256];

		while (true) {

			int read = fscanf_s(objFile, "%s", buffer, sizeof(buffer));
			if (read == EOF) break;

			//if first part of the line is "v"
			if (strcmp(buffer, "v") == 0) {
				//printf("Found a Vertex:\n");
				glm::vec3 vert;
				fscanf_s(objFile, "%f %f %f\n", &vert.x, &vert.y, &vert.z);
				objFileVerts.push_back(vert);
			}

			//if first part of the line is "vn"
			else if (strcmp(buffer, "vn") == 0) {
				//printf("Found a Vertex Normal:\n");
				glm::vec3 normal;
				fscanf_s(objFile, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				objFileNormals.push_back(normal);
			}

			//if first part of the line is "vt"
			else if (strcmp(buffer, "vt") == 0) {
				//printf("Found a Texture Coordinate:\n");
				glm::vec2 texCoord;
				fscanf_s(objFile, "%f %f\n", &texCoord.x, &texCoord.y);
				objFileTexCoords.push_back(texCoord);
			}

			//if first part of the line is "f"
			else if (strcmp(buffer, "f") == 0) {
				//printf("Found f:\n");

				/* we need to split the line following 'f' into individual bits
				* for processing i.e "1/2/3", "2/1/3", "3/3/3" etc
				*
				* NOTE - There's probably a more efficient way than this! */

				//read the line, turn it into a std::string and put that in a stringstream
				fscanf_s(objFile, "%256[^\n]", buffer, sizeof(buffer));
				std::string s(buffer);
				std::stringstream stream(s);

				/* find each "word" in the stringstream (i.e. something like "1/2/3"
				* and store it as 'split', also add each split to the 'splits' std::vec */
				std::string split;
				std::vector<std::string> splits;
				while (stream >> split)
					splits.push_back(split);

				/* now just send each split to the function which works out what they contain
				* and store what comes back in the faceVerts std::vector */
				for (int i = 0; i < splits.size(); i++)
					vertices.push_back(ExtractFaceVertexData(splits[i]));
			}
			else {
				printf("> Found unrecognised obj line: %s\n", buffer);
			}
		}
	}

	/* This function is called once we have extracted everything from the
	* obj file. It looks at all the 'face vertex' definitions (i.e "1/2/3")
	* and used them to build two std::vectors, one with all the right
	* vertex positions inside in the right order and another for the
	* normals. Tex-coord data is basically ignored.
	*
	* Two std::vectors can be used in a standard OpenGL glDrawArrays
	* procedure. This doesn't support anything clever like indexed
	* draws (look up "index buffer rendering OpenGL")but that wouldn't
	* be that hard to add on. */
	void ObjLoader::BuildMeshDataVectors() {

		for (int i = 0; i < vertices.size(); i++) {

			//the ith vertex in the std::vector
			Vertex* vnp = &vertices[i];

			//pack the vertex position data into the meshVertices list
			if (vnp->Position > 0) {
				meshVertices.push_back(objFileVerts[vnp->Position - 1]);

				/* if we added pos data we need to add tex coord and normal data */

				//pack vertex normal data into the meshNormals list
				if (vnp->Normal > 0)
					meshNormals.push_back(objFileNormals[vnp->Normal - 1]);
				else
					// dummy normal if there wasn't any for this vertex
					meshNormals.push_back(glm::vec3(1, 0, 0));

				//pack vertex texture coordinate data into the meshTexCoords list
				if (vnp->TexCoord > 0)
					meshTexCoords.push_back(objFileTexCoords[vnp->TexCoord - 1]);
				else
					// if there was no TC for this vertex, add dummy data
					meshTexCoords.push_back(glm::vec2(0, 0));
			}
		}
	}

	/*
	* This function receives a single portion of a 'f' line at a time
	*
	* Examples:
	*
	*    "123"   - Just a vertex id
	*    "1/2"   - Vertex and normal ids
	*    "1//2"  - Again, vertex and normal ids
	*    "1/2/3" - Vertex, texture-coordinate and normal ids
	*
	* The job of this function is to work out what information it has been
	* passed, store it in a FaceVertexData struct and then return that to
	* the caller.
	*/
	Vertex ObjLoader::ExtractFaceVertexData(std::string& s) {

		//we will see how many '/' the above string contains, and store their positions
		int slashPos[2];
		int slashCount = 0;

		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '/') {
				slashPos[slashCount] = i;
				slashCount++;
			}
		}

		/* this struct will hold whatever information we are
		* able to obtain about the face vertex. This will be
		* a combination of vertex, tex-coord and normal ids */
		Vertex result;

		if (slashCount == 0) {
			/* if we found no slashes then we probably have just a
			* vertex id so just convert to an int and store it */

			result.Position = std::stoi(s); //convert the whole of string s into an int
		}
		else if (slashCount == 1) {
			/* if we found one slash then we have just a vertex id
			* and normal id. Split the string into these two sub-
			* strings and convert them to ints. Store as necessary */

			result.Position = std::stoi(s.substr(0, slashPos[0]));	//convert up to the '/' into an int
			result.Normal = std::stoi(s.substr(slashPos[0] + 1));   //convert everything after the '/' to an int
		}
		else if (slashCount == 2) {
			/* if we have found two '/'s then it's slightly more
			* complicated as we could either have something like
			* "1/2/3" or "1//2". Extracting the vertex and normal
			* is the same in either case: */

			result.Position = std::stoi(s.substr(0, slashPos[0]));  //convert up to the first '/' into an int
			result.Normal = std::stoi(s.substr(slashPos[1] + 1)); //convert everything after the second '/' to an int

																  /* for the tex-coord, we will grab a sub-string of between
																  * the two '/'s, if that string is 0 length then we do not
																  * need to do anything, but if not then we need to turn
																  * whatever we have into an int, this is the tex-coord id */

			std::string texCoordString = s.substr(slashPos[0] + 1, (slashPos[1] - (slashPos[0])) - 1);
			if (texCoordString.size() > 0)
				result.TexCoord = std::stoi(texCoordString);

		}

		return result;
	}

	/*
	* Adapted from opengl-tutorial.com (tutorial #13)
	*
	* This works out the tangent and bi-tangent (sometimes called
	* bi-normal) vectors for each triangle. These are needed in
	* normal mapping.
	*/
	void ObjLoader::ComputeTangentBasis() {

		for (unsigned int i = 0; i < meshVertices.size(); i += 3) {

			/// Shortcuts for vertices
			glm::vec3& v0 = meshVertices[i + 0];
			glm::vec3& v1 = meshVertices[i + 1];
			glm::vec3& v2 = meshVertices[i + 2];

			/// Shortcuts for UVs
			glm::vec2& uv0 = meshTexCoords[i + 0];
			glm::vec2& uv1 = meshTexCoords[i + 1];
			glm::vec2& uv2 = meshTexCoords[i + 2];

			/// Edges of the triangle : position delta
			glm::vec3 deltaPos1 = v1 - v0;
			glm::vec3 deltaPos2 = v2 - v0;

			/// UV delta
			glm::vec2 deltaUV1 = uv1 - uv0;
			glm::vec2 deltaUV2 = uv2 - uv0;

			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
			glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
			glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

			/// Set the same tangent for all three vertices of the triangle.
			meshTangents.push_back(tangent);
			meshTangents.push_back(tangent);
			meshTangents.push_back(tangent);

			/// Same thing for binormals
			meshBiTangents.push_back(bitangent);
			meshBiTangents.push_back(bitangent);
			meshBiTangents.push_back(bitangent);
		}
	}

}