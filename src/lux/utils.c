#include "utils.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>

void log_message(LogLevel level, const char* format, ...) {
    time_t now;
    time(&now);
    char* date = ctime(&now);
    date[strlen(date) - 1] = '\0'; // 移除换行符

    const char* level_str[] = {
        "DEBUG",
        "INFO",
        "WARNING",
        "ERROR"
    };

    fprintf(stderr, "[%s] %s: ", date, level_str[level]);
    
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    
    fprintf(stderr, "\n");
}

int json_get_int(struct json_object* obj, const char* key, int default_value) {
    struct json_object* value;
    if (!json_object_object_get_ex(obj, key, &value)) {
        return default_value;
    }
    return json_object_get_int(value);
}

double json_get_double(struct json_object* obj, const char* key, double default_value) {
    struct json_object* value;
    if (!json_object_object_get_ex(obj, key, &value)) {
        return default_value;
    }
    return json_object_get_double(value);
}

const char* json_get_string(struct json_object* obj, const char* key, const char* default_value) {
    struct json_object* value;
    if (!json_object_object_get_ex(obj, key, &value)) {
        return default_value;
    }
    return json_object_get_string(value);
}
