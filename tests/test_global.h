#ifndef TEST_GLOBAL_H
#define TEST_GLOBAL_H

#define BEGIN_TEST_CASE g_print("\n");
#define END_TEST_CASE//   g_print("\n");

#define TEST_CMPINT(n1, cmp, n2) \
    g_print("\tRunning: %s %s %s\n", #n1, #cmp, #n2); \
    g_assert_cmpint(n1, cmp, n2);

#define TEST_CMPUINT(n1, cmp, n2) \
    g_print("\tRunning: %s %s %s\n", #n1, #cmp, #n2); \
    g_assert_cmpuint(n1, cmp, n2);

#define TEST_CMPHEX(n1, cmp, n2) \
    g_print("\tRunning: %s %s %s\n", #n1, #cmp, #n2); \
    g_assert_cmphex(n1, cmp, n2);

#define TEST_CMPFLOAT(n1, cmp, n2) \
    g_print("\tRunning: %s %s %s\n", #n1, #cmp, #n2); \
    g_assert_cmpfloat(n1, cmp, n2);

#define TEST_IS_NULL(n1) \
    g_print("\tRunning: %s == NULL\n", #n1); \
    g_assert_cmpint(n1, ==, 0);

#define TEST_IS_NOT_NULL(n1) \
    g_print("\tRunning: %s != NULL\n", #n1); \
    g_assert_cmpint(n1, !=, 0);

#define TEST_CMPINT_M(m, n1, cmp, n2) \
    g_print("\tRunning: %s\n", #m); \
    g_assert_cmpint(n1, cmp, n2);

#define TEST_CMPUINT_M(m, n1, cmp, n2) \
    g_print("\tRunning: %s\n", #m); \
    g_assert_cmpuint(n1, cmp, n2);

#define TEST_CMPHEX_M(m, n1, cmp, n2) \
    g_print("\tRunning: %s\n", #m); \
    g_assert_cmphex(n1, cmp, n2);

#define TEST_CMPFLOAT_M(m, n1, cmp, n2) \
    g_print("\tRunning: %s\n", #m); \
    g_assert_cmpfloat(n1, cmp, n2);

#endif // TEST_GLOBAL_H
