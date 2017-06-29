#include "Mesh.h"
#include "GameObject.h"
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

namespace engine
{

	Mesh::Mesh()
	{
		ObjLoader objLoader;
		_shader = new Shader();
		//_shader->InitialiseShaders();
		//_shader->InitialiseLightShaders();

		_VAO = 0;
		this->shader = _shader->shader;
		this->_shaderModelMatLocation = _shader->_shaderProjMatLocation;
		this->_shaderViewMatLocation = _shader->_shaderViewMatLocation;
		this->_shaderProjMatLocation = _shader->_shaderProjMatLocation;
		_numVertices = 0;
		objLoader.Load("sphere2.obj");

		this->vertices = objLoader.GetMeshVertices();
		this->normals = objLoader.GetMeshNormals();
		this->texcoords = objLoader.GetMeshTexCoords();
		this->meshTangets = objLoader.GetMeshTangents();
		this->meshBiTangents = objLoader.GetMeshBiTangents();

		/// Create the model
		InitialiseVAO();
	}

	Mesh::Mesh(std::string objFileName, std::string textureName, int shaderID)
	{
		ObjLoader objLoader;
		/// Initialise variables
		_VAO = 0;
		shader = 0;
		_shaderModelMatLocation = _shaderViewMatLocation = _shaderProjMatLocation = 0;

		_numVertices = 0;
		objLoader.Load(objFileName);

		this->vertices = objLoader.GetMeshVertices();
		this->normals = objLoader.GetMeshNormals();
		this->texcoords = objLoader.GetMeshTexCoords();
		this->meshTangets = objLoader.GetMeshTangents();
		this->meshBiTangents = objLoader.GetMeshBiTangents();

		/// Create the model
		InitialiseVAO();
		/// Create the shaders

		if (shaderID == 0)
		{
			_shader->InitialiseShaders(&shader, &_shaderModelMatLocation, &_shaderViewMatLocation, &_shaderProjMatLocation);
		}
		else if(shaderID == 1)
		{
			_shader->InitialiseLightShaders(&shader, &_shaderModelMatLocation, &_shaderViewMatLocation, &_shaderProjMatLocation);
		}
		else if(shaderID == 2)
		{
			_shader->InitialiseNormalShaders(&shader, &_shaderModelMatLocation, &_shaderViewMatLocation, &_shaderProjMatLocation);
		}
	}

	Mesh::Mesh(std::string objFileName, int light)
	{
		ObjLoader objLoader;
		/// Initialise variables
		_VAO = 0;
		shader = 0;
		_shaderModelMatLocation = _shaderViewMatLocation = _shaderProjMatLocation = 0;

		_numVertices = 0;
		objLoader.Load(objFileName);

		this->vertices = objLoader.GetMeshVertices();
		this->normals = objLoader.GetMeshNormals();
		this->texcoords = objLoader.GetMeshTexCoords();
		this->meshTangets = objLoader.GetMeshTangents();
		this->meshBiTangents = objLoader.GetMeshBiTangents();

		/// Create the model
		InitialiseVAO();
		/// Create the shaders

		if (light == 0)
		{
			_shader->InitialiseShaders(&shader, &_shaderModelMatLocation, &_shaderViewMatLocation, &_shaderProjMatLocation);
		}
		else
		{
			_shader->InitialiseLightShaders(&shader, &_shaderModelMatLocation, &_shaderViewMatLocation, &_shaderProjMatLocation);
		}
	}

	Mesh::~Mesh()
	{

	}

	void Mesh::InitialiseVAO()
	{
		/// Creates one VAO
		glGenVertexArrays(1, &_VAO);
		glBindVertexArray(_VAO);
		_numVertices = vertices.size();

		positionBuffer = 0;
		glGenBuffers(1, &positionBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numVertices * 3, &vertices[0], GL_STATIC_DRAW);

		normalBuffer = 0;
		glGenBuffers(1, &normalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numVertices * 3, &normals[0], GL_STATIC_DRAW);

		texCoordBuffer = 0;
		glGenBuffers(1, &texCoordBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numVertices * 2, &texcoords[0], GL_STATIC_DRAW);
		
		tangentBuffer = 0;
		glGenBuffers(1, &tangentBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, tangentBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numVertices * 3, &meshTangets[0], GL_STATIC_DRAW);

		bitangentBuffer = 0;
		glGenBuffers(1, &bitangentBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, bitangentBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numVertices * 3, &meshBiTangents[0], GL_STATIC_DRAW);

		/// Unbind for neatness, it just makes life easier
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		/// Technically we can do this, because the enabled / disabled state is stored in the VAO
		glDisableVertexAttribArray(0);
	}

	GLuint Mesh::InitialiseVAO(GLuint _VAO)
	{
		/// Creates one VAO
		glGenVertexArrays(1, &_VAO);
		glBindVertexArray(_VAO);
		_numVertices = vertices.size();

		positionBuffer = 0;
		glGenBuffers(1, &positionBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numVertices * 3, &vertices[0], GL_STATIC_DRAW);

		normalBuffer = 0;
		glGenBuffers(1, &normalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numVertices * 3, &normals[0], GL_STATIC_DRAW);

		texCoordBuffer = 0;
		glGenBuffers(1, &texCoordBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numVertices * 2, &texcoords[0], GL_STATIC_DRAW);

		/// Unbind for neatness, it just makes life easier
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		/// Technically we can do this, because the enabled / disabled state is stored in the VAO
		glDisableVertexAttribArray(0);

		return _VAO;
	}

	void Mesh::Render(glm::mat4& _modelMatrix, glm::mat4& viewMatrix, glm::mat4& projMatrix)
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);

		/// Activate the shader program
		glUseProgram(shader);

		/// Activate the VAO
		glBindVertexArray(_VAO);
		
		/// Send matrices to the shader as uniforms like this:
		glUniformMatrix4fv(_shaderModelMatLocation, 1, GL_FALSE, glm::value_ptr(_modelMatrix));
		glUniformMatrix4fv(_shaderViewMatLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(_shaderProjMatLocation, 1, GL_FALSE, glm::value_ptr(projMatrix));

		/// send the diffuse texture to the shader
		glm::mat4 MVP = projMatrix * viewMatrix * _modelMatrix;

		/// Send our transformation to the currently bound shader, 
		/// in the "MVP" uniform
		int MatrixID = glGetUniformLocation(shader, "MVP");
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		/// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTexID);
		/// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(MatrixID, 0);

		///vertex position data read in from obj file
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		///vertex normal data read in from obj file
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		///vertex texture coordinate data read in from obj file
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		/// Tell OpenGL to draw it
		/// Must specify the type of geometry to draw and the number of vertices
		glDrawArrays(GL_TRIANGLES, 0, _numVertices);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);

		/// Unbind VAO
		glBindVertexArray(0);

		/// Technically we can do this, but it makes no real sense because we must always have a valid shader program to draw geometry
		glUseProgram(0);
	}

	void Mesh::Render(glm::mat4& _modelMatrix, glm::mat4& viewMatrix, glm::mat4& projMatrix, glm::vec3 LightPos)
	{
		/*
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);

		/// Activate the shader program
		glUseProgram(shader);

		/// Activate the VAO
		glBindVertexArray(_VAO);

		glm::mat4 MVP = projMatrix * viewMatrix * _modelMatrix;
		glm::mat4 ModelViewMatrix = viewMatrix * _modelMatrix;
		glm::mat3 ModelView3x3Matrix = glm::mat3(ModelViewMatrix);

		/// Send our transformation to the currently bound shader, 
		/// in the "MVP" uniform
		GLuint modelView3x3MatrixID = glGetUniformLocation(shader, "MV3x3");
		int MatrixID = glGetUniformLocation(shader, "MVP");
		glUniformMatrix4fv(_shaderModelMatLocation, 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(_shaderProjMatLocation, 1, GL_FALSE, &_modelMatrix[0][0]);
		glUniformMatrix4fv(_shaderViewMatLocation, 1, GL_FALSE, &viewMatrix[0][0]);
		glUniformMatrix3fv(modelView3x3MatrixID, 1, GL_FALSE, &ModelView3x3Matrix[0][0]);
		/// Send matrices to the shader as uniforms like this:


		///send the diffuse texture to the shader
		GLuint lightID = glGetUniformLocation(shader, "LightPosition_worldspace");
		glUniform3f(lightID, LightPos.x, LightPos.y, LightPos.z);

		/// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTexID);
		/// Set our "myTextureSampler" sampler to user Texture Unit 0
		int diffuseSampler = glGetUniformLocation(shader, "texSampler");
		glUniform1i(diffuseSampler, 0);

		// Bind our normal texture in Texture Unit 1
		
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normalTexID);
		GLuint normalSampler = glGetUniformLocation(shader, "normalMap");
		// Set our "Normal    TextureSampler" sampler to user Texture Unit 0
		glUniform1i(normalSampler, 1);

		// Bind our normal texture in Texture Unit 2
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, specularTexID);
		GLuint specularSampler = glGetUniformLocation(shader, "specularMap");
		glUniform1i(specularSampler, 2);

		///vertex position data read in from obj file
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		///vertex texture coordinate data read in from obj file
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		///vertex normal data read in from obj file
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//tanget data read in from obj file
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, tangentBuffer);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//bi-tangent data read in from obj file
		glEnableVertexAttribArray(4);
		glBindBuffer(GL_ARRAY_BUFFER, bitangentBuffer);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		/// Tell OpenGL to draw it
		/// Must specify the type of geometry to draw and the number of vertices
		glDrawArrays(GL_TRIANGLES, 0, _numVertices);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);

		/// Unbind VAO
		glBindVertexArray(0);

		/// Technically we can do this, but it makes no real sense because we must always have a valid shader program to draw geometry
		glUseProgram(0);
		*/
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);

		/// Activate the shader program
		glUseProgram(shader);

		/// Activate the VAO
		glBindVertexArray(_VAO);

		glm::mat4 MVP = projMatrix * viewMatrix * _modelMatrix;
		glm::mat4 ModelViewMatrix = viewMatrix * _modelMatrix;
		glm::mat3 ModelView3x3Matrix = glm::mat3(ModelViewMatrix);

		/// Send our transformation to the currently bound shader, 
		/// in the "MVP" uniform
		GLuint modelView3x3MatrixID = glGetUniformLocation(shader, "MV3x3");
		glUniformMatrix4fv(glGetUniformLocation(shader, "MVP"), 1, GL_FALSE, &MVP[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shader, "M"), 1, GL_FALSE, &_modelMatrix[0][0]);
		glUniformMatrix4fv(glGetUniformLocation(shader, "V"), 1, GL_FALSE, &viewMatrix[0][0]);
		glUniformMatrix3fv(glGetUniformLocation(shader, "MV3x3"), 1, GL_FALSE, &ModelView3x3Matrix[0][0]);

		///send the diffuse texture to the shader
		GLuint lightID = glGetUniformLocation(shader, "LightPosition_worldspace");
		glUniform3f(lightID, LightPos.x, LightPos.y, LightPos.z);

		/// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTexID);
		glUniform1i(glGetUniformLocation(shader, "texSampler"), 0);

		// Bind our normal texture in Texture Unit 1
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normalTexID);
		glUniform1i(glGetUniformLocation(shader, "normalMap"), 1);


		// Bind our normal texture in Texture Unit 2
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, specularTexID);
		glUniform1i(glGetUniformLocation(shader, "specularMap"), 2);

		///vertex position data read in from obj file
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		///vertex texture coordinate data read in from obj file
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		///vertex normal data read in from obj file
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//tanget data read in from obj file
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, tangentBuffer);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		//bi-tangent data read in from obj file
		glEnableVertexAttribArray(4);
		glBindBuffer(GL_ARRAY_BUFFER, bitangentBuffer);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		/// Tell OpenGL to draw it
		/// Must specify the type of geometry to draw and the number of vertices
		glDrawArrays(GL_TRIANGLES, 0, _numVertices);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);

		/// Unbind VAO
		glBindVertexArray(0);

		/// Technically we can do this, but it makes no real sense because we must always have a valid shader program to draw geometry
		glUseProgram(0);
	}

	void Mesh::update(float dt)
	{

	}
}