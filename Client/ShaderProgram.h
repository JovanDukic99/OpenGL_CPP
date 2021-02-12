#pragma once
#include <string>
#include <GL/glew.h>

class ShaderProgram
{
private:
	int numAttributes;
	GLuint programID;
	GLuint vertexShaderID;
	GLuint fragmenShaderID;

public:
	ShaderProgram();
	void createProgram();
	void createShaders();
	void use();
	void unuse();
	void compileShaders(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	void linkShaders();
	void addAttribute(const std::string& attributeName);
	GLint getUniformValueLocation(const std::string& uniformValueName);

private:
	void createShader(GLenum shaderType);
	void compileShader(GLuint shaderID, const std::string& shaderFile, GLenum shaderType);
	void throwFileError(GLenum shaderType);
	std::string getFileData(const std::string& filePath, GLenum shaderType);
};

