#include "handlers.h"
#include "json.h"

char *handle_root(void) {
  json_object_t *obj = json_init_object();
  json_add_pair(obj, "Handle", "Root");
  char *json_string = json_stringify(obj);
  json_free_object(obj);

  return json_string;
}

char *handle_create_user(void) {
  json_object_t *obj = json_init_object();
  json_add_pair(obj, "Handle", "Create User");
  char *json_string = json_stringify(obj);
  json_free_object(obj);

  return json_string;
}

char *handle_login_user(void) {
  json_object_t *obj = json_init_object();
  json_add_pair(obj, "Handle", "Login User");
  char *json_string = json_stringify(obj);
  json_free_object(obj);

  return json_string;
}
