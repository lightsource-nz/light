
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

#define LIGHT_COMPONENT_TYPE_ID_MAINBOARD           0
#define LIGHT_COMPONENT_TYPE_NAME_MAINBOARD         "mainboard"

// data structure constants
#define LIGHT_MODULE_DEPS_MAX               32
#define LIGHT_MODULE_DECL_MAX               32
#define LIGHT_MODULE_IMPL_MAX               32

typedef struct _light_app_context light_app_context_t;

typedef struct _light_component {
    uint8_t const *name;
    uint8_t (*init)(light_app_context_t *);
} light_component_t;

typedef void (light_module_init_func_t)(light_app_context_t *app);

typedef enum _light_module_type {
    LIGHT_MODULE_BASE = 0,
    LIGHT_MODULE_ABSTRACT = 1
} light_module_type_t;

typedef struct _light_module light_module_t;

typedef struct _light_module {
    uint8_t active;
    uint8_t const *name;
    const light_module_type_t type;
    light_module_init_func_t *init;
    const char *depends_on[LIGHT_MODULE_DEPS_MAX];
    const uint8_t deps_count;
    const char *declares[LIGHT_MODULE_DECL_MAX];
    const uint8_t decl_count;
} light_module_t;

typedef struct _light_app_context {
    uint8_t const *name;
    uint8_t module_count;
    light_module_t *module[LIGHT_ACTIVE_MODULES_MAX];
    const char *depends_on[LIGHT_MODULE_DEPS_MAX];
    const uint8_t deps_count;
} light_app_context_t;


#include <light/log.h>

void light_init(light_app_context_t *app);

uint8_t light_app_activate_modules(light_app_context_t *app);

uint8_t light_component_type_register(light_component_t *ct);

light_component_t *light_component_type_get(char *name);

uint8_t light_module_register(light_app_context_t *app, light_module_t *mod);

uint8_t light_module_activate(light_app_context_t *app, light_module_t *mod);

// linkage point for BSP logging function
extern void _light_board_log_handler(const char *msg);

#endif
