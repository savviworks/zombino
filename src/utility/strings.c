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
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>

#include "strings.h"

static char *strings_destroy(char *str) {
    if (str != NULL) {
        *str = '\000';
        free(str);
    }

    return NULL;
}

static unsigned char strings_startsWith(const char *str, const char *prefix) {
    if (str == NULL || prefix == NULL) {
        return 0;
    } else {
        return strncmp(str, prefix, strlen(prefix)) == 0;
    }
}

static unsigned int strings_count(const char * str, const char * match) {
    if (str == NULL || match == NULL) {
        return 0;
    }

    int match_len = strlen(match);
    const char *src_p = str;
    int matches = 0;
    while(src_p = strstr(src_p, match)) {
        matches++;
        src_p += match_len;
    }

    return matches;
}

static char *strings_replace(const char * src, const char * match, const char * replacement) {
    if (NULL == src || NULL == match) {
        return  NULL;
    }

    // Get all the lenths
    int src_len = strlen(src);
    int match_len = strlen(match);
    int replacement_len = (replacement) ? strlen(replacement) : 0;

    // Count matches first
    const char *src_p = src;
    unsigned int matches = strings_count(src, match);

    // Allocate memory
    char *result = calloc(1 + src_len + matches * (replacement_len - match_len), sizeof(char));
    
    // Traverse again, this time copying the strings into the result
    char *result_p = result;
    const char *src_prev_p = src_p = src;
    int d = 0;
    while(src_p = strstr(src_p, match)) {
        if (src_p > src_prev_p) {
            d = src_p - src_prev_p;
            strncpy(result_p, src_prev_p, d);
            result_p += d;
        }

        if (replacement) {
            strncpy(result_p, replacement, replacement_len);
            result_p += replacement_len;
        }

        src_prev_p = src_p + match_len;
        src_p += match_len;
    }

    d = src + src_len - src_prev_p;
    strncpy(result_p, src_prev_p, d);
    result_p[d] = '\000';
    return result;
}

static char *strings_fromInt(int i) {
    const unsigned int chars = (int)((ceil(log10(i))+1));
    char *str = calloc(chars, sizeof(char));
    sprintf(str, "%d", i);
    return str;
}

static char *strings_concat(const char *str1, const char *str2) {
    const int len1 = strlen(str1);
    const int len2 = strlen(str2);
    char *newStr = calloc(len1 + len2 + 1, sizeof(char));
    strcpy(newStr, str1);
    strcpy(&newStr[len1], str2);
    newStr[len1 + len2] = '\000';
    return newStr;
}

static unsigned char strings_contains(const char *str, const char c) {
    return !!strchr(str, c);   
}

/**
 * Splits the specified text into tokens based on the specified delimiter.
 **/
static int strings_splitTokens(char text[], char *tokens[], int tokenMax, char delim) {
  int ti = 0;      // Token index
  for (char *found = text; found != NULL && *found != '\0'; found++) {
    // Skip consecutive delimiters
    if (*found == delim) {
      continue;
    }

    tokens[ti++] = found;
    found = strchr (found, delim);
    if (NULL != found) {
      *found = '\0';
    } else {
      break;
    }
  }

  if (ti < tokenMax) tokens[ti] = NULL; // Sentinel at end of filled token slots
  return ti;
}

static void strings_trimEnd(char * text) {
  int len = strlen(text);
  for (int i = (len - 1); i >= 0; i--) {
    if (isspace(text[i])) {
      text[i] = '\0'; // Replace the whitespace char with string terminator
    } else {
      break; // Non-space char, so exit the triming function
    }
  }
}

struct strings_s Strings = {
    .fromInt = strings_fromInt,
    .concat = strings_concat,
    .destroy = strings_destroy,
    .replace = strings_replace,
    .count = strings_count,
    .startsWith = strings_startsWith,
    .contains = strings_contains,
    .splitTokens = strings_splitTokens,
    .trimEnd = strings_trimEnd
};
