#include "unity.h"
#include "ring_buffer.h"

void setUp(void) {}
void tearDown(void) {}

/* --- Initialisation tests --- */

void test_init_sets_count_to_zero(void) {
    ring_buffer_t buf;
    ring_buffer_init(&buf);
    TEST_ASSERT_EQUAL_UINT8(0, buf.count);
}

void test_init_sets_head_to_zero(void) {
    ring_buffer_t buf;
    ring_buffer_init(&buf);
    TEST_ASSERT_EQUAL_UINT8(0, buf.head);
}

void test_init_sets_tail_to_zero(void) {
    ring_buffer_t buf;
    ring_buffer_init(&buf);
    TEST_ASSERT_EQUAL_UINT8(0, buf.tail);
}

/* --- Push tests --- */

void test_push_returns_true_when_space_available(void) {
    ring_buffer_t buf;
    ring_buffer_init(&buf);
    TEST_ASSERT_TRUE(queue_push(&buf, 0xAA));
}

void test_push_increments_count(void) {
    ring_buffer_t buf;
    ring_buffer_init(&buf);
    queue_push(&buf, 0xAA);
    TEST_ASSERT_EQUAL_UINT8(1, buf.count);
}

void test_push_stores_correct_value(void) {
    ring_buffer_t buf;
    ring_buffer_init(&buf);
    queue_push(&buf, 0xAA);
    TEST_ASSERT_EQUAL_HEX8(0xAA, buf.buffer[0]);
}

void test_push_multiple_items_increments_count_correctly(void) {
    ring_buffer_t buf;
    ring_buffer_init(&buf);
    queue_push(&buf, 0x01);
    queue_push(&buf, 0x02);
    queue_push(&buf, 0x03);
    TEST_ASSERT_EQUAL_UINT8(3, buf.count);
}

/* --- Overflow protection tests --- */

void test_push_returns_false_when_full(void) {
    ring_buffer_t buf;
    ring_buffer_init(&buf);
    for (int i = 0; i < QUEUE_SIZE; i++) {
        queue_push(&buf, (uint8_t)i);
    }
    TEST_ASSERT_FALSE(queue_push(&buf, 0xFF));
}

void test_push_does_not_increment_count_when_full(void) {
    ring_buffer_t buf;
    ring_buffer_init(&buf);
    for (int i = 0; i < QUEUE_SIZE; i++) {
        queue_push(&buf, (uint8_t)i);
    }
    queue_push(&buf, 0xFF);
    TEST_ASSERT_EQUAL_UINT8(QUEUE_SIZE, buf.count);
}

/* --- Pop tests --- */

void test_pop_returns_true_when_data_available(void) {
    ring_buffer_t buf;
    ring_buffer_init(&buf);
    queue_push(&buf, 0xAA);
    uint8_t val;
    TEST_ASSERT_TRUE(queue_pop(&buf, &val));
}

void test_pop_returns_correct_value(void) {
    ring_buffer_t buf;
    ring_buffer_init(&buf);
    queue_push(&buf, 0xBB);
    uint8_t val;
    queue_pop(&buf, &val);
    TEST_ASSERT_EQUAL_HEX8(0xBB, val);
}

void test_pop_decrements_count(void) {
    ring_buffer_t buf;
    ring_buffer_init(&buf);
    queue_push(&buf, 0xAA);
    uint8_t val;
    queue_pop(&buf, &val);
    TEST_ASSERT_EQUAL_UINT8(0, buf.count);
}

void test_pop_returns_false_when_empty(void) {
    ring_buffer_t buf;
    ring_buffer_init(&buf);
    uint8_t val;
    TEST_ASSERT_FALSE(queue_pop(&buf, &val));
}

/* --- FIFO ordering tests --- */

void test_fifo_order_preserved(void) {
    ring_buffer_t buf;
    ring_buffer_init(&buf);
    queue_push(&buf, 0x01);
    queue_push(&buf, 0x02);
    queue_push(&buf, 0x03);

    uint8_t val;
    queue_pop(&buf, &val);
    TEST_ASSERT_EQUAL_HEX8(0x01, val);
    queue_pop(&buf, &val);
    TEST_ASSERT_EQUAL_HEX8(0x02, val);
    queue_pop(&buf, &val);
    TEST_ASSERT_EQUAL_HEX8(0x03, val);
}

/* --- Wraparound tests --- */

void test_wraparound_maintains_correct_values(void) {
    ring_buffer_t buf;
    ring_buffer_init(&buf);

    for (uint8_t i = 0; i < QUEUE_SIZE; i++) {
        queue_push(&buf, i);
    }

    uint8_t val;
    for (int i = 0; i < QUEUE_SIZE / 2; i++) {
        queue_pop(&buf, &val);
    }

    queue_push(&buf, 0xAA);
    queue_push(&buf, 0xBB);

    for (int i = QUEUE_SIZE / 2; i < QUEUE_SIZE; i++) {
        queue_pop(&buf, &val);
        TEST_ASSERT_EQUAL_UINT8((uint8_t)i, val);
    }

    queue_pop(&buf, &val);
    TEST_ASSERT_EQUAL_HEX8(0xAA, val);
    queue_pop(&buf, &val);
    TEST_ASSERT_EQUAL_HEX8(0xBB, val);
}

/* --- Helper function tests --- */

void test_is_empty_returns_true_when_empty(void) {
    ring_buffer_t buf;
    ring_buffer_init(&buf);
    TEST_ASSERT_TRUE(queue_is_empty(&buf));
}

void test_is_empty_returns_false_when_not_empty(void) {
    ring_buffer_t buf;
    ring_buffer_init(&buf);
    queue_push(&buf, 0xAA);
    TEST_ASSERT_FALSE(queue_is_empty(&buf));
}

void test_is_full_returns_true_when_full(void) {
    ring_buffer_t buf;
    ring_buffer_init(&buf);
    for (int i = 0; i < QUEUE_SIZE; i++) {
        queue_push(&buf, (uint8_t)i);
    }
    TEST_ASSERT_TRUE(queue_is_full(&buf));
}

void test_is_full_returns_false_when_not_full(void) {
    ring_buffer_t buf;
    ring_buffer_init(&buf);
    TEST_ASSERT_FALSE(queue_is_full(&buf));
}