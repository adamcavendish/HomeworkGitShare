#pragma once

struct LinkNode {
    int m_value;
    struct LinkNode * m_prev;
    struct LinkNode * m_next;
};//struct LinkNode

struct LinkListSet {
    struct LinkNode * m_head;
};//struct LinkListSet

struct LinkNode *
LinkNode_create(int value);

struct LinkListSet *
LinkListSet_create();

void
LinkListSet_destroy(struct LinkListSet * set);

/**
 * @brief insert `value` into LinkListSet
 * @return on success, return 1;
 *      on failure (already there), return 0;
 */
int
LinkListSet_insert(struct LinkListSet * set, int value);

/**
 * @brief delete `value` from LinkListSet
 * @return on success return 1;
 *      on failure (not there), return 0;
 */
int
LinkListSet_delete(struct LinkListSet * set, int value);

/**
 * @brief find `value` inside LinkListSet
 * @return if found return the node of the `value`;
 *      if not found return NULL;
 */
struct LinkNode *
LinkListSet_find(const struct LinkListSet * set, int value);

/**
 * @brief print all LinkListSet's elements
 */
void
LinkListSet_printall(const struct LinkListSet * set);

/**
 * @brief clear all elements inside LinkListSet
 */
void
LinkListSet_clear(struct LinkListSet * set);

/**
 * @brief compute union of `a` and `b`
 */
void
LinkListSet_union(
        struct LinkListSet * result,
        const struct LinkListSet * a,
        const struct LinkListSet * b);

void
LinkListSet_intersect(
        struct LinkListSet * result,
        const struct LinkListSet * a,
        const struct LinkListSet * b);

void
LinkListSet_diff(
        struct LinkListSet * result,
        const struct LinkListSet * a,
        const struct LinkListSet * b);

