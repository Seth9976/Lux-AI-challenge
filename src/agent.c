#include "agent.h"
#include "lux/kit.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_UNITS 100
#define MAX_RELIC_NODES 1000

Agent* agent_create(const char* player, struct json_object* env_cfg) {
    Agent* agent = (Agent*)malloc(sizeof(Agent));
    if (!agent) {
        fprintf(stderr, "Failed to allocate agent\n");
        return NULL;
    }

    agent->player = strdup(player);
    agent->team_id = strcmp(player, "player_0") == 0 ? 0 : 1;
    agent->opp_team_id = 1 - agent->team_id;
    agent->env_cfg = env_cfg;
    
    // 初始化资源数组
    agent->relic_node_positions = (int*)malloc(MAX_RELIC_NODES * 2 * sizeof(int));
    agent->discovered_relic_nodes_ids = (int*)malloc(MAX_RELIC_NODES * sizeof(int));
    agent->relic_nodes_count = 0;
    agent->discovered_nodes_count = 0;

    // 初始化单位探索位置
    agent->unit_explore_locations = (int**)malloc(MAX_UNITS * sizeof(int*));
    for (int i = 0; i < MAX_UNITS; i++) {
        agent->unit_explore_locations[i] = (int*)malloc(2 * sizeof(int));
    }
    agent->units_count = 0;

    return agent;
}

void agent_destroy(Agent* agent) {
    if (!agent) return;

    free(agent->player);
    
    free(agent->relic_node_positions);
    free(agent->discovered_relic_nodes_ids);
    
    for (int i = 0; i < MAX_UNITS; i++) {
        free(agent->unit_explore_locations[i]);
    }
    free(agent->unit_explore_locations);
    
    // 注意: env_cfg 由外部管理，这里不需要释放
    free(agent);
}

struct json_object* agent_act(Agent* agent, int step, struct json_object* obs, int remaining_overage_time) {
    struct json_object* actions = json_object_new_object();
    
    // 获取单位信息
    struct json_object* units;
    json_object_object_get_ex(obs, "units", &units);
    
    struct json_object* player_units;
    char player_key[10];
    snprintf(player_key, sizeof(player_key), "%d", agent->team_id);
    json_object_object_get_ex(units, player_key, &player_units);

    // 处理每个单位的行动
    int units_len = json_object_array_length(player_units);
    for (int i = 0; i < units_len; i++) {
        struct json_object* unit = json_object_array_get_idx(player_units, i);
        
        // 获取单位ID
        struct json_object* unit_id_obj;
        json_object_object_get_ex(unit, "unit_id", &unit_id_obj);
        const char* unit_id = json_object_get_string(unit_id_obj);
        
        // 这里添加单位行动逻辑
        struct json_object* unit_action = create_move_action(agent, unit);
        if (unit_action) {
            json_object_object_add(actions, unit_id, unit_action);
        }
    }

    return actions;
}

// 辅助函数：创建移动动作
static struct json_object* create_move_action(Agent* agent, struct json_object* unit) {
    // 简单的移动逻辑示例
    struct json_object* action = json_object_new_array();
    json_object_array_add(action, json_object_new_string("MOVE"));
    
    // 随机选择一个方向 (这里需要改进为更智能的移动策略)
    const char* directions[] = {"UP", "RIGHT", "DOWN", "LEFT"};
    int dir_idx = rand() % 4;
    json_object_array_add(action, json_object_new_string(directions[dir_idx]));
    
    return action;
}
