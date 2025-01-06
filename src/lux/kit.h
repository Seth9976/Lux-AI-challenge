#ifndef KIT_H
#define KIT_H

#include <json-c/json.h>

// 游戏常量
#define MAP_SIZE 64
#define MAX_FACTORIES 5
#define MAX_UNITS_PER_TEAM 100

// 方向枚举
typedef enum {
    DIR_CENTER = 0,
    DIR_UP,
    DIR_RIGHT,
    DIR_DOWN,
    DIR_LEFT
} Direction;

// 游戏状态结构体
typedef struct {
    int step;
    struct json_object* obs;
    struct json_object* env_cfg;
} GameState;

// 核心函数声明
GameState* game_state_create(void);
void game_state_destroy(GameState* state);
void game_state_update(GameState* state, struct json_object* obs);

// 工具函数
Direction direction_to(int start_x, int start_y, int target_x, int target_y);
int manhattan_distance(int x1, int y1, int x2, int y2);

#endif
