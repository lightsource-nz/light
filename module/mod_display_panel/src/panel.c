#include <light.h>
#include <light/module.h>
#include <light/component.h>

#include <light_core.h>
#include <light/mod_display_ic.h>
#include <light/mod_display_panel.h>

#include <stddef.h>
#include <stdlib.h>

#include <stdio.h>

#include <component/panel.h>

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

uint8_t light_component_type_display_panel_oled1p3in_init(light_component_type_t *type)
{

        return LIGHT_OK;
}
uint8_t light_component_type_display_panel_oled1p3in_create(light_component_t *cmp)
{
        light_log(LIGHT_TRACE, "%s: cmp.name = %s", __func__, cmp->name);

        light_panel_t *panel = (light_panel_t *) &cmp->object;
        light_panel_oled1p3in_t *child;
        
        if((child = malloc(sizeof(light_panel_oled1p3in_t))) == NULL) {
                return LIGHT_ALLOC_FAILURE;
        }
        
        panel->child = child;

        return LIGHT_OK;
}

void light_component_type_display_panel_oled1p3in_release(light_component_t *cmp)
{

}

uint8_t light_component_type_display_panel_oled1p3in_i2c_init(light_component_type_t *type)
{
        return LIGHT_OK;
}

// this allocates a bunch of stuff on the heap because it recursively creates subcomponents, and generates their descriptors in RAM
uint8_t light_component_type_display_panel_oled1p3in_i2c_create(light_component_t *cmp)
{
        light_component_t *driver = malloc(sizeof(light_component_t));
        uint8_t *name = calloc(sizeof(uint8_t), LIGHT_DESCRIPTOR_NAME_MAX_LENGTH);
        snprintf(name, LIGHT_DESCRIPTOR_NAME_MAX_LENGTH, "%s.driver", cmp->name);
        driver->name = name;
        driver->type = &component_type_display_panel_oled1p3in_i2c;
        
        uint8_t status;

        if(status = light_component_instance_create(driver)) {
                light_log(LIGHT_WARN, "failed to create component for display driver");
                return status;
        }

        light_panel_t *panel = (light_panel_t *) cmp->object;
        light_panel_oled1p3in_t *panel_0 = (light_panel_oled1p3in_t *)panel->child;
        panel->driver_ic = driver;
        panel_0->transport = PANEL_TRANSPORT_I2C;

        return LIGHT_OK;
}

// make sure to free the generated descriptor, after light_component_instance_destroy() removes all references to it
void light_component_type_display_panel_oled1p3in_i2c_release(light_component_t *cmp)
{
        light_panel_t *panel = (light_panel_t *) cmp->object;
        light_panel_oled1p3in_t *panel_0 = (light_panel_oled1p3in_t *)panel->child;
        light_component_instance_destroy(panel->driver_ic);
        free(panel->driver_ic->name);
        free(panel->driver_ic);
}

uint8_t light_component_type_display_panel_oled1p3in_spi_init(light_component_type_t *type)
{
        return LIGHT_OK;
}

uint8_t light_component_type_display_panel_oled1p3in_spi_create(light_component_t *cmp)
{
        light_component_t *driver = malloc(sizeof(light_component_t));
        uint8_t *name = calloc(sizeof(uint8_t), LIGHT_DESCRIPTOR_NAME_MAX_LENGTH);
        snprintf(name, LIGHT_DESCRIPTOR_NAME_MAX_LENGTH, "%s.driver", cmp->name);
        driver->name = name;
        driver->type = &component_type_display_panel_oled1p3in_spi;
        
        uint8_t status;

        if(status = light_component_instance_create(driver)) {
                light_log(LIGHT_WARN, "failed to create component for display driver");
                return status;
        }

        light_panel_t *panel = (light_panel_t *) cmp->object;
        light_panel_oled1p3in_t *panel_0 = (light_panel_oled1p3in_t *)panel->child;
        panel->driver_ic = driver;
        panel_0->transport = PANEL_TRANSPORT_SPI;

        return LIGHT_OK;
}

void light_component_type_display_panel_oled1p3in_spi_release(light_component_t *cmp)
{
        light_panel_t *panel = (light_panel_t *) cmp->object;
        light_panel_oled1p3in_t *panel_0 = (light_panel_oled1p3in_t *)panel->child;
        light_component_instance_destroy(panel->driver_ic);
        free(panel->driver_ic->name);
        free(panel->driver_ic);
}
