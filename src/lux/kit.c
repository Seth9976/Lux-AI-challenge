#include "kit.h"
#include <stdlib.h>
#include <math.h>

GameState* game_state_create(void) {
    GameState* state = (GameState*)malloc(sizeof(GameState));
    if (!state) return NULL;
    
    state->step = 0;
    state->obs = NULL;
    state->env_cfg = NULL;
    
    return state;
}

void game_state_destroy(GameState* state) {
    if (!state) return;
    // obs 和 env_cfg 由外部管理，这里不需要释放
    free(state);
}

void game_state_update(GameState* state, struct json_object* obs) {
    if (!state || !obs) return;
    
    state->obs = obs;
    struct json_object* step_obj;
    if (json_object_object_get_ex(obs, "step", &step_obj)) {
        state->step = json_object_get_int(step_obj);
    }
}

Direction direction_to(int start_x, int start_y, int target_x, int target_y) {
    int dx = target_x - start_x;
    int dy = target_y - start_y;
    
    if (abs(dx) > abs(dy)) {
        if (dx > 0) return DIR_RIGHT;
        if (dx < 0) return DIR_LEFT;
    } else {
        if (dy > 0) return DIR_DOWN;
        if (dy < 0) return DIR_UP;
    }
    
    return DIR_CENTER;
}

int manhattan_distance(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}
