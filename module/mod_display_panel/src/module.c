#include <light.h>
#include <light/module.h>
#include <light/component.h>

#include <light_core.h>
#include <light/mod_display_ic.h>
#include <light/mod_display_panel.h>

#include <stddef.h>

static light_component_type_t component_type_display_panel = {
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_PANEL,
        .parent = NULL,
        .init = light_component_type_display_panel_init,
        .create = light_component_type_display_panel_create
};

static light_component_type_t component_type_display_panel_oled1p3in = {
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_PANEL_OLED1P3IN,
        .parent = &component_type_display_panel,
        .init = light_component_type_display_panel_oled1p3in_init,
        .create = light_component_type_display_panel_oled1p3in_create
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
        light_component_type_register(&component_type_display_panel_oled1p3in);

}

void light_component_type_display_panel_init(light_component_type_t *type)
{
        light_log(LIGHT_TRACE, "%s: type.name = %s", __func__, type->name);
}

void light_component_type_display_panel_create(light_component_t *cmp)
{
        light_log(LIGHT_TRACE, "%s: cmp.name = %s", __func__, cmp->name);

}

void light_component_type_display_panel_oled1p3in_init(light_component_type_t *type)
{

}
void light_component_type_display_panel_oled1p3in_create(light_component_t *type)
{

}

light_module_t *light_display_panel_module_get()
{
        return &this_module;
}
