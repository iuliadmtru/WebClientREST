#include <assert.h>
#include <string.h>

#include "command.h"
#include "server_utils.h"
#include "helpers.h"

int main()
{
    return 0;
}

test_server_data(void)
{
    printf("---------- TEST SERVER DATA ----------\n");
    server_t server = server_init(SERVERADDR, SERVERPORT);
    assert(strcmp(server.ip, SERVERADDR) == 0);
    assert(server.port == SERVERPORT);
    printf("---------- TEST SERVER DATA: PASSED ----------\n");
}

test_user_input(void)
{
    test_register();
}

test_register(void)
{
    printf("Testing REGISTER command, enter details:\nusername: iulia123#\npassword: pass\n");

    char *cmd = "register";
    command_data_t cmd_data = command_get_data(cmd);

    assert(strcmp(cmd_data.username, "iulia123#") == 0);
    assert(strcmp(cmd_data.password, "pass") == 0);
}
