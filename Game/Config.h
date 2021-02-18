#include <string>

// screen config
static const std::string TITLE = "Game";
static const int SCREEN_WIDTH = 1080;
static const int SCREEN_HEIGHT = 720;
static const float HALF_WIDTH = SCREEN_WIDTH / 2.0f;
static const float HALF_HEIGHT = SCREEN_HEIGHT / 2.0f;

// world config
static const float UNIT_WIDTH = 60.0f;
static const float UNIT_HEIGHT = 60.0f;
static const int VERTICAL_UNITS = SCREEN_WIDTH / UNIT_WIDTH;
static const int HORIZONTAL_UNITS = SCREEN_HEIGHT / UNIT_HEIGHT;

// map config
static const float MAP_WIDTH = UNIT_WIDTH * 36.0f;
static const float MAP_HEIGHT = UNIT_HEIGHT * 24.0f;

// player config
static const float START_PLAYER_X = 60.0f;
static const float START_PLAYER_Y = 60.0f;
static const float PLAYER_WIDTH = 60.0f;
static const float PLAYER_HEIGHT = 60.0f;
static const float PLAYER_SPEED = 10.0f;

// clear color values
static const float CLEAR_R = 0.0f;
static const float CLEAR_G = 0.0f;
static const float CLEAR_B = 0.0f;
static const float CLEAR_A = 0.0f;

// camera config
static const float SCALE_FACTOR = 0.1f;

// shader info
static const std::string VERTEX_SHADER_PATH = "Shaders/baseShader.vert";
static const std::string FRAGMENT_SHADER_PATH = "Shaders/baseShader.frag";
static const std::string LIGHT_VERTEX_PATH = "Shaders/lightShader.vert";
static const std::string LIGHT_FRAGMENT_PATH = "Shaders/lightShader.frag";

// levels
static const std::string MAP_PATH = "Maps/Level1.png";