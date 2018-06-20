/**********************************************************************
 * Polly Scop Profiler Runtime
 * Copyright (C) 2018  Dominik Adamski
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************/

#include "DatabaseHandler.h"
#include <memory>
#include <sqlite3.h>
#include <stdexcept>
using namespace std;
void closeDatabase(sqlite3 *db) { sqlite3_close(db); }
DatabaseHandler::DatabaseHandler(const char *DatabaseFile)
    : DatabasePtr(nullptr, &closeDatabase) {
  sqlite3 *databasePtr;
  int rc;
  rc = sqlite3_open(DatabaseFile, &databasePtr);
  if (rc)
    throw runtime_error("Cannot open database");
  DatabasePtr =
      unique_ptr<sqlite3, void (*)(sqlite3 *)>(databasePtr, &closeDatabase);
};

DatabaseHandler::~DatabaseHandler(){};
sqlite3 *DatabaseHandler::GetDatabasePtr() { return DatabasePtr.get(); }

int DatabaseHandler::exec(const char *command) {
  return 1; // sqlite3_exec(database);
}
