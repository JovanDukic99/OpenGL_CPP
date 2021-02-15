#pragma once
#include "Camera2D.h"
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
class ShaderProgram
{
private:
	int numAttributes;
	GLuint programID;
	GLuint vertexShaderID;
	GLuint fragmenShaderID;
	glm::mat4* cameraMatrix;
public:
	ShaderProgram();
	ShaderProgram(Camera2D& camera, std::string vertexPath, std::string fragmenPath);
	void init(std::string vertexPath, std::string fragmenPath);
	void init(Camera2D& camera, std::string vertexPath, std::string fragmenPath);
	void use();
	void unuse();
private:
	void createProgram();
	void createShaders();
	void createShader(GLenum shaderType);
	void compileShaders(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	void compileShader(GLuint shaderID, const std::string& shaderFile, GLenum shaderType);
	void addAttribute(const std::string& attributeName);
	void linkShaders();
	void uploadCameraMatrix();
	void throwFileError(GLenum shaderType);
	void setCamera(Camera2D& camera);
	bool check();
	std::string getFileData(const std::string& filePath, GLenum shaderType);
	GLint getUniformValueLocation(const std::string& uniformValueName);
};

