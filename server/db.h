#ifndef DB_H
#define DB_H

#include <sqlite3.h>

static sqlite3 *db;

int db_init(void);
void db_destroy();

#endif // !DB_H
