#pragma once

#include <stddef.h>
//#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

#include <utils/types.h>
#include <usb/usbd.h>
#include <usb/usb_descriptor_types.h>

// custom request to upload data into the stack
#define USB_REQ_CUSTOM 0x30

void gfx_printf(const char *fmt, ...);
#define DEBUG(x, ...) gfx_printf(x, ##__VA_ARGS__)
#define INFO(x, ...) gfx_printf(x, ##__VA_ARGS__)
#define WARNING(x, ...) gfx_printf(x, ##__VA_ARGS__)
#define ERROR(x, ...) gfx_printf(x, ##__VA_ARGS__)

#define cpu_to_be32(x) byte_swap_32(x)
#define cpu_to_be16(x) byte_swap_16(x)
#define be32_to_cpu(x) byte_swap_32(x)
#define be16_to_cpu(x) byte_swap_16(x)
#define cpu_to_le16(x) (x)
#define cpu_to_le32(x) (x)
#define le16_to_cpu(x) (x)
#define le32_to_cpu(x) (x)

#define container_of(ptr, type, member) ({                      \
        const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
        (type *)( (char *)__mptr - offsetof(type,member) );})

#define min(x, y) (((x) < (y)) ? (x) : (y))

#if defined(static_assert)
#define CHECK_SIZE(type, size) static_assert(sizeof(type) == size, #type " must be " #size " bytes")
#else
#define CHECK_SIZE(type, size)
#endif

typedef uint32_t be32ptr_t;

typedef struct udpih_device udpih_device_t;

enum {
    STATE_INIT,

    STATE_DEVICE0_CONNECTED,
    //STATE_DEVICE0_READY,
    //STATE_DEVICE0_DISCONNECTED,

    STATE_DEVICE1_CONNECTED,
    //STATE_DEVICE1_READY,
    //STATE_DEVICE1_DISCONNECTED,

    STATE_DEVICE2_CONNECTED,
};

typedef struct udpih_device {
    // the current state
    int state;
} udpih_device_t;

//int device_bind(udpih_device_t* device, uint16_t maxpacket);

int device_setup(udpih_device_t* device, const usb_ctrl_setup_t* ctrlrequest, uint8_t* buf, bool high_speed);
