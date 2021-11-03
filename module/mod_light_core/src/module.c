#include <light.h>
#include <light_core.h>

void light_core_init(light_app_context_t *app);

static light_board_type_t *light_board_type_table[LIGHT_BOARD_TYPES_MAX];
static uint8_t light_board_type_count;

static light_board_type_t board_type_mainboard = {
        .name = LIGHT_BOARD_TYPE_NAME_MAINBOARD
};

static light_app_context_t this_app;

static light_module_t this_module = {
        .init = &light_core_init
};

static light_log_context_t logger = {
        .handler = &light_core_do_log
};

void light_init()
{
        light_module_register(&this_app, &this_module);
}

void light_core_init(light_app_context_t *app)
{
        light_board_type_count = 0;
        light_board_type_register(LIGHT_BOARD_TYPE_ID_MAINBOARD, &board_type_mainboard);

}

uint8_t light_board_type_register(uint8_t id, light_board_type_t *bt)
{
        if(id < LIGHT_BOARD_TYPES_MAX) {
                if(light_board_type_count < LIGHT_BOARD_TYPES_MAX) {
                        light_board_type_table[id] = bt;
                        light_board_type_count++; 
                }
                return LIGHT_ALLOC_LIMIT_REACHED;
        }
        return LIGHT_INVALID_ARG;
        
}

light_board_type_t *light_board_type_get(uint8_t id)
{
        if(id < LIGHT_BOARD_TYPES_MAX) {
                return light_board_type_table[id];
        }
        return NULL;
}

uint8_t light_module_register(light_app_context_t *app, light_module_t *mod)
{
        if(app->module_count < LIGHT_DEFINED_MODULES_MAX) {
                app->module[app->module_count++] = mod;
        } else {
                return LIGHT_ALLOC_LIMIT_REACHED;
        }
        return LIGHT_OK;
}

void light_core_do_log(const char *msg)
{
        _light_board_log_handler(msg);
}
