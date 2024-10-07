#include "handlers.h"
#include "json.h"

char *handle_root(const char *body) {
  char *json_string = json_from_body(body);

  return json_string;
}

char *handle_create_user(const char *body) {
  char *json_string = json_from_body(body);

  return json_string;
}

char *handle_login_user(const char *body) {
  char *json_string = json_from_body(body);

  return json_string;
}

char *handle_create_product(const char *body) {
  char *json_string = json_from_body(body);

  return "";
}
