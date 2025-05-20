// SPDX-License-Identifier: BSD-2-Clause
// openiap - An open implementation of the iPod Accessory Protocol
// Copyright (c) 2025, Nathan Gill

#include "openiap/openiap.h"
#include "openiap/device.h"
#include "openiap/error.h"

#include <stdlib.h>
#include <stdint.h>

typedef struct openiap_config {
    libusb_context *libusb_ctx;
} openiap_config_t;

int probe_device(libusb_device *device, openiap_device_t **o_device) {
    struct libusb_device_descriptor desc;
    struct libusb_config_descriptor *config;
    int r;

    (*o_device) = NULL;

    libusb_get_device_descriptor(device, &desc);

    if (desc.idVendor != 0x05AC || desc.bNumConfigurations < 2) {  // Apple vendor (0x05AC)
        return OPENIAP_ERROR_NO_MATCHES;
    }

    for (int i = 0; i < desc.bNumConfigurations; i++) {
        r = libusb_get_config_descriptor(device, i, &config);
        if (r != 0) {
            continue;
        }

        for (int j = 0; j < config->bNumInterfaces; j++) {
            const struct libusb_interface *iface = &config->interface[j];
            for (int alt = 0; alt < iface->num_altsetting; alt++) {
                const struct libusb_interface_descriptor *altset = &iface->altsetting[alt];
                if (altset->bInterfaceClass == 0x03 || altset->bInterfaceClass == 0xFF) { // USB HID, or custom interface, used for iAP
                    (*o_device) = (openiap_device_t *)malloc(sizeof(openiap_device_t));
                    if (NULL == (*o_device)) {
                        libusb_free_config_descriptor(config);
                        return OPENIAP_ERROR_MEMORY_ALLOCATION;
                    }

                    libusb_ref_device(device);

                    (*o_device)->device = device;
                    (*o_device)->iap_configuration = i;
                    (*o_device)->iap_interface = j;
                    (*o_device)->iap_interface_alt = alt;
                    (*o_device)->product_id = desc.idProduct;

                    libusb_free_config_descriptor(config);
                    return OPENIAP_ERROR_SUCCESS;
                }
            }
        }

        libusb_free_config_descriptor(config);
    }

    return OPENIAP_ERROR_SUCCESS;
} 

int openiap_enumerate_devices(openiap_device_t ***devices, int *count) {
    if (NULL == count) {
        return OPENIAP_ERROR_NULL_POINTER;
    }

    ssize_t n_devices;
    libusb_device **list;
    int r;

    (*devices) = NULL;

    openiap_config_t *cfg = openiap_get_config();

    n_devices = libusb_get_device_list(cfg->libusb_ctx, &list);
    for (ssize_t idx = 0; idx < n_devices; ++idx) {
        libusb_device *dev = list[idx];
        openiap_device_t *o_dev = NULL;

        r = probe_device(dev, &o_dev);
        if (r != 0) {
            libusb_free_device_list(list, 1);
            return r;
        }

        if (NULL != o_dev) {
            (*devices) = (openiap_device_t**)realloc((*devices), sizeof(openiap_device_t*) * (*count + 1));
            if (NULL == devices) {
                libusb_free_device_list(list, 1);
                return OPENIAP_ERROR_MEMORY_ALLOCATION;
            }
            (*devices)[*count] = o_dev;
            ++(*count);
        }
    }

    libusb_free_device_list(list, 1);
    return OPENIAP_ERROR_SUCCESS;
}

