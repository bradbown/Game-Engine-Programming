#pragma once

#include "ref.h"
#include "glew.h"
#include <sstream>
#include <string>
#include <fstream>

namespace engine 
{

	class Shader 
	{
	public:
		Shader();
		~Shader();
		
		/// Loads shaders for the object into OpenGL
		void InitialiseShaders(GLuint* shader, GLint* _shaderModelMatLocation, GLint* _shaderViewMatLocation, GLint* _shaderProjMatLocation);
		void InitialiseLightShaders(GLuint* shader, GLint* _shaderModelMatLocation, GLint* _shaderViewMatLocation, GLint* _shaderProjMatLocation);
		void InitialiseNormalShaders(GLuint* shader, GLint* _shaderModelMatLocation, GLint* _shaderViewMatLocation, GLint* _shaderProjMatLocation);
		/// Shader program
		GLuint shader;
		/// Uniform locations
		GLint _shaderModelMatLocation, _shaderViewMatLocation, _shaderProjMatLocation;

	protected:



	private:

		std::string ReadFile(std::string fileName);
		void Awake();
	};

}
