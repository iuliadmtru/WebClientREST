#include "parson.h"
#include "command.h"
#include "serialize.h"

char *serialize_register(command_data_t cmd_data)
{
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);

    json_object_set_string(root_object, "username", cmd_data.username);
    json_object_set_string(root_object, "password", cmd_data.password);

    char *serialized_string = json_serialize_to_string_pretty(root_value);

    json_value_free(root_value);

    return serialized_string;
}
