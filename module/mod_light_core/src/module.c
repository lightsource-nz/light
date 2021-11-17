#include <light.h>
#include <light/module.h>
#include <light_core.h>

#include <stdbool.h>
#include <stddef.h>

void light_core_init(light_app_context_t *app);
void light_core_do_log(const char *msg);

static light_component_t *light_component_type_table[LIGHT_COMPONENT_TYPES_MAX];
static uint8_t light_component_type_count;

static light_component_t component_type_mainboard = {
        .id = LIGHT_COMPONENT_TYPE_ID_MAINBOARD,
        .name = LIGHT_COMPONENT_TYPE_NAME_MAINBOARD
};

static light_app_context_t this_app;

static light_module_t this_module = {
        .init = &light_core_init
};

static light_log_context_t logger = {
        .handler = &light_core_do_log
};

light_module_t *_light_modules[LIGHT_DEFINED_MODULES_MAX];
uint8_t _light_module_count;

LIGHT_MODULE_IMPLEMENT(this_module);

void light_init()
{
        
}

light_app_context_t *light_primary_app_context_get()
{
        return &this_app;
}

light_module_t *light_core_module_get()
{
        return &this_module;
}

void light_core_init(light_app_context_t *app)
{
        light_log(LIGHT_DEBUG, "light_core module loaded");
        light_component_type_count = 0;
        light_component_type_register(&component_type_mainboard);

}

uint8_t light_component_type_register(light_component_t *ct)
{
        if(light_component_type_count < LIGHT_COMPONENT_TYPES_MAX) {
                light_component_type_table[light_component_type_count++] = ct;
                return LIGHT_OK;
        }
        return LIGHT_ALLOC_LIMIT_REACHED;
}

// light_component_type_get:
// search component table for the specified ID
light_component_t *light_component_type_get(uint8_t id)
{
        for(uint8_t i = 0; i < light_component_type_count; i++) {
                if(light_component_type_table[i]->id == id)
                        return light_component_type_table[i];
        }
        return NULL;
}

uint8_t light_module_register(light_app_context_t *app, light_module_t *mod)
{
        if(app->module_count < LIGHT_DEFINED_MODULES_MAX) {
                app->module[app->module_count++] = mod;
        } else return LIGHT_ALLOC_LIMIT_REACHED;

        return LIGHT_OK;
}

uint8_t light_app_activate_modules(light_app_context_t *app)
{
        for(uint8_t i = 0; i < app->module_count; i++) {
                light_module_activate(app, app->module[i]);
        }

        return LIGHT_OK;
}

uint8_t light_module_activate(light_app_context_t *app, light_module_t *mod)
{
        if(mod->active) return LIGHT_OK;

        mod->active = true;
        for(uint8_t i = 0; i < mod->deps_count; i++) {
                light_module_activate(app, mod->depends_on[i]);
        }

        // call module init handler, after dependencies are activated
        mod->init(app);

        return LIGHT_OK;
}

void light_core_do_log(const char *msg)
{
        _light_board_log_handler(msg);
}
