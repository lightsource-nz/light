#include <light.h>
#include <light/mod_light_core.h>
#include <light/mod_display_fonts.h>

static light_app_context_t this_app = {
        .name = "mod_display_fonts demo application",
        .deps_count = 2,
        .depends_on = {
            LIGHT_MODULE_NAME_LIGHT_CORE,
            LIGHT_MODULE_NAME_DISPLAY_FONTS
        }
};

int main(void)
{
    light_app_context_t *app = &this_app;

    light_init(app);

    return 0;
}
