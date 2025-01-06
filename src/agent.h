#ifndef AGENT_H
#define AGENT_H

#include <json-c/json.h>

typedef struct {
    char* player;
    int team_id;
    int opp_team_id;
    struct json_object* env_cfg;
    
    // 存储已发现的遗迹节点位置
    int* relic_node_positions;
    int relic_nodes_count;
    int* discovered_relic_nodes_ids;
    int discovered_nodes_count;
    
    // 单位探索位置
    int** unit_explore_locations;
    int units_count;
} Agent;

// 初始化智能体
Agent* agent_create(const char* player, struct json_object* env_cfg);

// 释放智能体资源
void agent_destroy(Agent* agent);

// 执行动作
struct json_object* agent_act(Agent* agent, int step, struct json_object* obs, int remaining_overage_time);

#endif
