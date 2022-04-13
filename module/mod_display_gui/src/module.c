#include <light.h>
#include <light/module.h>
#include <light/component.h>

#include <light/mod_light_core.h>
#include <light/mod_display_gui.h>
#include <light/mod_display_ic.h>
#include <light/mod_display_panel.h>

#include <light/display_panel.h>
#include <light/display_gui.h>

#include <stddef.h>
#include <stdlib.h>


typedef struct gui_prop {
        gui_render_context_t context;
        uint8_t *image;
} gui_prop_t;

light_component_type_t component_type_display_gui = {
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_GUI,
        .parent = NULL,
        .is_abstract = LIGHT_COMPONENT_TYPE_IS_ABSTRACT,
        .pin_count = 0,
        .init = light_component_type_display_gui_init,
        .create = light_component_type_display_gui_create
};

light_component_type_t component_type_display_gui_64x128 = {
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_GUI_64X128,
        .parent = NULL,
        .is_abstract = LIGHT_COMPONENT_TYPE_IS_CONCRETE,
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
        light_component_type_register(&component_type_display_gui_64x128);
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
        gui_render_context_t *prop;
        if(!(prop = malloc(sizeof(gui_prop_t)))) {
                return LIGHT_ALLOC_FAILURE;
        }

        cmp->object = prop;

        return LIGHT_OK;
}

uint8_t light_component_type_display_gui_64x128_init(light_component_type_t *type)
{
        return LIGHT_OK;
}

uint8_t light_component_type_display_gui_64x128_create(light_component_t *cmp)
{
        gui_prop_t *prop = (gui_prop_t *)cmp->object;
        if(prop->image = calloc(64 * 128, sizeof(uint8_t))) {
                return LIGHT_ALLOC_FAILURE;
        }
        paint_ctx = &prop->context;
        Paint_NewImage(prop->image, 128, 64, ROTATE_0, BLACK);
        return LIGHT_OK;
}

uint8_t light_component_action_display_gui_set_context(light_component_t *cmp)
{
        if(!light_component_instance_is_of_type(cmp, LIGHT_COMPONENT_TYPE_NAME_DISPLAY_GUI)) {
                return LIGHT_INVALID_ARG;
        }

        gui_prop_t *prop = (gui_prop_t *)cmp->object;

        paint_ctx = &prop->context;
        
        return LIGHT_OK;
}
