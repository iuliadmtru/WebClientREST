#ifndef _SERIALIZE_H_
#define _SERIALIZE_H_

#include "parson.h"
#include "command.h"

char *serialize_register(command_data_t cmd_data);

#endif  // _SERIALIZE_H_