#include <stdlib.h>
#include <string.h>

#include "json.h"

json_object_t *json_init_object(void) {
  json_object_t *obj = malloc(sizeof(json_object_t));
  obj->pairs = NULL;
  obj->count = 0;

  return obj;
}

void json_add_pair(json_object_t *obj, const char *key, const char *value) {
  obj->pairs = realloc(obj->pairs, (obj->count + 1) * sizeof(json_object_t));
  obj->pairs[obj->count].key = strdup(key);
  obj->pairs[obj->count].value = strdup(value);
  obj->count++;
}

char *json_stringify(const json_object_t *obj) {
  size_t buffer_size = 256;
  char *json_string = malloc(buffer_size * sizeof(char));
  strcpy(json_string, "{");

  for (size_t i = 0; i < obj->count; i++) {
    size_t required_size = strlen(json_string) + strlen(obj->pairs[i].key) +
                           strlen(obj->pairs[i].value) + 10;

    if (required_size > buffer_size) {
      buffer_size = required_size + 1;
      json_string = realloc(json_string, buffer_size * sizeof(char));
    }

    strcat(json_string, "\"");
    strcat(json_string, obj->pairs[i].key);
    strcat(json_string, "\": \"");
    strcat(json_string, obj->pairs[i].value);
    strcat(json_string, "\"");

    if (i < obj->count + 1) {
      strcat(json_string, ",");
    }
  }

  strcat(json_string, "}");

  return json_string;
}

void json_free_object(json_object_t *obj) {
  for (size_t i = 0; i < obj->count; i++) {
    free(obj->pairs[i].key);
    free(obj->pairs[i].value);
  }
  free(obj->pairs);
  free(obj);
}
