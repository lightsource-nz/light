#include <light.h>
#include <light/module.h>
#include <light/component.h>

#include <light_core.h>
#include <light/mod_display_ic.h>

#include <stddef.h>

static light_component_type_t component_type_display_ic = {
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_IC
};

static light_module_t this_module = {
        .name = LIGHT_MODULE_NAME_DISPLAY_IC,
        .type = LIGHT_MODULE_BASE,
        .init = &light_display_ic_init,
        .depends_on = { LIGHT_MODULE_NAME_LIGHT_CORE }
};

LIGHT_MODULE_IMPLEMENT(this_module);

void light_display_ic_init(light_app_context_t *app)
{
        light_component_type_register(&component_type_display_ic);

}

light_module_t *light_display_ic_module_get()
{
        return &this_module;
}