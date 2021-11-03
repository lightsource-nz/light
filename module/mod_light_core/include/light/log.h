#ifndef __LIGHT_LOG_H
#define __LIGHT_LOG_H

#include <stdint.h>

typedef void (light_log_method_t)(const char *msg);

typedef struct _light_log_context {
        light_log_method_t *handler;
} light_log_context_t;

extern light_log_context_t *_light_log_default;

extern void light_log(uint8_t code, const char *msg);

extern void light_log_to_logger(light_log_context_t *logger, uint8_t code, const char *msg);

#endif
