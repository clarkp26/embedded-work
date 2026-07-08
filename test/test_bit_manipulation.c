#include "unity.h"
#include "bit_manipulation.h"

void setUp(void) {}
void tearDown(void) {}

void test_bit_set_sets_correct_bit(void) {
    uint8_t reg = 0x00;
    bit_set(&reg, 3);
    TEST_ASSERT_EQUAL_HEX8(0x08, reg);
}

void test_bit_set_does_not_affect_other_bits(void) {
    uint8_t reg = 0xF0;
    bit_set(&reg, 0);
    TEST_ASSERT_EQUAL_HEX8(0xF1, reg);
}

void test_bit_set_idempotent_when_already_set(void) {
    uint8_t reg = 0xFF;
    bit_set(&reg, 4);
    TEST_ASSERT_EQUAL_HEX8(0xFF, reg);
}

void test_bit_clear_clears_correct_bit(void) {
    uint8_t reg = 0xFF;
    bit_clear(&reg, 5);
    TEST_ASSERT_EQUAL_HEX8(0xDF, reg);
}

void test_bit_clear_does_not_affect_other_bits(void) {
    uint8_t reg = 0xFF;
    bit_clear(&reg, 0);
    TEST_ASSERT_EQUAL_HEX8(0xFE, reg);
}

void test_bit_clear_idempotent_when_already_clear(void) {
    uint8_t reg = 0x00;
    bit_clear(&reg, 3);
    TEST_ASSERT_EQUAL_HEX8(0x00, reg);
}

void test_bit_toggle_toggles_bit_from_zero(void) {
    uint8_t reg = 0x00;
    bit_toggle(&reg, 7);
    TEST_ASSERT_EQUAL_HEX8(0x80, reg);
}

void test_bit_toggle_toggles_bit_from_one(void) {
    uint8_t reg = 0xFF;
    bit_toggle(&reg, 7);
    TEST_ASSERT_EQUAL_HEX8(0x7F, reg);
}

void test_bit_toggle_twice_restores_original(void) {
    uint8_t reg = 0xA5;
    bit_toggle(&reg, 3);
    bit_toggle(&reg, 3);
    TEST_ASSERT_EQUAL_HEX8(0xA5, reg);
}

void test_bit_check_returns_true_when_set(void) {
    uint8_t reg = 0x08;
    TEST_ASSERT_TRUE(bit_check(reg, 3));
}

void test_bit_check_returns_false_when_clear(void) {
    uint8_t reg = 0xF7;
    TEST_ASSERT_FALSE(bit_check(reg, 3));
}

void test_bit_check_bit_zero(void) {
    uint8_t reg = 0x01;
    TEST_ASSERT_TRUE(bit_check(reg, 0));
}

void test_bit_check_bit_seven(void) {
    uint8_t reg = 0x80;
    TEST_ASSERT_TRUE(bit_check(reg, 7));
}