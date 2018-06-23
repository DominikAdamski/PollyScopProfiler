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

#include "DatabaseManager.h"
#include "DatabaseMutex.h"
#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <string.h>
#include <string>

using namespace std;

struct RecordDescription {
  int64_t rowID;
  bool found;
  RecordDescription() : rowID{0}, found{false} {};
};

static int callback(void *id, int argc, char **argv, char **azColName) {
  RecordDescription *c = (RecordDescription *)id;
  c->rowID = atoi(argv[0]);
  c->found = true;
  return 0;
}

int64_t DatabaseManager::registerNewScop(uint64_t hashID, const char *name) {
  DatabaseHandler Handler(DatabaseFileName);
  int rc;
  stringstream ss;
  RecordDescription foundRecord;
  ss << "SELECT id FROM general_info WHERE hash=" << hashID << " AND name = '"
     << name << "';";
  string sqlCommandCount = ss.str();
  ss.str("");
  DatabaseMutex dbMutex(Handler.GetDatabasePtr());
  dbMutex.Lock();
  rc = sqlite3_exec(Handler.GetDatabasePtr(), sqlCommandCount.c_str(),
                    &callback, &foundRecord, nullptr);
  if (rc)
    return -1;

  if (!foundRecord.found) {
    ss << "INSERT INTO general_info(hash, name) VALUES ('" << hashID << "','"
       << name << "');" << endl;
    ss << "SELECT id FROM general_info WHERE hash=" << hashID << " AND name = '"
       << name << "';";
    string sqlCommandInsert = ss.str();
    rc = sqlite3_exec(Handler.GetDatabasePtr(), sqlCommandInsert.c_str(),
                      &callback, &foundRecord, nullptr);
    ss.str("");
  }
  if (rc)
    return -1;

  return foundRecord.rowID;
}

int64_t DatabaseManager::setScopParams(
    int64_t generalInfoID, int64_t maxLoopDepth, int64_t instructionNumber,
    int64_t memoryAccess, int64_t readMemoryAccess, int64_t indvarNumber,
    int64_t sumOfCoeff, int64_t scopSize, int64_t sumOfOffsets,
    uint64_t *upperPartScopID, uint64_t *lowerPartScopID) {
  DatabaseHandler Handler(DatabaseFileName);
  int rc;
  unsigned char uuid[16];
  for (int i = 0; i < 16; ++i) {
    uuid[i] = (unsigned char)(rand() % 256);
  }
  uuid[7] = (uuid[6] & 0x0F) | 0x40;
  uuid[8] = (uuid[8] & 0x3F) | 0x80;
  stringstream ss;

  RecordDescription foundRecord;
  sqlite3_stmt *pStmt;
  ss << "INSERT INTO scop_info(scop_id, general_info_id, max_loop_depth, "
        "instruction_number, memory_access, read_memory_access, indvar_number, "
        "scop_size, "
        "sum_of_array_coeff, sum_of_array_offset) VALUES "
        "(? , '"
     << generalInfoID << "','" << maxLoopDepth << "','" << instructionNumber
     << "','" << memoryAccess << "','" << readMemoryAccess << "','"
     << indvarNumber << "','" << scopSize << "','" << sumOfCoeff << "','"
     << sumOfOffsets << "');" << endl;
  string sqlCommand = ss.str();
  cout << sqlCommand;
  rc = sqlite3_prepare(Handler.GetDatabasePtr(), sqlCommand.c_str(), -1, &pStmt,
                       0);
  if (rc) {
    return -1;
  }
  rc = sqlite3_bind_blob(pStmt, 1, uuid, sizeof(char) * 16, SQLITE_STATIC);
  if (rc) {
    return -1;
  }
  rc = sqlite3_step(pStmt);
  if (rc && rc != SQLITE_DONE) {
    return -1;
  }
  sqlite3_finalize(pStmt);
  memcpy(lowerPartScopID, &uuid[0], 8);
  memcpy(upperPartScopID, &uuid[8], 8);
  return 1;
}

int64_t DatabaseManager::setScopLoopParams(uint64_t upperPartScopID,
                                           uint64_t lowerPartScopID,
                                           int64_t range) {
  DatabaseHandler Handler(DatabaseFileName);

  unsigned char uuid[16];
  int rc;
  stringstream ss;
  RecordDescription foundRecord;
  DatabaseMutex dbMutex(Handler.GetDatabasePtr());

  memcpy(&uuid[0], &lowerPartScopID, 8);
  memcpy(&uuid[8], &upperPartScopID, 8);

  ss << "INSERT INTO loops(scop_id, range) VALUES (? ,'" << range << "');"
     << endl;
  string sqlCommand = ss.str();
  sqlite3_stmt *pStmt;
  rc = sqlite3_prepare(Handler.GetDatabasePtr(), sqlCommand.c_str(), -1, &pStmt,
                       0);
  if (rc) {
    return -1;
  }
  rc = sqlite3_bind_blob(pStmt, 1, uuid, sizeof(char) * 16, SQLITE_STATIC);
  if (rc) {
    return -1;
  }
  rc = sqlite3_step(pStmt);
  if (rc && rc != SQLITE_DONE) {
    return -1;
  }
  sqlite3_finalize(pStmt);

  return 1;
}
