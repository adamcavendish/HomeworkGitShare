#pragma once

struct ArraySet
{
    int * m_arr;
    int m_arrsize;
    int m_size;
};//struct ArraySet

/**
 * @brief create ArraySet
 */
struct ArraySet *
ArraySet_create(int element_num);

void
ArraySet_destroy(struct ArraySet * set);

/**
 * @brief return the number of elements inside ArraySet
 */
int
ArraySet_size(const struct ArraySet * set);

/**
 * @brief return the maximum of elements ArraySet can hold
 */
int
ArraySet_maxsize(const struct ArraySet * set);

/**
 * @brief insert `value` into ArraySet
 * @return on success, return 1;
 *      on failure (already there), return 0;
 *      on full(it can hold no more values), return -1;
 */
int
ArraySet_insert(struct ArraySet * set, int value);

/**
 * @brief delete `value` from ArraySet
 * @return on success return 1;
 *      on failure (not there), return 0;
 */
int
ArraySet_delete(struct ArraySet * set, int value);

/**
 * @brief find `value` inside ArraySet
 * @return if found return the index of the `value`;
 *      if not found return -1;
 */
int
ArraySet_find(const struct ArraySet * set, int value);

/**
 * @brief print all ArraySet's elements
 */
void
ArraySet_printall(const struct ArraySet * set);

/**
 * @brief clear all elements inside ArraySet
 */
void
ArraySet_clear(struct ArraySet * set);

/**
 * @brief compute union of `a` and `b`
 */
void
ArraySet_union(
        struct ArraySet * result,
        const struct ArraySet * a,
        const struct ArraySet * b);

void
ArraySet_intersect(
        struct ArraySet * result,
        const struct ArraySet * a,
        const struct ArraySet * b);

void
ArraySet_diff(
        struct ArraySet * result,
        const struct ArraySet * a,
        const struct ArraySet * b);

