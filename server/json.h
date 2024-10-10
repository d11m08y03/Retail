#ifndef JSON_H
#define JSON_H

#include "globals.h"
#include <stdlib.h>

typedef struct json_pair_t {
  char *key;
  char *value;
} json_pair_t;

typedef struct {
  json_pair_t *pairs;
  size_t count;
} json_object_t;

json_object_t *json_init_object(void);
void json_add_pair(json_object_t *obj, const char *key, const char *value);
char *json_stringify(const json_object_t *obj);
void json_free_object(json_object_t *obj);
char *json_from_body(const char *buffer);
json_object_t *json_from_string(const char *json_string);
void json_print_object(const json_object_t *obj);
char *json_get_value_by_key(const json_object_t *obj, const char *key);

#endif // !JSON_H
