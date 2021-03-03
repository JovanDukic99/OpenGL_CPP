#pragma once
#include <string>

// shader file paths
// non shadow shaders
static const std::string GEOMETRY_VERTEX_PATH = "Shaders/geometryShader.vert";
static const std::string GEOMETRY_FRAGMENT_PATH = "Shaders/geometryShader.frag";

static const std::string TEXTURE_VERTEX_PATH = "Shaders/textureShader.vert";
static const std::string TEXTURE_FRAGMENT_PATH = "Shaders/textureShader.frag";

// shadow shaders
static const std::string VISION_GEOMETRY_VERTEX_PATH = "Shaders/visionGeometryShader.vert";
static const std::string VISION_GEOMETRY_FRAGMENT_PATH = "Shaders/visionGeometryShader.frag";

static const std::string VISION_TEXTURE_VERTEX_PATH = "Shaders/visionTextureShader.vert";
static const std::string VISION_TEXTURE_FRAGMENT_PATH = "Shaders/visionTextureShader.frag";

// multi shadow shaders
static const std::string MULTI_VISION_GEOMETRY_VERTEX_PATH = "Shaders/multiVisionGeometryShader.vert";
static const std::string MULTI_VISION_GEOMETRY_FRAGMENT_PATH = "Shaders/multiVisionGeometryShader.frag";

static const std::string MULTI_VISION_TEXTURE_VERTEX_PATH = "Shaders/multiVisionTextureShader.vert";
static const std::string MULTI_VISION_TEXTURE_FRAGMENT_PATH = "Shaders/multiVisionTextureShader.frag";

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

// A* algorithm
static const int HORIZONTAL_VERTICAL_COST = 10;
static const int DIAGONAL_COST = 14;

// assets paths
static const std::string PLAYER_TEXTURE = "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png";
static const std::string LEVEL_PATH = "Textures/jimmyJump_pack/PNG/LevelMap.png";

