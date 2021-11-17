#include <light.h>
#include <light/module.h>
                                              
#include <light/display_panel.h>

#include <stddef.h>

static light_component_t component_type_display_panel = {
        .id = LIGHT_COMPONENT_TYPE_ID_DISPLAY_PANEL,
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_PANEL
};

static light_module_t this_module = {
        .init = &light_display_panel_init
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
