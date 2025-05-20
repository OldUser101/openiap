// SPDX-License-Identifier: BSD-2-Clause
// openiap - An open implementation of the iPod Accessory Protocol
// Copyright (c) 2025, Nathan Gill

#pragma once

#ifndef OPENIAP_H
#define OPENIAP_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct openiap_config openiap_config_t;
typedef struct openiap_device openiap_device_t;

int openiap_init(void);
void openiap_exit(void);

openiap_config_t *openiap_get_config();

int openiap_enumerate_devices(openiap_device_t ***devices, int *count);

const char *openiap_error_name(int code); 

#ifdef __cplusplus
}
#endif

#endif