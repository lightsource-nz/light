#include <light.h>
#include <light_board.h>
#include <light/module.h>
#include <light_core.h>

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

void light_core_init(light_app_context_t *app);
void light_core_do_log(const char *msg);

static light_component_t *light_component_type_table[LIGHT_COMPONENT_TYPES_MAX];
static uint8_t light_component_type_count;

static light_component_t component_type_mainboard = {
        .name = LIGHT_COMPONENT_TYPE_NAME_MAINBOARD
};

static light_module_t this_module = {
        .init = &light_core_init,
        .name = LIGHT_MODULE_NAME_LIGHT_CORE,
        .type = LIGHT_MODULE_BASE,
        .deps_count = 0,
        .decl_count = 0
};

static light_log_context_t logger = {
        .handler = &light_core_do_log
};

light_module_t *_light_modules[LIGHT_DEFINED_MODULES_MAX];
uint8_t _light_module_count;

LIGHT_MODULE_IMPLEMENT(this_module);

// Light Framework external entry point:
// - populates module graph from module table and supplied config info
// - loads and initializes modules, performing dependency injection to provide
//      modules with the modules they require in correct order
void light_init(light_app_context_t *app)
{
        uint8_t res;
        if((res = light_board_init()) != LIGHT_OK) {
                // TODO handle boot failure somehow
                _exit(res);
        }
        light_log(LIGHT_INFO, "light_init: starting application [%s]\n", app->name);
        light_app_activate_modules(app);
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
// search component table for the specified component name
light_component_t *light_component_type_get(char *name)
{
        for(uint8_t i = 0; i < light_component_type_count; i++) {
                if(strcmp(light_component_type_table[i]->name, name))
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
        light_log(LIGHT_TRACE, "light_app_activate_modules: enter");
        for(uint8_t i = 0; i < app->module_count; i++) {
                light_module_activate(app, app->module[i]);
        }

        return LIGHT_OK;
}

uint8_t light_module_activate(light_app_context_t *app, light_module_t *mod)
{
        light_log(LIGHT_TRACE, "light_module_activate: %s\n", mod->name);
        if(mod->active) return LIGHT_OK;

        for(uint8_t i = 0; i < mod->deps_count; i++) {
                light_module_t *dep = light_module_reference_resolve(mod->depends_on[i]);
                if(dep == NULL) {
                        light_log(LIGHT_ERROR, "error: failed to resolve module reference \"%s\"", mod->depends_on[i]);
                        _exit(LIGHT_INVALID_ARG);
                }
                light_module_activate(app, dep);
        }

        mod->active = true;

        // call module init handler, after dependencies are activated
        mod->init(app);

        light_log(LIGHT_DEBUG, "module activated: %s\n", mod->name);

        return LIGHT_OK;
}

light_module_t *light_module_reference_resolve(const char *ref)
{
        light_log(LIGHT_TRACE, "light_module_reference_resolve: %s\n", ref);
        for(uint8_t i = 0; i < _light_module_count; i++) {
                if(strcmp(_light_modules[i]->name, ref)) {
                        return _light_modules[i];
                }
        }
        return NULL;
}

void light_core_do_log(const char *msg)
{
        _light_board_log_handler(msg);
}
