#ifndef UTILS_H
#define UTILS_H

#include <json-c/json.h>

// 日志级别
typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
} LogLevel;

// 日志函数
void log_message(LogLevel level, const char* format, ...);

// JSON工具函数
int json_get_int(struct json_object* obj, const char* key, int default_value);
double json_get_double(struct json_object* obj, const char* key, double default_value);
const char* json_get_string(struct json_object* obj, const char* key, const char* default_value);

#endif
