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

  const char *sql_file_01 = "./001_create_users.sql";
  rc = run_migration(db, sql_file_01);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Migration 01 failed.\n");
    sqlite3_close(db);
    return 1;
  }

  printf("Migration ran 01 successfully.\n");

  const char *sql_file_02 = "./002_create_products.sql";
  rc = run_migration(db, sql_file_02);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Migration 02 failed\n");
    sqlite3_close(db);
    return 1;
  }

  printf("Migration ran 02 successfully\n");

  const char *sql_file_03 = "./001_create_users.sql";
  rc = run_migration(db, sql_file_03);

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Migration 03 failed.\n");
    sqlite3_close(db);
    return 1;
  }

  printf("Migration ran 03 successfully.\n");

  sqlite3_close(db);
  return 0;
}
