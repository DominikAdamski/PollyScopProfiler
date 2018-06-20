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

#ifndef DATABASE_MUTEX_H
#define DATABASE_MUTEX_H

#include <memory>
#include <sqlite3.h>

class DatabaseMutex {
  std::unique_ptr<sqlite3_mutex, void (*)(sqlite3_mutex *)> MutexPtr;

public:
  DatabaseMutex(sqlite3 *db);
  void Lock();
};
#endif
