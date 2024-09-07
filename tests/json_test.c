#include "criterion/criterion.h"
#include "criterion/internal/assert.h"
#include "criterion/internal/test.h"
#include "criterion/logging.h"
#include <stdio.h>

#include "../src/json.h"

Test(json_init_object, basic) {
  json_object_t *obj = json_init_object();
  cr_assert_neq(obj, NULL);
  json_free_object(obj);
}

Test(json_add_pair, basic) {
  json_object_t *obj = json_init_object();

  json_add_pair(obj, "hello", "world");

  char *json_string = json_stringify(obj);
  printf("%s\n", json_string);
  cr_assert_eq(json_string, "{\"hello\": \"world\"}");

  json_free_object(obj);
}
