// SPDX-License-Identifier: BSD-2-Clause
// openiap - An open implementation of the iPod Accessory Protocol
// Copyright (c) 2025, Nathan Gill

#pragma once

#ifndef OPENIAP_H
#define OPENIAP_H

typedef struct openiap_config openiap_config_t;

int openiap_init(void);
void openiap_exit(void);

const char *openiap_get_error(int code); 

#endif