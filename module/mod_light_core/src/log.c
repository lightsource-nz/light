#include <light.h>

#include <stdio.h>
#include <pico/stdio.h>

void light_log(uint8_t code, const char *msg)
{
        light_log_to_logger(&_light_board_log_handler, code, msg);
}

// dumb logger implementation ignores code and passes msg directly
extern void light_log_to_logger(light_log_context_t *logger, uint8_t code, const char *msg)
{
        (void) code;
        logger->handler(msg);
}