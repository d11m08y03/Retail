#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>

char *load_sql_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    fprintf(stderr, "Cannot open file: %s\n", filename);
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long length = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *sql = malloc(length + 1);
  if (sql) {
    fread(sql, 1, length, file);
    sql[length] = '\0';
  }

  fclose(file);
  return sql;
}

int run_migration(sqlite3 *db, const char *sql_file) {
  char *err_msg = 0;
  char *sql = load_sql_file(sql_file);

  if (!sql) {
    return 1;
  }

  int rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
    free(sql);
    return rc;
  }

  free(sql);
  return SQLITE_OK;
}

int main(void) {
  sqlite3 *db;
  int rc = sqlite3_open("test.db", &db);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    return 1;
  }

  // List of migration files to run
  const char *migration_files[] = {
      "./migrations/001_create_users.sql",
      "./migrations/002_create_products.sql",
      "./migrations/003_create_orders_table.sql",
      "./migrations/004_create_order_items_table.sql",
      "./migrations/005_populate_users.sql",
      "./migrations/006_populate_products.sql",
      "./migrations/007_populate_orders.sql",
      "./migrations/008_populate_order_items.sql"};

  // Run each migration file
  for (size_t i = 0; i < sizeof(migration_files) / sizeof(migration_files[0]);
       i++) {
    rc = run_migration(db, migration_files[i]);
    if (rc != SQLITE_OK) {
      fprintf(stderr, "Migration %02zu failed.\n", i + 1);
      sqlite3_close(db);
      return 1;
    }
    printf("Migration %02zu ran successfully.\n", i + 1);
  }

  sqlite3_close(db);
  return 0;
}
