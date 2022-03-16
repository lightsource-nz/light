#include <light.h>
#include <light/module.h>
#include <light/component.h>

#include <light_core.h>
#include <mod_display_gui.h>
#include <mod_display_ic.h>
#include <mod_display_panel.h>

#include <component/panel.h>
#include <light/gui.h>

#include <stddef.h>
#include <stdlib.h>


light_component_type_t component_type_display_gui = {
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_GUI,
        .parent = NULL,
        .pin_count = 0,
        .init = light_component_type_display_gui_init,
        .create = light_component_type_display_gui_create
};

static light_module_t this_module = {
        .name = LIGHT_MODULE_NAME_DISPLAY_GUI,
        .type = LIGHT_MODULE_BASE,
        .init = &light_display_gui_module_init,
        .deps_count = 3,
        .depends_on = { LIGHT_MODULE_NAME_LIGHT_CORE,
                        LIGHT_MODULE_NAME_DISPLAY_PANEL,
                        LIGHT_MODULE_NAME_DISPLAY_IC },
        .decl_count = 0
};

LIGHT_MODULE_IMPLEMENT(this_module);

void light_display_gui_module_init(light_app_context_t *app)
{
        light_component_type_register(&component_type_display_gui);
}

light_module_t *light_display_gui_module_get()
{
        return &this_module;
}

uint8_t light_component_type_display_gui_init(light_component_type_t *type)
{
        return LIGHT_OK;
}

uint8_t light_component_type_display_gui_create(light_component_t *cmp)
{
        gui_render_context_t *ctx;
        if(!(ctx = malloc(sizeof(gui_render_context_t)))) {
                return LIGHT_ALLOC_FAILURE;
        }

        cmp->object = ctx;
        return LIGHT_OK;
}
