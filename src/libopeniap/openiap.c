// SPDX-License-Identifier: BSD-2-Clause
// openiap - An open implementation of the iPod Accessory Protocol
// Copyright (c) 2025, Nathan Gill

#include <stdlib.h>

#include <libusb-1.0/libusb.h>

#include "openiap/openiap.h"
#include "openiap/error.h"

typedef struct openiap_config {
    libusb_context *libusb_ctx;
} openiap_config_t;

static openiap_config_t *openiap_cfg;

int openiap_init(void) {
    if (NULL != openiap_cfg) { // Don't initialize twice to avoid a memory leak
        return OPENIAP_ERROR_ALREADY_INITIALIZED;
    }

    openiap_cfg = (openiap_config_t*)malloc(sizeof(openiap_config_t));
    if (NULL == openiap_cfg) {
        return OPENIAP_ERROR_MEMORY_ALLOCATION;
    }

    int r = libusb_init_context(&openiap_cfg->libusb_ctx, NULL, 0);
    if (r < 0) {
        free(openiap_cfg);
        openiap_cfg = NULL;
        return r;
    }

    return OPENIAP_ERROR_SUCCESS;
}

void openiap_exit(void) {
    if (NULL != openiap_cfg) {
        libusb_exit(openiap_cfg->libusb_ctx);
        free(openiap_cfg);
        openiap_cfg = NULL;
    }
}