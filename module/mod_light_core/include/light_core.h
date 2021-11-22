#ifndef __LIGHT_CORE_H
#define __LIGHT_CORE_H

#include <light.h>

#define LIGHT_MODULE_NAME_LIGHT_CORE                "light.core"

#define LIGHT_COMPONENT_TYPE_ID_MAINBOARD           0
#define LIGHT_COMPONENT_TYPE_NAME_MAINBOARD         "mainboard"

light_module_t *light_core_module_get();

#endif
