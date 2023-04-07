#pragma once /* Inc */
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifdef __unix__
#include <unistd.h>
#endif

#include "error_handling.h"
#include "types.h"

#define buf_size 64