
#ifndef __LIGHT_H
#define __LIGHT_H

#include <stdint.h>

#include "conf_light.h"

#define LIGHT_ATTR_PREMAIN                      __attribute__((constructor))

// zero return value means success,
// less-than-zero means validation failure,
// greater-than-zero means internal error
#define LIGHT_OK                                0
#define LIGHT_INVALID_ARG                       -1
#define LIGHT_ALLOC_LIMIT_REACHED               1

#define LIGHT_BOARD_TYPE_ID_MAINBOARD           0
#define LIGHT_BOARD_TYPE_NAME_MAINBOARD         "mainboard"

// data structure constants
#define LIGHT_MODULE_DEPS_MAX              32

typedef struct _light_board_type {
    uint8_t id;
    uint8_t const *name;
} light_board_type_t;

typedef struct _light_app_context light_app_context_t;

typedef void (light_module_init_func_t)(light_app_context_t *app);

typedef struct _light_module {
    light_module_init_func_t *init;
    uint8_t const *name;
} light_module_t;

typedef enum _light_module_type {
    MODULE_BASE = 0,
    MODULE_ABSTRACT = 1
} light_module_type_t;

typedef struct _light_module_desc light_module_desc_t;
typedef struct _light_module_desc {
    uint8_t const *name;
    light_module_type_t type;
    light_module_desc_t *depends_on[LIGHT_MODULE_DEPS_MAX];

} light_module_desc_t;

typedef struct _light_app_context {
    uint8_t module_count;
    light_module_t *module[LIGHT_ACTIVE_MODULES_MAX];
    uint8_t const *name;
} light_app_context_t;


#include <light/log.h>

void light_init();

uint8_t light_board_type_register(light_board_type_t *bt);

light_board_type_t *light_board_type_get(uint8_t id);

uint8_t light_module_register(light_app_context_t *app, light_module_t *mod);

// linkage point for BSP logging function
extern void _light_board_log_handler(const char *msg);

#endif
