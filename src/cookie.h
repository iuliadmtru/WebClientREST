#ifndef _COOKIE_H_
#define _COOKIE_H_

#include <string.h>

#define COOKIE_FIELDS_MAXNUM 10

struct cookie_t {
    int fields_num;
    char *cookie[COOKIE_FIELDS_MAXNUM];
};
typedef struct cookie_t cookie_t;

cookie_t *cookie_create();

void cookie_destroy(cookie_t *cookie);

void cookie_add_field(cookie_t *cookie, char *field);

void cookie_print(cookie_t *cookie, FILE *fout);

#endif  // _COOKIE_H_
