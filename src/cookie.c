#include <stdlib.h>
#include <stdio.h>
#include "cookie.h"

cookie_t *cookie_create()
{
    cookie_t *cookie = malloc(sizeof(cookie_t));
    cookie->fields_num = 0;

    return cookie;
}

void cookie_destroy(cookie_t *cookie)
{
    for (int i = 0; i < cookie->fields_num; i++) {
        free(cookie->cookie[i]);
    }
    free(cookie);
}

void cookie_print(cookie_t *cookie)
{
    printf("Cookie:\n");
    printf("\tNumber of fields: %d\n", cookie->fields_num);
    for (int i = 0; i < cookie->fields_num; i++) {
        printf("\tField %d: %s\n", i, cookie->cookie[i]);
    }
}
