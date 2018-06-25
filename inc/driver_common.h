#ifndef __DRIVER_COMMON_H__
#define __DRIVER_COMMON_H__

#include "stdint.h"

typedef enum
{
    // Generic Return Values
    DRIVER_OK = 0x00,
    DRIVER_TIMEOUT,
    DRIVER_ERROR_INVALID_PARAM,
    // Driver Specifi Return Values
    // Default Error Value
    DRIVER_ERROR_UNKNOWN = 0xFF,
} Driver_Status;

#endif // __DRIVER_COMMON_H__
