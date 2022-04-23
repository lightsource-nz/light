
#ifndef __LIGHT_H
#define __LIGHT_H

#include <stdint.h>
#include <stddef.h>     // required for size_t

#include "conf_light.h"

#define LIGHT_ATTR_PREMAIN                      __attribute__((constructor))

#define LIGHT_STATUS_MAXVALUE                   UINT8_MAX

// zero return value means success,
// greater-than-zero means internal error or validation failure
#define LIGHT_OK                                0
#define LIGHT_ALLOC_LIMIT_REACHED               1
#define LIGHT_ALLOC_FAILURE                     2
#define LIGHT_INVALID_ARG                       3
#define LIGHT_RESOURCE_UNAVAILABLE              4

#define LIGHT_OK_STRING                     "OK"
#define LIGHT_INVALID_ARG_STRING            "Invalid argument"
#define LIGHT_ALLOC_LIMIT_REACHED_STRING    "Static memory limit reached"
#define LIGHT_ALLOC_FAILURE_STRING          "Dynamic memory allocation failed"
#define LIGHT_RESOURCE_UNAVAILABLE_STRING   "Hardware resource unavailable"
#define LIGHT_STATUS_UNDEF_STRING           "Undefined status code"

// data structure constants
#define LIGHT_MODULE_DEPS_MAX               32
#define LIGHT_MODULE_DECL_MAX               32
#define LIGHT_MODULE_IMPL_MAX               32

#define LIGHT_DESCRIPTOR_NAME_MAX_LENGTH    32

typedef struct _light_app_context light_app_context_t;
typedef struct _light_module light_module_t;
 
typedef void (light_module_init_func_t)(light_app_context_t *app);

typedef enum _light_module_type {
    LIGHT_MODULE_BASE = 0,
    LIGHT_MODULE_ABSTRACT = 1
} light_module_type_t;


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

static inline const uint8_t *light_status_code_to_message(const uint8_t code)
{
    switch (code)
    {
    case LIGHT_OK:
        return LIGHT_OK_STRING;
        
    case LIGHT_INVALID_ARG:
        return LIGHT_INVALID_ARG_STRING;
        
    case LIGHT_ALLOC_LIMIT_REACHED:
        return LIGHT_ALLOC_LIMIT_REACHED_STRING;
        
    case LIGHT_ALLOC_FAILURE:
        return LIGHT_ALLOC_FAILURE_STRING;
    
    default:
        return LIGHT_STATUS_UNDEF_STRING;
    }
}

#include <light/log.h>
#include <light/component.h>

void light_init(light_app_context_t *app);

uint8_t light_app_activate_modules(light_app_context_t *app);

uint8_t light_module_register(light_app_context_t *app, light_module_t *mod);

uint8_t light_module_activate(light_app_context_t *app, light_module_t *mod);

uint8_t light_descriptor_write(uint8_t *buffer, uint8_t *name, size_t field_length);

uint8_t light_descriptor_write_name(uint8_t *buffer, uint8_t *name);

// linkage point for BSP logging function
extern void _light_board_log_handler(const char *msg);

#endif
