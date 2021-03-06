#include <light.h>
#include <light/module.h>
#include <light/component.h>

#include <light/mod_light_core.h>
#include <light/mod_display_ic.h>
#include <light/mod_display_panel.h>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <light/display_panel.h>

uint8_t light_component_type_display_panel_init(light_component_type_t *type)
{
        light_log(LIGHT_TRACE, "%s: type.name = %s", __func__, type->name);

        return LIGHT_OK;
}

uint8_t light_component_type_display_panel_create(light_component_t *cmp)
{
        light_log(LIGHT_TRACE, "%s: cmp.name = %s", __func__, cmp->name);
        
        if((cmp->object = malloc(sizeof(light_panel_t))) == NULL) {
                return LIGHT_ALLOC_FAILURE;
        }

        light_panel_t *panel = (light_panel_t *) &cmp->object;


        return LIGHT_OK;
}

void light_component_type_display_panel_release(light_component_t *cmp)
{
        free(&cmp->object);
}

void light_component_type_display_panel_update(light_component_t *cmp, const uint8_t *refname, const uint8_t *value)
{

}

uint8_t light_component_type_display_panel_oled1p3in_init(light_component_type_t *type)
{

        return LIGHT_OK;
}
uint8_t light_component_type_display_panel_oled1p3in_create(light_component_t *cmp)
{
        light_log(LIGHT_TRACE, "%s: cmp.name = %s", __func__, cmp->name);

        light_panel_t *panel = (light_panel_t *) &cmp->object;

        panel->x_pixels = LIGHT_COMPONENT_DISPLAY_PANEL_OLED1P3IN_X_PIXELS;
        panel->y_pixels = LIGHT_COMPONENT_DISPLAY_PANEL_OLED1P3IN_Y_PIXELS;

        /*light_panel_oled1p3in_t *child;
        
        if((child = malloc(sizeof(light_panel_oled1p3in_t))) == NULL) {
                return LIGHT_ALLOC_FAILURE;
        }
        
        panel->child = child;
        */

        return LIGHT_OK;
}

void light_component_type_display_panel_oled1p3in_release(light_component_t *cmp)
{
        
}
void light_component_type_display_panel_oled1p3in_update(light_component_t *cmp, const uint8_t *refname, const uint8_t *value)
{

}

uint8_t light_component_display_panel_get_x_dimension(light_component_t *cmp)
{
        light_panel_t *panel = (light_panel_t *) &cmp->object;
        return panel->x_pixels;
}

uint8_t light_component_display_panel_get_y_dimension(light_component_t *cmp)
{
        light_panel_t *panel = (light_panel_t *) &cmp->object;
        return panel->y_pixels;
}

/*
uint8_t light_component_type_display_panel_oled1p3in_i2c_init(light_component_type_t *type)
{
        return LIGHT_OK;
}

// this allocates a bunch of stuff on the heap because it recursively creates subcomponents, and generates their descriptors in RAM
uint8_t light_component_type_display_panel_oled1p3in_i2c_create(light_component_t *cmp)
{
        light_component_t *driver = malloc(sizeof(light_component_t));

        // ^ TODO null check this pointer to make sure malloc was successful


        if(strlen(cmp->name) > (LIGHT_DESCRIPTOR_NAME_MAX_LENGTH - 7)) {
                return LIGHT_ALLOC_LIMIT_REACHED;
        }
        snprintf(driver->name, LIGHT_DESCRIPTOR_NAME_MAX_LENGTH, "%s.driver", cmp->name);

        driver->type = &component_type_display_ic_sh1107_i2c;
        

        light_component_pindef_t *next_pin = light_component_instance_get_pin_by_name(cmp, LIGHT_PANEL_PIN_NAME_SCL);
        light_component_pindef_t *next_driver_pin = light_component_instance_get_pin_by_name(driver, LIGHT_DISPLAY_IC_PIN_NAME_I2C_SCL);

        next_driver_pin->id = next_pin->id;

        next_pin = light_component_instance_get_pin_by_name(cmp, LIGHT_PANEL_PIN_NAME_SDA);
        next_driver_pin = light_component_instance_get_pin_by_name(driver, LIGHT_DISPLAY_IC_PIN_NAME_I2C_SDA);

        next_driver_pin->id = next_pin->id;

        uint8_t status;
        if(status = light_component_spawn(driver)) {
                light_log(LIGHT_WARN, "failed to create component for display driver");
                return status;
        }

        light_panel_t *panel = (light_panel_t *) cmp->object;
        light_panel_oled1p3in_t *panel_0 = (light_panel_oled1p3in_t *)panel->child;
        panel->driver_ic = driver;
        panel_0->transport = PANEL_TRANSPORT_I2C;

        return LIGHT_OK;
}

// make sure to free the generated descriptor, after light_component_destroy() removes all references to it
void light_component_type_display_panel_oled1p3in_i2c_release(light_component_t *cmp)
{
        
}

void light_component_type_display_panel_oled1p3in_i2c_update(light_component_t *cmp, const uint8_t *refname, const uint8_t *value)
{

}

uint8_t light_component_type_display_panel_oled1p3in_spi_init(light_component_type_t *type)
{
        return LIGHT_OK;
}

uint8_t light_component_type_display_panel_oled1p3in_spi_create(light_component_t *cmp)
{
        /*
        light_component_t *driver = malloc(sizeof(light_component_t));
        uint8_t *name = calloc(sizeof(uint8_t), LIGHT_DESCRIPTOR_NAME_MAX_LENGTH);
        snprintf(name, LIGHT_DESCRIPTOR_NAME_MAX_LENGTH, "%s.display_ic", cmp->name);
        light_descriptor_write_name(driver->name, name);
        driver->type = &component_type_display_panel_oled1p3in_spi;
        
        uint8_t status;

        if(status = light_component_spawn(driver)) {
                light_log(LIGHT_WARN, "failed to create component for display driver");
                return status;
        }

        light_panel_t *panel = (light_panel_t *) cmp->object;
        light_panel_oled1p3in_t *panel_0 = (light_panel_oled1p3in_t *)panel->child;
        //panel->driver_ic = driver;
        panel_0->transport = PANEL_TRANSPORT_SPI;

        return LIGHT_OK;
}

void light_component_type_display_panel_oled1p3in_spi_release(light_component_t *cmp)
{
        
}

void light_component_type_display_panel_oled1p3in_spi_update(light_component_t *cmp, const uint8_t *refname, const uint8_t *value)
{

}
*/