#pragma once
#include <string>

// window config
static const std::string TITLE = "Game engine";

static const int SCREEN_WIDTH = 1080;
static const int SCREEN_HEIGHT = 720;

static const int HALF_WIDTH = SCREEN_WIDTH / 2.0f;
static const int HALF_HEIGHT = SCREEN_HEIGHT / 2.0f;

static const int MAP_WIDHT = 36;
static const int MAP_HEIGHT = 24;

static const float UNIT_WIDTH = 60.0f;
static const float UNIT_HEIGHT = 60.0f;

// rgba clear values
static const float R_CLEAR = 0.0f;
static const float G_CLEAR = 0.0f;
static const float B_CLEAR = 0.0f;
static const float A_CLEAR = 1.0f;

// shader file paths
static const std::string VERTEX_SHADER_PATH = "Shaders/colorShading.vert";
static const std::string FRAGMENT_SHADER_PATH = "Shaders/colorShading.frag";

static const std::string OBJECT_VERTEX_PATH = "Shaders/baseShader.vert";
static const std::string OBJECT_FRAGMENT_PATH = "Shaders/baseShader.frag";

static const std::string LIGHT_VERTEX_PATH = "Shaders/lightShader.vert";
static const std::string LIGHT_FRAGMENT_PATH = "Shaders/lightShader.frag";

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

