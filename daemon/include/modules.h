#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <orbis/libkernel.h>
#include <orbis/Sysmodule.h>

#include "constants.h"

int loadInternalModules();

int loadLibjbc();

bool (*jailbreak)();