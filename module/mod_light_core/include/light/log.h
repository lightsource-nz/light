#ifndef __LIGHT_LOG_H
#define __LIGHT_LOG_H

#include <stdint.h>
#include <stdarg.h>

#define LIGHT_TRACE     5
#define LIGHT_DEBUG     4
#define LIGHT_INFO      3
#define LIGHT_WARN      2
#define LIGHT_ERROR     1

typedef void (light_log_method_t)(const char *msg);

typedef struct _light_log_context {
        light_log_method_t *handler;
} light_log_context_t;

extern light_log_context_t *_light_log_default;

extern void light_log(uint8_t code, const char *msg, ...);

extern void light_log_to_logger(light_log_context_t *logger, uint8_t code, const char *msg, va_list args);

#endif
