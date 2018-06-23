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

#ifndef DATABASE_PROXY_H
#define DATABASE_PROXY_H
#include <cstdint>
extern "C" int64_t register_new_scop(uint64_t hashID, const char *name);
extern "C" int64_t
set_scop_params(int64_t generalInfoID, int64_t maxLoopDepth,
                int64_t instructionNumber, int64_t memoryAccess,
                int64_t readMemoryAccess, int64_t indvarNumber,
                int64_t scopSize, int64_t sumOfCoeff, int64_t sumOfOffsets,
                uint64_t *upperPartScopID, uint64_t *lowerPartScopID);
extern "C" int64_t set_scop_loop_params(uint64_t upperPartScopID,
                                        uint64_t lowerPartScopID,
                                        int64_t range);
#endif
