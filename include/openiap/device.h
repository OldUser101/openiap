// SPDX-License-Identifier: BSD-2-Clause
// openiap - An open implementation of the iPod Accessory Protocol
// Copyright (c) 2025, Nathan Gill

#pragma once

#ifndef OPENIAP_DEVICE_H
#define OPENIAP_DEVICE_H

#include <stdint.h>

#include <libusb-1.0/libusb.h>

typedef struct openiap_device {
    libusb_device *device;
    uint16_t product_id;
    uint8_t iap_interface;
    uint8_t iap_interface_alt;
    uint8_t iap_configuration;
} openiap_device_t;

#endif