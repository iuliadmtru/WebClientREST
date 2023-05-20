#ifndef _SERIALIZE_H_
#define _SERIALIZE_H_

#include "parson.h"
#include "command.h"

/*
 * Serialize user input to JSON for POST and DELETE requests.
 */
char *serialize_register(command_data_t cmd_data);
char *serialize_login(command_data_t cmd_data);
char *serialize_add_book(command_data_t cmd_data);
char *serialize_delete_book(command_data_t cmd_data);

#endif  // _SERIALIZE_H_
