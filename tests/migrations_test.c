#include "../external/criterion-2.4.2/include/criterion/criterion.h"
#include "../migrations/migrations.h"
#include <sqlite3.h>
#include <stdio.h>

sqlite3 *create_test_db() {
  sqlite3 *db;
  int rc = sqlite3_open("./tests/test.db", &db);

  if (rc != SQLITE_OK) {
    cr_assert_fail("Cannot open database");
  }
  return db;
}

// Test case for migrations
Test(migrations, run_migrations) {
  sqlite3 *db = create_test_db();
  int rc;

  // Run all migrations
  const char *migration_files[] = {
      "./migrations/001_create_users.sql",
      "./migrations/002_create_products.sql",
      "./migrations/003_create_orders_table.sql",
      "./migrations/004_create_order_items_table.sql",
      "./migrations/005_populate_users.sql",
      "./migrations/006_populate_products.sql",
      "./migrations/007_populate_orders.sql",
      "./migrations/008_populate_order_items.sql"};

  for (size_t i = 0; i < sizeof(migration_files) / sizeof(migration_files[0]);
       ++i) {
    rc = run_migration(db, migration_files[i]);
    cr_assert_eq(
        rc,
        SQLITE_OK,
        "Migration %s failed with error code: %d",
        migration_files[i],
        rc);
  }

  sqlite3_close(db);
}

// Test to ensure the tables exist
Test(migrations, check_tables_exist) {
  sqlite3 *db = create_test_db();
  char *err_msg = 0;

  const char *check_users =
      "SELECT name FROM sqlite_master WHERE type='table' AND name='users';";
  int rc = sqlite3_exec(db, check_users, NULL, NULL, &err_msg);
  cr_assert_eq(rc, SQLITE_OK, "Error checking users table: %s", err_msg);

  const char *check_products =
      "SELECT name FROM sqlite_master WHERE type='table' AND name='products';";
  rc = sqlite3_exec(db, check_products, NULL, NULL, &err_msg);
  cr_assert_eq(rc, SQLITE_OK, "Error checking products table: %s", err_msg);

  const char *check_orders =
      "SELECT name FROM sqlite_master WHERE type='table' AND name='orders';";
  rc = sqlite3_exec(db, check_orders, NULL, NULL, &err_msg);
  cr_assert_eq(rc, SQLITE_OK, "Error checking orders table: %s", err_msg);

  const char *check_order_items = "SELECT name FROM sqlite_master WHERE "
                                  "type='table' AND name='order_items';";
  rc = sqlite3_exec(db, check_order_items, NULL, NULL, &err_msg);
  cr_assert_eq(rc, SQLITE_OK, "Error checking order_items table: %s", err_msg);

  sqlite3_free(err_msg);
  sqlite3_close(db);
}
