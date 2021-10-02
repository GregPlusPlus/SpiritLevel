#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdio.h>
#include <errno.h>

#include "swo.h"

#define WRITE_PROTOTYPE int _write(int file, char *data, int len)
#define READ_PROTOTYPE int _read(int file, char *data, int len)

#endif // CONSOLE_H