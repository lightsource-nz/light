#include <light.h>
#include <light/mod_light_core.h>

static light_app_context_t this_app = {
        .name = "mod_light_core demo application",
        .deps_count = 1,
        .depends_on = { LIGHT_MODULE_NAME_LIGHT_CORE }
};

int main(void)
{
    light_app_context_t *app = &this_app;

    light_init(app);

    return 0;
}
