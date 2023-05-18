#ifndef _COOKIE_H_
#define _COOKIE_H_

struct cookie_t {
    int fields_num;
    char *cookie[];
};
typedef struct cookie_t cookie_t;

cookie_t *cookie_create();

void cookie_destroy(cookie_t *cookie);

void cookie_print(cookie_t *cookie);

#endif  // _COOKIE_H_
