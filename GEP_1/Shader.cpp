#include "Shader.h"

namespace engine
{

	bool CheckShaderCompiled(GLint shader)
	{
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			GLsizei len;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetShaderInfoLog(shader, len, &len, log);
			std::cerr << "ERROR: Shader compilation failed: " << log << std::endl;
			delete[] log;

			return false;
		}
		return true;
	}

	Shader::Shader()
	{
		shader = 0;
	}


	Shader::~Shader()
	{

	}

	std::string Shader::ReadFile(std::string fileName)
	{

		std::string result;

		std::ifstream stream(fileName, std::ios::in);
		if (stream.is_open()) {
			std::string Line = "";
			while (getline(stream, Line))
				result += "\n" + Line;
			stream.close();
		}

		return result;
	}

	void Shader::InitialiseShaders(GLuint* shader, GLint* _shaderModelMatLocation, GLint* _shaderViewMatLocation, GLint* _shaderProjMatLocation)
	{

		/// This is the vertex shader being loaded from file
		std::string VertexShaderCode = ReadFile("texturing.vertexshader");

		/// This is the fragment shader
		std::string FragShaderCode = ReadFile("texturing.fragmentshader");

		/// The 'program' stores the shaders
		*shader = glCreateProgram();

		/// Create the vertex shader
		GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
		/// Give GL the source for it
		char const* VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(vShader, 1, &VertexSourcePointer, NULL);
		/// Compile the shader
		glCompileShader(vShader);
		/// Check it compiled and give useful output if it didn't work!
		if (!CheckShaderCompiled(vShader))
		{
			return;
		}
		/// This links the shader to the program
		glAttachShader(*shader, vShader);

		/// Same for the fragment shader
		GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
		char const* FragSourcePointer = FragShaderCode.c_str();
		glShaderSource(fShader, 1, &FragSourcePointer, NULL);
		glCompileShader(fShader);
		if (!CheckShaderCompiled(fShader))
		{
			return;
		}
		glAttachShader(*shader, fShader);

		/// This makes sure the vertex and fragment shaders connect together
		glLinkProgram(*shader);
		/// Check this worked
		GLint linked;
		glGetProgramiv(*shader, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			GLsizei len;
			glGetProgramiv(*shader, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetProgramInfoLog(*shader, len, &len, log);
			std::cerr << "ERROR: Shader linking failed: " << log << std::endl;
			delete[] log;

			return;
		}

		/// We need to get the location of the uniforms in the shaders
		/// This is so that we can send the values to them from the application
		/// We do this in the following way: 
		*_shaderModelMatLocation = glGetUniformLocation(*shader, "modelMat");
		*_shaderViewMatLocation = glGetUniformLocation(*shader, "viewMat");
		*_shaderProjMatLocation = glGetUniformLocation(*shader, "projMat");
	}

	void Shader::InitialiseLightShaders(GLuint* shader, GLint* _shaderModelMatLocation, GLint* _shaderViewMatLocation, GLint* _shaderProjMatLocation)
	{

		/// This is the vertex shader being loaded from file
		std::string VertexShaderCode = ReadFile("light.vertexshader");

		/// This is the fragment shader
		std::string FragShaderCode = ReadFile("light.fragmentshader");

		/// The 'program' stores the shaders
		*shader = glCreateProgram();

		/// Create the vertex shader
		GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
		/// Give GL the source for it
		char const* VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(vShader, 1, &VertexSourcePointer, NULL);
		/// Compile the shader
		glCompileShader(vShader);
		/// Check it compiled and give useful output if it didn't work!
		if (!CheckShaderCompiled(vShader))
		{
			return;
		}
		/// This links the shader to the program
		glAttachShader(*shader, vShader);

		/// Same for the fragment shader
		GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
		char const* FragSourcePointer = FragShaderCode.c_str();
		glShaderSource(fShader, 1, &FragSourcePointer, NULL);
		glCompileShader(fShader);
		if (!CheckShaderCompiled(fShader))
		{
			return;
		}
		glAttachShader(*shader, fShader);

		/// This makes sure the vertex and fragment shaders connect together
		glLinkProgram(*shader);
		/// Check this worked
		GLint linked;
		glGetProgramiv(*shader, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			GLsizei len;
			glGetProgramiv(*shader, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetProgramInfoLog(*shader, len, &len, log);
			std::cerr << "ERROR: Shader linking failed: " << log << std::endl;
			delete[] log;

			return;
		}

		/// We need to get the location of the uniforms in the shaders
		/// This is so that we can send the values to them from the application
		/// We do this in the following way: 
		*_shaderModelMatLocation = glGetUniformLocation(*shader, "MVP");
		*_shaderViewMatLocation = glGetUniformLocation(*shader, "V");
		*_shaderProjMatLocation = glGetUniformLocation(*shader, "M");
	}

	void Shader::InitialiseNormalShaders(GLuint* shader, GLint* _shaderModelMatLocation, GLint* _shaderViewMatLocation, GLint* _shaderProjMatLocation)
	{
		/*
		/// This is the vertex shader being loaded from file
		std::string VertexShaderCode = ReadFile("normal.vertexshader");

		/// This is the fragment shader
		std::string FragShaderCode = ReadFile("normal.fragmentshader");

		/// The 'program' stores the shaders
		*shader = glCreateProgram();

		/// Create the vertex shader
		GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
		/// Give GL the source for it
		char const* VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(vShader, 1, &VertexSourcePointer, NULL);
		/// Compile the shader
		glCompileShader(vShader);
		/// Check it compiled and give useful output if it didn't work!
		if (!CheckShaderCompiled(vShader))
		{
			return;
		}
		/// This links the shader to the program
		glAttachShader(*shader, vShader);

		/// Same for the fragment shader
		GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
		char const* FragSourcePointer = FragShaderCode.c_str();
		glShaderSource(fShader, 1, &FragSourcePointer, NULL);
		glCompileShader(fShader);
		if (!CheckShaderCompiled(fShader))
		{
			return;
		}
		glAttachShader(*shader, fShader);

		/// This makes sure the vertex and fragment shaders connect together
		glLinkProgram(*shader);
		/// Check this worked
		GLint linked;
		glGetProgramiv(*shader, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			GLsizei len;
			glGetProgramiv(*shader, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetProgramInfoLog(*shader, len, &len, log);
			std::cerr << "ERROR: Shader linking failed: " << log << std::endl;
			delete[] log;

			return;
		}

		/// We need to get the location of the uniforms in the shaders
		/// This is so that we can send the values to them from the application
		/// We do this in the following way: 
		*_shaderModelMatLocation = glGetUniformLocation(*shader, "MVP");
		*_shaderViewMatLocation = glGetUniformLocation(*shader, "V");
		*_shaderProjMatLocation = glGetUniformLocation(*shader, "M");
		*/

		/// This is the vertex shader being loaded from file
		std::string VertexShaderCode = ReadFile("normal.vertexshader");

		/// This is the fragment shader
		std::string FragShaderCode = ReadFile("normal.fragmentshader");

		// The 'program' stores the shaders
		*shader = glCreateProgram();

		// Create the vertex shader
		GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
		// Give GL the source for it
		char const* VertexSourcePointer = VertexShaderCode.c_str();
		glShaderSource(vShader, 1, &VertexSourcePointer, NULL);
		// Compile the shader
		glCompileShader(vShader);
		// Check it compiled and give useful output if it didn't work!
		if (!CheckShaderCompiled(vShader))
		{
			return;
		}
		// This links the shader to the program
		glAttachShader(*shader, vShader);

		// Same for the fragment shader
		GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
		char const* FragSourcePointer = FragShaderCode.c_str();
		glShaderSource(fShader, 1, &FragSourcePointer, NULL);
		glCompileShader(fShader);
		if (!CheckShaderCompiled(fShader))
		{
			return;
		}
		glAttachShader(*shader, fShader);

		// This makes sure the vertex and fragment shaders connect together
		glLinkProgram(*shader);
		// Check this worked
		GLint linked;
		glGetProgramiv(*shader, GL_LINK_STATUS, &linked);
		if (!linked)
		{
			GLsizei len;
			glGetProgramiv(*shader, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetProgramInfoLog(*shader, len, &len, log);
			std::cerr << "ERROR: Shader linking failed: " << log << std::endl;
			delete[] log;

			return;
		}
	}

	void Shader::Awake()
	{

	}
}