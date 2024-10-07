#ifndef MIGRATIONS_H
#define MIGRATIONS_H

#include <sqlite3.h>

int run_migration(sqlite3 *db, const char *sql_file);

#endif // !MIGRATIONS_H
