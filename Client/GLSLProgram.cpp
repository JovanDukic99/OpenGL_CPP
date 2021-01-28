#include "GLSLProgram.h"
#include "SDLException.h"
#include <fstream>
#include <iostream>
#include <vector>

GLSLProgram::GLSLProgram() : numAttributes(0), programID(0), vertexShaderID(0), fragmenShaderID(0)
{

}

void GLSLProgram::createProgram() {
	// create program
	programID = glCreateProgram();
}

void GLSLProgram::createShaders() {
	// create vertex and fragment shader
	createShader(GL_VERTEX_SHADER);
	createShader(GL_FRAGMENT_SHADER);
}

void GLSLProgram::createShader(GLenum shaderType) {
	// glCreateShader will return 0 if error happened
	switch (shaderType) {
	case GL_VERTEX_SHADER: {
		// check for errors
		if ((vertexShaderID = glCreateShader(shaderType)) == 0) {
			throw SDLException(VERTEX_ERROR_1);
		}
	}
	case GL_FRAGMENT_SHADER: {
		// check for errors
		if ((fragmenShaderID = glCreateShader(shaderType)) == 0) {
			throw SDLException(FRAGMENT_ERROR_1);
		}
		break;
	}
	default:
		break;
	}
}

void GLSLProgram::compileShaders(const std::string& vertexShaderFile, const std::string& fragmentShaderFile) {
	// complie vertex and fragment shader
	compileShader(vertexShaderID, vertexShaderFile, GL_VERTEX_SHADER);
	compileShader(fragmenShaderID, fragmentShaderFile, GL_FRAGMENT_SHADER);
}

void GLSLProgram::compileShader(GLuint shaderID, const std::string& shaderFile, GLenum shaderType) {
	// load shader
	std::string vertexData = getFileData(shaderFile, shaderType);

	// create char array
	const char* dataArray = vertexData.c_str();

	// prepare for compilation
	glShaderSource(shaderID, 1, &dataArray, nullptr);

	// compile shader
	glCompileShader(shaderID);

	// check for compilation errors
	GLint status = 0;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE) {
		GLint infoLength = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLength);

		// get error log
		std::vector<GLchar> errorLog(infoLength);
		glGetShaderInfoLog(shaderID, infoLength, &infoLength, &errorLog[0]);

		// determine shader type
		std::string vertexType;

		switch (shaderType) {
		case GL_VERTEX_SHADER: {
			vertexType = "Vertex shader error: ";
			break;
		}case GL_FRAGMENT_SHADER: {
			vertexType = "Fragment shader error: ";
			break;
		}
		default:
			break;
		}

		// create error log
		std::string error(&errorLog[0]);

		// delete shader
		glDeleteShader(shaderID);

		throw SDLException(vertexType + error);
	}
}

std::string GLSLProgram::getFileData(const std::string& filePath, GLenum shaderType) {
	// open input stream
	std::ifstream inputStream(filePath);

	// check for errors
	if (inputStream.fail()) {
		throwFileError(shaderType);
	}

	std::string fileData;
	std::string line;

	// read data
	while (std::getline(inputStream, line)) {
		fileData = fileData + line + "\n";
	}

	// close stream
	inputStream.close();

	return fileData;
}

void GLSLProgram::throwFileError(GLenum shaderType) {
	switch (shaderType) {
	case GL_VERTEX_SHADER: {
		throw SDLException(VERTEX_ERROR_2);
		break;
	}
	case GL_FRAGMENT_SHADER: {
		throw SDLException(FRAGMENT_ERROR_2);
		break;
	}
	default:
		break;
	}
}

void GLSLProgram::linkShaders() {

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.

	// attach shaders to program
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmenShaderID);

	// link program
	glLinkProgram(programID);

	// check for erros
	GLint status = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, &status);

	if (status == GL_FALSE) {
		GLint infoLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLength);

		// get error log
		std::vector<GLchar> errorLog(infoLength);
		glGetShaderInfoLog(programID, infoLength, &infoLength, &errorLog[0]);

		// create error log
		std::string error(&errorLog[0]);


		throw SDLException(error);
	}

	// detach shaders from program
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmenShaderID);

	// delete shaders
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmenShaderID);
}

void GLSLProgram::addAttribute(const std::string& attributeName) {
	glBindAttribLocation(programID, numAttributes++, attributeName.c_str());
}

GLuint GLSLProgram::getUniformValueLocation(const std::string& uniformValueName) {
	GLuint location = glGetUniformLocation(programID, uniformValueName.c_str());
	// check for errors
	if (location == GL_INVALID_INDEX) {
		throw SDLException(UNIFORM_VALUE_ERRROR + uniformValueName + ".");
	}
	return location;
}

void GLSLProgram::use() {
	// use program
	glUseProgram(programID);

	// enable attributes
	for (int i = 0; i < numAttributes; i++) {
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::unuse() {
	// unuse program, 0 means no program
	glUseProgram(0);

	// disable attributes
	for (int i = 0; i < numAttributes; i++) {
		glDisableVertexAttribArray(i);
	}
}
