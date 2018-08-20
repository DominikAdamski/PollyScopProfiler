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

#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H
#include "DatabaseHandler.h"
#include <string>
#include <vector>
class DatabaseManager {
  static constexpr const char *DatabaseFileName = "scops.db";
  static int bindSqlStmtWithScopID(const std::string &sqlCommand,
                                   DatabaseHandler &handler,
                                   unsigned char (&uuid)[16]);

public:
  static int64_t registerNewScop(uint64_t hashID, const char *name);
  static int64_t setScopParams(int64_t generalInfoID, int64_t maxLoopDepth,
                               int64_t instructionNumber, int64_t memoryAccess,
                               int64_t readMemoryAccess, int64_t indvarNumber,
                               int64_t sumOfCoeff, int64_t sumOfOffsets,
                               int64_t scopSize, uint64_t *upperPartScopID,
                               uint64_t *lowerPartScopID);
  static int64_t
  setScopLoopsParams(uint64_t upperPartScopID, uint64_t lowerPartScopID,
                     int64_t loopsNumber, std::vector<int64_t> &loopsRange,
                     std::vector<int64_t> &loopsDepth,
                     std::vector<int64_t> &loopsInstructionNumber);
};
#endif
