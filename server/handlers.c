#include <stdio.h>

#include "db.h"
#include "handlers.h"
#include "json.h"

char *handle_create_user(const char *body) {
  char *json_string = json_from_body(body);
  json_object_t *obj = json_from_string(json_string);

  json_print_object(obj);

  char *username = json_get_value_by_key(obj, "username");
  char *email = json_get_value_by_key(obj, "email");
  char *password = json_get_value_by_key(obj, "password");

  if (db_create_user(username, email, password) < 0) {
    printf("\n[LOG | %s | %s] Error creating new user.\n", __func__, __FILE__);
  }

  return json_string;
}

char *handle_create_product(const char *body) {
  char *json_string = json_from_body(body);
  json_object_t *obj = json_from_string(json_string);

  char *name = json_get_value_by_key(obj, "name");
  char *description = json_get_value_by_key(obj, "description");
  char *price_str = json_get_value_by_key(obj, "price");
  char *stock_quantity_str = json_get_value_by_key(obj, "stock_quantity");

  json_print_object(obj);

  char *end_ptr_price;
  char *end_ptr_quantity;

  double price = strtod(price_str, &end_ptr_price);
  int stock_quantity = strtol(stock_quantity_str, &end_ptr_quantity, 10);

  if (*end_ptr_price != '\0') {
    printf("\n[LOG | %s | %s] Error converting price .\n", __func__, __FILE__);
  }

  if (*end_ptr_quantity != '\0') {
    printf(
        "\n[LOG | %s | %s] Error converting stock_quantity.\n",
        __func__,
        __FILE__);
  }

  if (db_create_product(name, description, price, stock_quantity) < 0) {
    printf(
        "\n[LOG | %s | %s] Error creating new product.\n", __func__, __FILE__);
  }

  return json_string;
}
