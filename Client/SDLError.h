#pragma once
#include <string>

// glew errors
static const std::string WINDOW_ERROR = "Failed to create window.";
static const std::string CONTEXT_ERROR = "Failed to initialize context.";
static const std::string GLEW_ERROR = "Failed to initialize glew.";

// vertex errors
static const std::string VERTEX_ERROR_1 = "Failed to create vertex shader.";
static const std::string VERTEX_ERROR_2 = "Failed to open vertex shader file.";
static const std::string VERTEX_ERROR_3 = "Failed to compile vertex shader.";

// fragment errors
static const std::string FRAGMENT_ERROR_1 = "Failed to create fragment shader.";
static const std::string FRAGMENT_ERROR_2 = "Failed to open fragment shader file.";
static const std::string FRAGMENT_ERROR_3 = "Failed to compile vertex shader.";

static const std::string UNIFORM_VALUE_ERRROR = "Uniform value with given name not found: ";