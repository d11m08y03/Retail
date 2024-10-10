#ifndef DB_H
#define DB_H

#include <sqlite3.h>

int db_init(void);
void db_destroy();
int db_create_user(
    const char *username,
    const char *email,
    const char *password);
int db_create_product(
    const char *name,
    const char *description,
    double price,
    int quantity);
int db_create_order(int user_id, double total_amount);
int db_create_order_item(
    int order_id,
    int product_id,
    int quantity,
    double price);

#endif // !DB_H
