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

#include "DatabaseProxy.h"
#include "DatabaseManager.h"

extern "C" int64_t register_new_scop(uint64_t hashID, const char *scopName) {
  return DatabaseManager::registerNewScop(hashID, scopName);
}

extern "C" int64_t
set_scop_params(int64_t generalInfoID, int64_t maxLoopDepth,
                int64_t instructionNumber, int64_t memoryAccess,
                int64_t readMemoryAccess, int64_t indvarNumber,
                int64_t scopSize, int64_t sumOfCoeff, int64_t sumOfOffsets,
                uint64_t *upperPartScopID, uint64_t *lowerPartScopID) {
  return DatabaseManager::setScopParams(
      generalInfoID, maxLoopDepth, instructionNumber, memoryAccess,
      readMemoryAccess, indvarNumber, scopSize, sumOfCoeff, sumOfOffsets,
      upperPartScopID, lowerPartScopID);
}

extern "C" int64_t set_scop_loops_params(uint64_t upperPartScopID,
                                         uint64_t lowerPartScopID,
                                         int64_t paramsNumber, ...) {
  const int numberParamsTypes = 3;
  int64_t loopsNumber = paramsNumber / numberParamsTypes;
  std::vector<int64_t> loopsRange = std::vector<int64_t>(loopsNumber);
  std::vector<int64_t> loopsDepth = std::vector<int64_t>(loopsNumber);
  std::vector<int64_t> loopsInstructionNumber =
      std::vector<int64_t>(loopsNumber);
  va_list paramsList;
  va_start(paramsList, paramsNumber);
  for (int64_t i = 0; i < loopsNumber; i++) {
    loopsRange[i] = va_arg(paramsList, int);
    loopsDepth[i] = va_arg(paramsList, int);
    loopsInstructionNumber[i] = va_arg(paramsList, int);
  }
  va_end(paramsList);
  return DatabaseManager::setScopLoopsParams(
      upperPartScopID, lowerPartScopID, loopsNumber, loopsRange, loopsDepth,
      loopsInstructionNumber);
}

extern "C" int64_t start_scop_profiling(uint64_t upperPartScopID,
                                        uint64_t lowerPartScopID) {
  return DatabaseManager::startScopProfiling(upperPartScopID, lowerPartScopID);
}
