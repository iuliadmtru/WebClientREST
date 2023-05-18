#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cookie.h"

cookie_t *cookie_create()
{
    cookie_t *cookie = malloc(sizeof(cookie_t));
    cookie->fields_num = 0;

    return cookie;
}

void cookie_destroy(cookie_t *cookie)
{
    if (!cookie)
        return;

    for (int i = 0; i < cookie->fields_num; i++) {
        free(cookie->cookie[i]);
    }
    free(cookie);
}

void cookie_add_field(cookie_t *cookie, char *field)
{
    char *new_field = strdup(field);
    if (!new_field)
        return;
    
    cookie->cookie[cookie->fields_num] = new_field;
    cookie->fields_num++;
}

char *cookie_to_string(cookie_t *cookie)
{
    int last = cookie->fields_num - 1;
    int total_len = 0;
    for (int i = 0; i <= last; i++) {
        total_len += strlen(cookie->cookie[i]) + 1;
    }

    char *cookie_str = malloc(total_len);
    char *dst = cookie_str;
    for (int i = 0; i < last; i++) {
        int len = strlen(cookie->cookie[i]);
        memcpy(dst, cookie->cookie[i], len);
        memcpy(dst + len, " ", 1);
        dst += (len + 1);
    }

    strcpy(dst, cookie->cookie[last]);

    // printf("cookie_str: %s\n", cookie_str);

    return cookie_str;
}

void cookie_print(cookie_t *cookie, FILE *fout)
{
    fprintf(fout, "Cookie:\n");
    fprintf(fout, "\tNumber of fields: %d\n", cookie->fields_num);
    for (int i = 0; i < cookie->fields_num; i++) {
        fprintf(fout, "\tField %d: %s\n", i, cookie->cookie[i]);
    }
}
