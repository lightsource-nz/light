#include <light.h>

#include <stdio.h>
#include <pico/stdio.h>

static light_log_context_t default_logger = {
        .handler = &_light_board_log_handler
};

void light_log(uint8_t code, const char *__restrict msg, ...)
{
        va_list args;
        va_start(args, msg);
        light_log_to_logger(&default_logger, code, msg, args);
}

// TODO: add log-level to message format
extern void light_log_to_logger(light_log_context_t *logger, uint8_t code, const char *__restrict msg, va_list args)
{
        static char buffer[LIGHT_LOG_BUFFER_SIZE];
        (void) code;
        vsnprintf(buffer, LIGHT_LOG_BUFFER_SIZE, msg, args);
        logger->handler(buffer);
}