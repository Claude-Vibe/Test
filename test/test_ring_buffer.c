#include "ring_buffer.h"
#include "unit_test.h"

int ut_failed = 0;
int ut_run    = 0;

#define CAP 4

static uint8_t       storage[CAP];
static ring_buffer_t rb;

static void setup(void)
{
    rb_init(&rb, storage, CAP);
}

static void test_init_rejects_invalid_args(void)
{
    UT_ASSERT(!rb_init(NULL, storage, CAP));
    UT_ASSERT(!rb_init(&rb, NULL, CAP));
    UT_ASSERT(!rb_init(&rb, storage, 0));
}

static void test_new_buffer_is_empty(void)
{
    setup();
    UT_ASSERT(rb_is_empty(&rb));
    UT_ASSERT(!rb_is_full(&rb));
    UT_ASSERT_EQ(0u, rb_count(&rb));
}

static void test_push_pop_fifo_order(void)
{
    uint8_t v;
    setup();
    UT_ASSERT(rb_push(&rb, 0x11));
    UT_ASSERT(rb_push(&rb, 0x22));
    UT_ASSERT(rb_push(&rb, 0x33));

    UT_ASSERT(rb_pop(&rb, &v)); UT_ASSERT_EQ(0x11, v);
    UT_ASSERT(rb_pop(&rb, &v)); UT_ASSERT_EQ(0x22, v);
    UT_ASSERT(rb_pop(&rb, &v)); UT_ASSERT_EQ(0x33, v);
    UT_ASSERT(rb_is_empty(&rb));
}

static void test_push_fails_when_full(void)
{
    setup();
    for (uint8_t i = 0; i < CAP; i++) {
        UT_ASSERT(rb_push(&rb, i));
    }
    UT_ASSERT(rb_is_full(&rb));
    UT_ASSERT(!rb_push(&rb, 0xFF));
    UT_ASSERT_EQ((size_t)CAP, rb_count(&rb));
}

static void test_pop_fails_when_empty(void)
{
    uint8_t v = 0xAA;
    setup();
    UT_ASSERT(!rb_pop(&rb, &v));
    UT_ASSERT_EQ(0xAA, v); /* output untouched */
}

static void test_peek_does_not_consume(void)
{
    uint8_t v;
    setup();
    rb_push(&rb, 0x5A);
    UT_ASSERT(rb_peek(&rb, &v)); UT_ASSERT_EQ(0x5A, v);
    UT_ASSERT_EQ(1u, rb_count(&rb));
}

static void test_wrap_around(void)
{
    uint8_t v;
    setup();
    /* Advance head/tail past the end of storage several times */
    for (int round = 0; round < 3 * CAP; round++) {
        UT_ASSERT(rb_push(&rb, (uint8_t)round));
        UT_ASSERT(rb_pop(&rb, &v));
        UT_ASSERT_EQ((uint8_t)round, v);
    }
    UT_ASSERT(rb_is_empty(&rb));
}

static void test_clear_resets_state(void)
{
    setup();
    rb_push(&rb, 1);
    rb_push(&rb, 2);
    rb_clear(&rb);
    UT_ASSERT(rb_is_empty(&rb));
    UT_ASSERT(rb_push(&rb, 3));
}

static void test_null_out_pointer(void)
{
    setup();
    rb_push(&rb, 1);
    UT_ASSERT(!rb_pop(&rb, NULL));
    UT_ASSERT(!rb_peek(&rb, NULL));
    UT_ASSERT_EQ(1u, rb_count(&rb));
}

int main(void)
{
    UT_RUN(test_init_rejects_invalid_args);
    UT_RUN(test_new_buffer_is_empty);
    UT_RUN(test_push_pop_fifo_order);
    UT_RUN(test_push_fails_when_full);
    UT_RUN(test_pop_fails_when_empty);
    UT_RUN(test_peek_does_not_consume);
    UT_RUN(test_wrap_around);
    UT_RUN(test_clear_resets_state);
    UT_RUN(test_null_out_pointer);

    printf("\n%d tests, %d failed\n", ut_run, ut_failed);
    return ut_failed ? 1 : 0;
}
