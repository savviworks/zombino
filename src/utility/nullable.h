/*
  Copyright (c) Martin Sawicki. All right reserved.

  This file is part of the Zombino project.

  Zombino is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Zombino is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Zombino.  If not, see <https://www.gnu.org/licenses/>.
*/
// To be as fields in structs only!
#define NULL_BIT(b) 1<<(b)
#define NULLABLE(b, i) unsigned int i : ((b)+1)
#define IS_NULLABLE(b, i) ((i) <= 1<<(b))

#define NULL_8 NULL_BIT(8)
#define IS_NULLABLE_8(i) IS_NULLABLE(8, i)

#define NULL_15 1<<15
#define IS_NULLABLE_15(i) ((i) <= 1<<15)
