#pragma once
#include <string>

// shader file paths
static const std::string VERTEX_SHADER_PATH = "Shaders/baseShader.vert";
static const std::string FRAGMENT_SHADER_PATH = "Shaders/baseShader.frag";
static const std::string LIGHT_VERTEX_PATH = "Shaders/lightShader.vert";
static const std::string LIGHT_FRAGMENT_PATH = "Shaders/lightShader.frag";

// shader attributes
static const std::string VERTEX_POSITION = "vertexPosition";
static const std::string VERTEX_COLOR = "vertexColor";

// player config
static const float PLAYER_X = 0.0f;
static const float PLAYER_Y = 0.0f;
static const float PLAYER_WIDTH = 1.0f;
static const float PLAYER_HEIGHT = 1.0f;
static const float PLAYER_SPEED = 10.0f;

// block config
static const float BLOCK_WIDTH = 60.0f;
static const float BLOCK_HEIGHT = 60.0f;

// camera config
static const float CAMERA_SPEED = 10.0f;
static const float CAMERA_SCALE = 0.05f;

// assets paths
static const std::string PLAYER_TEXTURE = "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png";
static const std::string LEVEL_PATH = "Textures/jimmyJump_pack/PNG/LevelMap.png";

