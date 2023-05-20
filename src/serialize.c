#include "parson.h"
#include "command.h"
#include "serialize.h"
#include "cookie.h"

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

char *serialize_login(command_data_t cmd_data)
{
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);

    json_object_set_string(root_object, "username", cmd_data.username);
    json_object_set_string(root_object, "password", cmd_data.password);

    char *serialized_string = json_serialize_to_string_pretty(root_value);

    json_value_free(root_value);

    return serialized_string;
}

char *serialize_add_book(command_data_t cmd_data)
{
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);

    json_object_set_string(root_object, "title", cmd_data.book_title);
    json_object_set_string(root_object, "author", cmd_data.book_author);
    json_object_set_string(root_object, "genre", cmd_data.book_genre);
    json_object_set_number(root_object, "page_count", cmd_data.book_page_count);
    json_object_set_string(root_object, "publisher", cmd_data.book_publisher);

    char *serialized_string = json_serialize_to_string_pretty(root_value);

    json_value_free(root_value);

    return serialized_string;
}

char *serialize_delete_book(command_data_t cmd_data)
{
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);

    json_object_set_number(root_object, "id", cmd_data.book_id);
    char *serialized_string = json_serialize_to_string_pretty(root_value);

    json_value_free(root_value);

    return serialized_string;
}

char *serialize_logout(cookie_t *cookie)
{
    return cookie_to_string(cookie);
}
