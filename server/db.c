#include <stdio.h>

#include "db.h"

int db_init(void) {
  int rc = sqlite3_open("test.db", &db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open databse: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return -1;
  } else {
    printf("Opened databse successfully.\n");
  }

  return 0;
}

void db_destroy() {
  sqlite3_close(db);
}


