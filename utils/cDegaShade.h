#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#define GLEW_STATIC
#include <GL/glew.h>
//#include <glad/glad.h>
#include <cGUIUtils.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

namespace degawong {

class cDegaShader {
public:
	// Constructor generates the shader on the fly
	cDegaShader(const GLchar* vertexPath, const GLchar* fragmentPath) {
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		} catch (std::ifstream::failure e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char * fShaderCode = fragmentCode.c_str();
		// 2. compile shaders
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];
		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");
		// shader Program
		ProgramHandle = glCreateProgram();
		glAttachShader(ProgramHandle, vertex);
		glAttachShader(ProgramHandle, fragment);
		glLinkProgram(ProgramHandle);
		checkCompileErrors(ProgramHandle, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	cDegaShader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath) {
		// 1. Retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		std::ifstream gShaderFile;
		// ensures ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			// Open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// Read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// Convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			// If geometry shader path is present, also load a geometry shader
			if (geometryPath != nullptr) {
				gShaderFile.open(geometryPath);
				std::stringstream gShaderStream;
				gShaderStream << gShaderFile.rdbuf();
				gShaderFile.close();
				geometryCode = gShaderStream.str();
			}
		} catch (std::ifstream::failure e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const GLchar* vShaderCode = vertexCode.c_str();
		const GLchar * fShaderCode = fragmentCode.c_str();
		// 2. Compile shaders
		GLuint vertex, fragment;
		GLint success;
		GLchar infoLog[512];
		// Vertex Shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		// Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");
		// If geometry shader is given, compile geometry shader
		GLuint geometry;
		if (geometryPath != nullptr) {
			const GLchar * gShaderCode = geometryCode.c_str();
			geometry = glCreateShader(GL_GEOMETRY_SHADER);
			glShaderSource(geometry, 1, &gShaderCode, NULL);
			glCompileShader(geometry);
			checkCompileErrors(geometry, "GEOMETRY");
		}
		// Shader Program
		this->ProgramHandle = glCreateProgram();
		glAttachShader(this->ProgramHandle, vertex);
		glAttachShader(this->ProgramHandle, fragment);
		if (geometryPath != nullptr) { glAttachShader(this->ProgramHandle, geometry); }
		glLinkProgram(this->ProgramHandle);
		checkCompileErrors(this->ProgramHandle, "PROGRAM");
		// Delete the shaders as they're linked into our program now and no longer necessery
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		if (geometryPath != nullptr)
			glDeleteShader(geometry);
	}
public:
	/* use current shader */
	void useProgram() { glUseProgram(this->ProgramHandle); }
public:
	void setBool(const std::string &name, bool value) const { glUniform1i(glGetUniformLocation(ProgramHandle, name.c_str()), (int)value); }
	void setInt(const std::string &name, int value) const { glUniform1i(glGetUniformLocation(ProgramHandle, name.c_str()), value); }
	void setFloat(const std::string &name, float value) const { glUniform1f(glGetUniformLocation(ProgramHandle, name.c_str()), value); }
	void setVec2(const std::string &name, const glm::vec2 &value) const { glUniform2fv(glGetUniformLocation(ProgramHandle, name.c_str()), 1, &value[0]); }
	void setVec2(const std::string &name, float x, float y) const { glUniform2f(glGetUniformLocation(ProgramHandle, name.c_str()), x, y); }
	void setVec3(const std::string &name, const glm::vec3 &value) const { glUniform3fv(glGetUniformLocation(ProgramHandle, name.c_str()), 1, &value[0]); }
	void setVec3(const std::string &name, float x, float y, float z) const { glUniform3f(glGetUniformLocation(ProgramHandle, name.c_str()), x, y, z); }
	void setVec4(const std::string &name, const glm::vec4 &value) const { glUniform4fv(glGetUniformLocation(ProgramHandle, name.c_str()), 1, &value[0]); }
	void setVec4(const std::string &name, float x, float y, float z, float w) const { glUniform4f(glGetUniformLocation(ProgramHandle, name.c_str()), x, y, z, w); }
	void setMat2(const std::string &name, const glm::mat2 &mat) const { glUniformMatrix2fv(glGetUniformLocation(ProgramHandle, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
	void setMat3(const std::string &name, const glm::mat3 &mat) const { glUniformMatrix3fv(glGetUniformLocation(ProgramHandle, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
	void setMat4(const std::string &name, const glm::mat4 &mat) const { glUniformMatrix4fv(glGetUniformLocation(ProgramHandle, name.c_str()), 1, GL_FALSE, &mat[0][0]); }
public:
	GLuint ProgramHandle;
private:
	void checkCompileErrors(GLuint shader, std::string type) {
		GLint success;
		GLchar infoLog[1024];
		if (type != "PROGRAM") {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success) {
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "| ERROR::::SHADER-COMPILATION-ERROR of type: " << type << "|\n" << infoLog << "\n| -- --------------------------------------------------- -- |" << std::endl;
			}
		}
		else {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success) {
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "| ERROR::::PROGRAM-LINKING-ERROR of type: " << type << "|\n" << infoLog << "\n| -- --------------------------------------------------- -- |" << std::endl;
			}
		}
	}
};

class cDegaTexture2D {
public:
	cDegaTexture2D(){ glGenTextures(1, &textureID); }
	cDegaTexture2D(std::string _path2Image) {
		imageInfo.loadImage(_path2Image);
		glGenTextures(1, &textureID);
		defaultOperation();
	}
	~cDegaTexture2D(){}
public:
	DEGA_FORCE_INLINE GLvoid loadImage(std::string _path2Image){ 
		imageInfo.loadImage(_path2Image); 
		defaultOperation();
	}
	DEGA_FORCE_INLINE GLvoid defaultOperation() {		
		bindTexture();
		defaultMode();
		textureImage();
		glGenerateMipmap(GL_TEXTURE_2D);
		unBindTexture();
	}
public:
	DEGA_FORCE_INLINE GLvoid setTexParameteri(GLenum _paraName, GLint _paraValue) { glTexParameteri(GL_TEXTURE_2D, _paraName, _paraValue); }
	DEGA_FORCE_INLINE GLvoid bindTexture() { glBindTexture(GL_TEXTURE_2D, textureID); }
	DEGA_FORCE_INLINE GLvoid unBindTexture() { glBindTexture(GL_TEXTURE_2D, 0); }
	DEGA_FORCE_INLINE GLvoid defaultMode() {
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	DEGA_FORCE_INLINE GLvoid textureImage(){ glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageInfo.width, imageInfo.height, 0, imageInfo.checkImageFormat(), GL_UNSIGNED_BYTE, imageInfo.data); }
public:
	GLuint textureID;
	cImageInfo imageInfo;
};

class cDegaABE {
public:
	cDegaABE() { genBuffers(); }
	cDegaABE(GLfloat *_vertices, GLuint *_indices, GLuint _verticNumber, GLuint _indiceNumber) : indices(_indices), vertices(_vertices), indiceNumber(_indiceNumber), verticNumber(_verticNumber) { genBuffers(); }
	~cDegaABE() { deleteABE(); }
public:
	DEGA_FORCE_INLINE GLvoid loadVerticIndices(GLfloat *_vertices, GLuint *_indices, GLuint _verticNumber, GLuint _indiceNumber) { 
		indices = _indices;
		vertices = _vertices;
		indiceNumber = _indiceNumber;
		verticNumber = _verticNumber;
	}
public:
	DEGA_FORCE_INLINE GLvoid bindVAO() { glBindVertexArray(VAO); }
	DEGA_FORCE_INLINE GLvoid bindVBO() { glBindBuffer(GL_ARRAY_BUFFER, VBO); }
	DEGA_FORCE_INLINE GLvoid bindEBO() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); }
	DEGA_FORCE_INLINE GLvoid unBindVAO() { glBindVertexArray(0); }
	DEGA_FORCE_INLINE GLvoid unBindVBO() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
	DEGA_FORCE_INLINE GLvoid unBindEBO() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }	
public:
	DEGA_FORCE_INLINE GLvoid genBuffers(){	
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);		
	}
	DEGA_FORCE_INLINE GLvoid bindBuffers() {
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, verticNumber * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceNumber * sizeof(GLfloat), indices, GL_STATIC_DRAW);
	}
	DEGA_FORCE_INLINE GLvoid unBindBuffers() {
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	DEGA_FORCE_INLINE GLvoid setVertexAttribute(GLuint _index, GLint _size, GLsizei _stride, const GLvoid *_pointer) {
		glVertexAttribPointer(_index, _size, GL_FLOAT, GL_FALSE, _stride * sizeof(GLfloat), (GLvoid*)(_pointer));
		glEnableVertexAttribArray(_index);
	}
public:
	DEGA_FORCE_INLINE GLvoid deleteABE() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}
public:
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;
public:
	GLuint * indices;
	GLfloat * vertices;
	GLuint indiceNumber;
	GLuint verticNumber;
};
}
