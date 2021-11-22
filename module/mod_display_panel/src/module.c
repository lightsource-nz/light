#include <light.h>
#include <light/module.h>
#include <light/component.h>

#include <light_core.h>
#include <light/mod_display_ic.h>
#include <light/mod_display_panel.h>

#include <stddef.h>

static light_component_t component_type_display_panel = {
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_PANEL
};

static light_module_t this_module = {
        .name = LIGHT_MODULE_NAME_DISPLAY_PANEL,
        .type = LIGHT_MODULE_BASE,
        .init = &light_display_panel_init,
        .deps_count = 2,
        .depends_on = { LIGHT_MODULE_NAME_LIGHT_CORE,
                        LIGHT_MODULE_NAME_DISPLAY_IC },
        .decl_count = 0
};

LIGHT_MODULE_IMPLEMENT(this_module);

void light_display_panel_init(light_app_context_t *app)
{
        light_component_type_register(&component_type_display_panel);

}

light_module_t *light_display_panel_module_get()
{
        return &this_module;
}
