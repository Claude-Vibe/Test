#ifndef UNIT_TEST_H
#define UNIT_TEST_H

/* Minimal assert-based test framework (no external dependency). */
#include <stdio.h>

extern int ut_failed;
extern int ut_run;

#define UT_ASSERT(cond)                                                   \
    do {                                                                  \
        if (!(cond)) {                                                    \
            printf("  FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond);      \
            ut_failed++;                                                  \
            return;                                                       \
        }                                                                 \
    } while (0)

#define UT_ASSERT_EQ(exp, act) UT_ASSERT((exp) == (act))

#define UT_RUN(test)                                                      \
    do {                                                                  \
        int before = ut_failed;                                           \
        ut_run++;                                                         \
        test();                                                           \
        printf("[%s] %s\n", (ut_failed == before) ? " OK " : "FAIL", #test); \
    } while (0)

#endif /* UNIT_TEST_H */
