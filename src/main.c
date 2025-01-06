#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include "agent.h"
#include "lux/kit.h"

#define BUFFER_SIZE 1048576  // 1MB buffer

int main() {
    char buffer[BUFFER_SIZE];
    struct json_object *env_cfg = NULL;
    Agent *agent = NULL;
    
    // 读取环境配置
    if (fgets(buffer, BUFFER_SIZE, stdin)) {
        env_cfg = json_tokener_parse(buffer);
        if (!env_cfg) {
            fprintf(stderr, "Failed to parse env_cfg\n");
            return 1;
        }
    }

    // 读取玩家ID
    if (fgets(buffer, BUFFER_SIZE, stdin)) {
        // 移除换行符
        buffer[strcspn(buffer, "\n")] = 0;
        agent = agent_create(buffer, env_cfg);
        if (!agent) {
            fprintf(stderr, "Failed to create agent\n");
            json_object_put(env_cfg);
            return 1;
        }
    }

    // 主游戏循环
    while (fgets(buffer, BUFFER_SIZE, stdin)) {
        struct json_object *obs = json_tokener_parse(buffer);
        if (!obs) {
            fprintf(stderr, "Failed to parse observation\n");
            continue;
        }

        // 获取当前步数和剩余时间
        int step = 0;
        int remaining_overage_time = 0;
        
        struct json_object *step_obj, *time_obj;
        if (json_object_object_get_ex(obs, "step", &step_obj)) {
            step = json_object_get_int(step_obj);
        }
        if (json_object_object_get_ex(obs, "remainingOverageTime", &time_obj)) {
            remaining_overage_time = json_object_get_int(time_obj);
        }

        // 执行动作
        struct json_object *actions = agent_act(agent, step, obs, remaining_overage_time);
        
        // 输出动作
        printf("%s\n", json_object_to_json_string(actions));
        fflush(stdout);

        // 清理
        json_object_put(obs);
        json_object_put(actions);
    }

    // 清理资源
    agent_destroy(agent);
    json_object_put(env_cfg);
    
    return 0;
}
