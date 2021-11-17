#include <light.h>
#include <light_core.h>

int main(void)
{
    light_app_context_t *app = light_primary_app_context_get();

    light_init();

    light_module_register(app, light_core_module_get());

    light_app_activate_modules(app); 
    
    return 0;
}
