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

// Test application

int main() {
  int64_t res = register_new_scop(0xFF, "test4");
  uint64_t a, b;
  set_scop_params(res, 1, 2, 3, 4, 5, 8, 6, 7, &a, &b);
  set_scop_loops_params(a, b, 6, 1, 2, 3, 4, 5, 6);
  return 0;
}
