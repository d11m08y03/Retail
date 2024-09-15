#include "db.h"
#include "server.h"

int main(void) {
  if (db_init() < 0) {
    return -1;
  }

  server_start();
  db_destroy();

  return 0;
}
