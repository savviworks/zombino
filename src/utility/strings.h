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
#ifndef UTIL_STRING_H
#define UTIL_STRING_H

#ifdef __cplusplus
extern "C"{
#endif

struct strings_s {
    char *(* fromInt)(int);
    char *(* concat)(const char *str1, const char *str2);
    char *(* destroy)(char *str);
    char *(* replace)(const char * src, const char * match, const char * replacement);
    unsigned int (* count)(const char * str, const char * match);
    unsigned char (* startsWith)(const char *str, const char *prefix);
    unsigned char (* contains)(const char *str, const char c);
    int (* splitTokens)(char text[], char *tokens[], int tokenMax, char delim);
    void (*trimEnd)(char * text);
};

extern struct strings_s Strings;

#ifdef __cplusplus
} // extern "C"
#endif

#endif
