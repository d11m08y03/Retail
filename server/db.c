#include <stdio.h>

#include "db.h"

static sqlite3 *db;

int db_init(void) {
  int rc = sqlite3_open("test.db", &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return -1;
  } else {
    printf("Opened database successfully.\n");
  }

  return 0;
}

int db_create_user(
    const char *username,
    const char *email,
    const char *password) {
  const char *sql =
      "INSERT INTO Users (username, email, password) VALUES (?, ?, ?);";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    return -1;
  }

  // TODO: Password hashing
  sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, email, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 3, password, -1, SQLITE_STATIC);

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
  }

  sqlite3_finalize(stmt);
  return (rc == SQLITE_DONE) ? 0 : -1;
}

int db_create_product(
    const char *name,
    const char *description,
    double price,
    int quantity) {
  const char *sql = "INSERT INTO products (name, description, price, "
                    "stock_quantity) VALUES (?, ?, ?, ?);";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    return -1;
  }

  sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
  sqlite3_bind_text(stmt, 2, description, -1, SQLITE_STATIC);
  sqlite3_bind_double(stmt, 3, price);
  sqlite3_bind_int(stmt, 4, quantity);

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
  }

  sqlite3_finalize(stmt);
  return (rc == SQLITE_DONE) ? 0 : -1;
}

int db_create_order(int user_id, double total_amount) {
  const char *sql = "INSERT INTO orders (user_id, total_amount, created_at) "
                    "VALUES (?, ?, CURRENT_TIMESTAMP);";
  sqlite3_stmt *stmt;
  int order_id = -1; // To store the new order ID

  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    return -1;
  }

  sqlite3_bind_int(stmt, 1, user_id);
  sqlite3_bind_double(stmt, 2, total_amount);

  rc = sqlite3_step(stmt);
  if (rc == SQLITE_DONE) {
    order_id = (int)sqlite3_last_insert_rowid(db);
    printf("Order created successfully with ID: %d\n", order_id);
  } else {
    fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
    return -1;
  }

  sqlite3_finalize(stmt);
  return order_id;
}

int db_create_order_item(
    int order_id,
    int product_id,
    int quantity,
    double price) {
  const char *sql = "INSERT INTO order_items (order_id, product_id, quantity, "
                    "price) VALUES (?, ?, ?, ?);";
  sqlite3_stmt *stmt;

  int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
    return -1;
  }

  sqlite3_bind_int(stmt, 1, order_id);
  sqlite3_bind_int(stmt, 2, product_id);
  sqlite3_bind_int(stmt, 3, quantity);
  sqlite3_bind_double(stmt, 4, price);

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
  }

  sqlite3_finalize(stmt);
  return (rc == SQLITE_DONE) ? 0 : -1;
}

void db_destroy() { sqlite3_close(db); }
