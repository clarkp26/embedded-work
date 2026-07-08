#ifndef BIT_MANIPULATION_H
#define BIT_MANIPULATION_H

#include <stdint.h>
#include <stdbool.h>

static inline void bit_set(uint8_t *reg, uint8_t bit) {
    *reg |= (uint8_t)(1u << bit);
}

static inline void bit_clear(uint8_t *reg, uint8_t bit) {
    *reg &= (uint8_t)(~(1u << bit));
}

static inline void bit_toggle(uint8_t *reg, uint8_t bit) {
    *reg ^= (uint8_t)(1u << bit);
}

static inline bool bit_check(uint8_t reg, uint8_t bit) {
    return (reg & (uint8_t)(1u << bit)) != 0u;
}

#endif