#include <ctype.h>
#include <stdio.h>
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
      buffer_size = required_size;
      json_string = realloc(json_string, buffer_size * sizeof(char));
    }

    strcat(json_string, "\"");
    strcat(json_string, obj->pairs[i].key);
    strcat(json_string, "\": \"");
    strcat(json_string, obj->pairs[i].value);
    strcat(json_string, "\"");

    if (i < obj->count - 1) {
      strcat(json_string, ", ");
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

char *json_from_body(const char *buffer) {
  char *body_start = strstr(buffer, "\r\n\r\n");
  char *json_content = NULL;

  if (body_start) {
    // Move past \r\n\r\n
    body_start += 4;
    json_content = body_start;
  }

  return json_content;
}

static char *trim_whitespace(char *str) {
  char *end;

  while (isspace((unsigned char)*str))
    str++;

  if (*str == 0)
    return str;

  end = str + strlen(str) - 1;
  while (end > str && isspace((unsigned char)*end))
    end--;

  *(end + 1) = '\0';

  return str;
}

json_object_t *json_from_string(const char *json_string) {
  if (json_string == NULL || *json_string != '{')
    return NULL;

  json_object_t *obj = malloc(sizeof(json_object_t));
  if (!obj)
    return NULL;
  obj->count = 0;
  obj->pairs = NULL;

  char *json_copy = strdup(json_string);
  if (!json_copy) {
    free(obj);
    return NULL;
  }

  json_copy++;
  char *end = strchr(json_copy, '}');
  if (!end) {
    free(json_copy - 1);
    free(obj);
    return NULL;
  }
  *end = '\0';

  char *token = strtok(json_copy, ",");
  while (token != NULL) {
    char *colon = strchr(token, ':');
    if (!colon) {
      free(json_copy - 1);
      free(obj->pairs);
      free(obj);
      return NULL;
    }

    *colon = '\0';
    char *key = trim_whitespace(token);
    char *value = trim_whitespace(colon + 1);

    if (*key == '"' && key[strlen(key) - 1] == '"') {
      key++;
      key[strlen(key) - 1] = '\0';
    }

    if (*value == '"' && value[strlen(value) - 1] == '"') {
      value++;
      value[strlen(value) - 1] = '\0';
    }

    json_pair_t *new_pairs =
        realloc(obj->pairs, (obj->count + 1) * sizeof(json_pair_t));
    if (!new_pairs) {
      free(json_copy - 1);
      free(obj->pairs);
      free(obj);
      return NULL;
    }
    obj->pairs = new_pairs;

    obj->pairs[obj->count].key = strdup(key);
    obj->pairs[obj->count].value = strdup(value);
    if (!obj->pairs[obj->count].key || !obj->pairs[obj->count].value) {
      free(json_copy - 1);
      free(obj->pairs);
      free(obj);
      return NULL;
    }

    obj->count++;
    token = strtok(NULL, ",");
  }

  free(json_copy - 1);
  return obj;
}

void json_print_object(const json_object_t *obj) {
  printf("\n");
  printf("{\n");
  for (size_t i = 0; i < obj->count; i++) {
    json_pair_t pair = obj->pairs[i];
    printf("  \"%s\": \"%s\"", pair.key, pair.value);

    if (i < obj->count - 1) {
      printf(",");
    }
    printf("\n");
  }
  printf("}\n");
  printf("\n");
}

char *json_get_value_by_key(const json_object_t *obj, const char *key) {
  for (size_t i = 0; i < obj->count; i++) {
    if (strcmp(obj->pairs[i].key, key) == 0) {
      return obj->pairs[i].value;
    }
  }
  return NULL;
}
