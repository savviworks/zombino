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
#include <stdio.h>

#include "../strings.h"
#include "assert.h"

static void testContains() {
    printf("--- %s ---\n", __func__);
    const char *truths[][2] = {
        { "abc", "a" },
        { "abc", "b" },
        { "abc", "c" },
        { "abc", "" },
    };

    const char *lies[][2] = {
        { "abc", "d" },
        { "", "a" },
    };

    for (int i = 0; i < sizeof(truths)/sizeof(truths[0]); i++) {
        const char *str = truths[i][0];
        const char c = truths[i][1][0];
        assert(Strings.contains(str, c));
    }

    for (int i = 0; i < sizeof(lies)/sizeof(lies[0]); i++) {
        const char *str = lies[i][0];
        const char c = lies[i][1][0];
        assert(!Strings.contains(str, c));
    }
}

static void testStartsWith() {
    printf("--- %s ---\n", __func__);
    const char *truths[][2] = {
        { "abc", "a" },
        { "abc", "ab" },
        { "abc", "abc" },
        { "abc", "" },
    };

    const char *lies[][2] = {
        { "abc", "c" },
        { "abc", NULL },
        { "abc", "abcd" },
    };

    for (int i = 0; i < sizeof(truths)/sizeof(truths[0]); i++) {
        const char *str = truths[i][0];
        const char *suffix = truths[i][1];
        assert(Strings.startsWith(str, suffix));
    }

    for (int i = 0; i < sizeof(lies)/sizeof(lies[0]); i++) {
        const char *str = lies[i][0];
        const char *suffix = lies[i][1];
        assert(!Strings.startsWith(str, suffix));
    }
}

static void testCount() {
    printf("--- %s ---\n", __func__);
    struct test_case_s {
        char *str;
        char *match;
        int expected;
    } test_cases[] = {
        /* { src, match, expect } */
        { "happy old year",     "old",  1 },
        { "a xx a xx a",        "xx",   2 },
        { "xx a xx",            "xx",   2 },
        { "a xx a xx",          "xx",   2 },
        { "abcde",              "xx",   0 },
    };

    for (int i = 0; i < sizeof(test_cases)/sizeof(test_cases[0]); i++) {
        struct test_case_s test_case = test_cases[i]; 
        unsigned int actual = Strings.count(test_case.str, test_case.match);
        assert(test_case.expected == actual);
    }
}

static void testReplace() {
    printf("--- %s ---\n", __func__);
    char *test_cases[][4] = {
        /* { src, match, replace, expect } */
        { "happy old year",     "old",  "new",  "happy new year" }, // Single mid same-length replacement
        { "a xx a xx a",        "xx",   "b",    "a b a b a" },      // Multi mid shorter replacement
        { "xx a xx",            "xx",   "bbb",  "bbb a bbb" },      // Multi boundary longer replacement
        { "a xx a xx",          "xx",   NULL,   "a  a " },          // Multi-removal including end
        { "abcde",              "xx",   "yy",   "abcde" },          // No match
    };

    for (int i = 0; i < sizeof(test_cases)/sizeof(test_cases[0]); i++) {
        char **test_case = test_cases[i]; 
        char *str = *test_case++;
        char *match = *test_case++;
        char *replacement = *test_case++;
        char *expected = *test_case++;

        char *actual = Strings.replace(str, match, replacement);
        assert(!strcmp(actual, expected));
        free(actual); // Note that passing NULL to free() is a NOP so no need to check 
    }
}

static void testConcat() {
    printf("--- %s ---\n", __func__);
    const char *testCases[][3] = {
        { "a", "bc", "abc" },
        { "", "ab", "ab" },
        { "a", "", "a" }
    };

    for (int i = 0; i < sizeof(testCases)/sizeof(testCases[0]); i++) {
        const char *str1 = testCases[i][0];
        const char *str2 = testCases[i][1];
        const char *expected = testCases[i][2];

        char *actual = Strings.concat(str1, str2);
        assert(!strcmp(expected, actual));
        actual = Strings.destroy(actual);
    }
}

static void testFromInt() {
    printf("--- %s ---\n", __func__);
    const struct test_case_s {
        int i;
        char *s;
    } testCases[] = {
        { .i = 123, .s = "123" },
        { .i = -321, .s = "-321" }
    };

    for (int i = 0; i < sizeof(testCases)/sizeof(testCases[0]); i++) {
        struct test_case_s testCase = testCases[i];
        char *expected = testCase.s;
        char *actual = Strings.fromInt(testCase.i);
        assert(!strcmp(actual, expected));
        actual = Strings.destroy(actual);
    }
}

void testSplitTokens() {
    printf("--- %s ---\n", __func__);
    struct test_case_s {
        const char *text;
        int tokenCount;
        int tokenCountStrict;
    } testCases[] = {
        { " hello ", 1, 3 },
        { "hello", 1, 1 },
        { " hello", 1, 2 },
        { "  hello  ", 1, 5 },
        { "hello world", 2, 2 },
        { "hello  world", 2, 3 },
        { " hello world", 2, 3 },
        { "  hello world", 2, 4 },
        { "hello world ", 2, 3 },
        { "hello world  ", 2, 4 },
    };
    
    const int maxTokenCount = 10;
    char *tokens[maxTokenCount];

    int testCaseCount = sizeof(testCases)/sizeof(testCases[0]);
    for (int i = 0; i < testCaseCount; i++) {
        struct test_case_s testCase = testCases[i];
        char *text = strdup(testCases[i].text);
        int tokenCount = Strings.splitTokens (text, tokens, maxTokenCount, ' ');
        printf ("Tokens: %d\t", tokenCount);
        for (int i = 0; i < tokenCount; i++) {
            printf ("%s%s", tokens[i], (i < tokenCount -1) ? "|" : "\n");
        }

        assert(tokenCount == testCase.tokenCount);
    }
}

void testTrimEnd() {
    char * testCases[][2] = {
        { "a", "a" },
        { "a ", "a" },
        { "a  ", "a" },
        { "  ", "" }
    };

    for (int i = 0; i < sizeof(testCases)/sizeof(testCases[0]); i++) {
        char *actual = strdup(testCases[i][0]);
        Strings.trimEnd(actual);
        char *expected = testCases[i][1];
        assert(!strcmp(actual, expected));
        free(actual);
    }
}

void testStrings() {
    testTrimEnd();
    testSplitTokens();
    testContains();
    testStartsWith();
    testCount();
    testConcat();
    testFromInt();
    testReplace();
}
