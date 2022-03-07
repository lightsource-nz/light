typedef struct light_panel_type {
        light_component_t *driver_ic;
        void *child;
} light_panel_t;

typedef enum panel_transport {
        PANEL_TRANSPORT_I2C,
        PANEL_TRANSPORT_SPI
} panel_transport_t;

typedef struct light_panel_type_oled1p3in {
        panel_transport_t transport;
} light_panel_oled1p3in_t;

uint8_t light_component_type_display_panel_init(light_component_type_t *type);

uint8_t light_component_type_display_panel_create(light_component_t *cmp);

void light_component_type_display_panel_release(light_component_t *cmp);

uint8_t light_component_type_display_panel_oled1p3in_init(light_component_type_t *type);

uint8_t light_component_type_display_panel_oled1p3in_create(light_component_t *cmp);

void light_component_type_display_panel_oled1p3in_release(light_component_t *cmp);

uint8_t light_component_type_display_panel_oled1p3in_i2c_init(light_component_type_t *type);

uint8_t light_component_type_display_panel_oled1p3in_i2c_create(light_component_t *cmp);

void light_component_type_display_panel_oled1p3in_i2c_release(light_component_t *cmp);

uint8_t light_component_type_display_panel_oled1p3in_spi_init(light_component_type_t *type);

uint8_t light_component_type_display_panel_oled1p3in_spi_create(light_component_t *cmp);

void light_component_type_display_panel_oled1p3in_spi_release(light_component_t *cmp);
