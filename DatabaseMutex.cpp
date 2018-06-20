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

#include "DatabaseMutex.h"
#include <memory>
#include <sqlite3.h>
#include <stdexcept>

using namespace std;

void releaseMutex(sqlite3_mutex *mutex) {
  if (!mutex)
    sqlite3_mutex_leave(mutex);
}

DatabaseMutex::DatabaseMutex(sqlite3 *db)
    : MutexPtr(sqlite3_db_mutex(db), &releaseMutex) {}

void DatabaseMutex::Lock() { sqlite3_mutex_enter(MutexPtr.get()); }
