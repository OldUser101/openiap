// SPDX-License-Identifier: BSD-2-Clause
// openiap - An open implementation of the iPod Accessory Protocol
// Copyright (c) 2025, Nathan Gill

#include "openiap/openiap.h"
#include "openiap/error.h"

static const char *error_list[] = {
    "OPENIAP_UNKNOWN",
    "OPENIAP_SUCCESS",
    "OPENIAP_GENERAL_FAILURE",
    "OPENIAP_MEMORY_ALLOCATION_ERROR",
    "OPENIAP_ALREADY_INITIALIZED",
    "OPENIAP_NULL_POINTER",
    "OPENIAP_NO_MATCHES",
    "OPENIAP_NOT_INITIALIZED",
};

const char *openiap_error_name(int code) {
    if (code == 0) { // Return success if the code is zero
        return error_list[1];
    } else if (code > OPENIAP_MAX_ERROR) { // Code out of range, unknown error
        return error_list[0];
    }
    return error_list[code - 999]; // Subtract 999, so 1 corresponds to "OPENIAP_GENERAL_FAILURE"
}