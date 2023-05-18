#ifndef _SERIALIZE_H_
#define _SERIALIZE_H_

#include "parson.h"
#include "command.h"

char *serialize_register(command_data_t cmd_data);

char *serialize_login(command_data_t cmd_data);

char **serialize_logout(cookie_t *cookie);

#endif  // _SERIALIZE_H_
