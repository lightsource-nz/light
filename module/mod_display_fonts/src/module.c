#include <light.h>
#include <light/module.h>

#include <light/mod_light_core.h>
#include <light/mod_display_fonts.h>

#include <stddef.h>

static light_module_t this_module = {
        .name = LIGHT_MODULE_NAME_DISPLAY_FONTS,
        .type = LIGHT_MODULE_BASE,
        .init = &light_display_fonts_init,
        .deps_count = 1,
        .depends_on = { LIGHT_MODULE_NAME_LIGHT_CORE },
        .decl_count = 0
};

LIGHT_MODULE_IMPLEMENT(this_module);

void light_display_fonts_init(light_app_context_t *app)
{

}

light_module_t *light_display_fonts_module_get()
{
        return &this_module;
}
