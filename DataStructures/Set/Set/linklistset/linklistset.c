#include "linklistset.h"
// Standard
#include <stdio.h>
#include <stdlib.h>

struct LinkNode *
LinkNode_create(int value) {
    struct LinkNode * node =
        (struct LinkNode *)(malloc(sizeof(struct LinkNode)));
    node->m_value = value;
    node->m_prev = NULL;
    node->m_next = NULL;
    return node;
}//LinkNode_create(value)

struct LinkListSet *
LinkListSet_create() {
    struct LinkListSet * ret =
        (struct LinkListSet *)(malloc(sizeof(struct LinkListSet)));
    ret->m_head = NULL;
    return ret;
}//LinkListSet_create()

void
LinkListSet_destroy(struct LinkListSet * set) {
    struct LinkNode * node = set->m_head;
    while(node != NULL) {
        set->m_head = set->m_head->m_next;
        free(node);
        node = set->m_head;
    }//while
    set->m_head = NULL;
    free(set);
}//LinkListSet_destroy(set)

int
LinkListSet_insert(struct LinkListSet * set, int value) {
    if(LinkListSet_find(set, value) != NULL)
        return 0;
    struct LinkNode * node = LinkNode_create(value);
    if(set->m_head == NULL) {
        set->m_head = node;
        return 1;
    }//if
    node->m_prev = NULL;
    node->m_next = set->m_head;
    set->m_head->m_prev = node;
    set->m_head = node;
    return 1;
}//LinkListSet_insert(set, value)

int
LinkListSet_delete(struct LinkListSet * set, int value) {
    struct LinkNode * node = LinkListSet_find(set, value);
    if(node == NULL)
        return 0;

    if(node->m_prev != NULL) {
        node->m_prev->m_next = node->m_next;
    } else {
        set->m_head = node->m_next;
    }//if-else

    if(node->m_next != NULL)
        node->m_next->m_prev = node->m_prev;

    free(node);
    return 1;
}//LinkListSet_delete(set, value)

struct LinkNode *
LinkListSet_find(const struct LinkListSet * set, int value) {
    struct LinkNode * node = set->m_head;
    while(node != NULL) {
        if(node->m_value == value)
            return node;
        node = node->m_next;
    }//while
    return NULL;
}//LinkListSet_find(set, value)

void
LinkListSet_printall(const struct LinkListSet * set) {
    struct LinkNode * node = set->m_head;

    printf("{ ");
    if(node == NULL) {
        printf("}\n");
        return;
    }//if

    while(node->m_next != NULL) {
        printf("%d, ", node->m_value);
        node = node->m_next;
    }//while
    printf("%d }\n", node->m_value);
}//LinkListSet_printall(set)

void
LinkListSet_clear(struct LinkListSet * set) {
    struct LinkNode * node = set->m_head;
    while(node != NULL) {
        set->m_head = set->m_head->m_next;
        free(node);
        node = set->m_head;
    }//while
    set->m_head = NULL;
}//LinkListSet_clear(set)

void
LinkListSet_union(
        struct LinkListSet * result,
        const struct LinkListSet * a,
        const struct LinkListSet * b) {
    LinkListSet_clear(result);

    struct LinkNode * node = a->m_head;
    while(node != NULL) {
        LinkListSet_insert(result, node->m_value);
        node = node->m_next;
    }//while
    node = b->m_head;
    while(node != NULL) {
        LinkListSet_insert(result, node->m_value);
        node = node->m_next;
    }//while
}//LinkListSet_union(result, a, b)

void
LinkListSet_intersect(
        struct LinkListSet * result,
        const struct LinkListSet * a,
        const struct LinkListSet * b) {
    LinkListSet_clear(result);

    struct LinkNode * node = a->m_head;
    while(node != NULL) {
        if(LinkListSet_find(b, node->m_value) != NULL)
            LinkListSet_insert(result, node->m_value);
        node = node->m_next;
    }//while

    node = b->m_head;
    while(node != NULL) {
        if(LinkListSet_find(a, node->m_value) != NULL)
            LinkListSet_insert(result, node->m_value);
        node = node->m_next;
    }//while
}//LinkListSet_inserset(result, a, b)

void
LinkListSet_diff(
        struct LinkListSet * result,
        const struct LinkListSet * a,
        const struct LinkListSet * b) {
    LinkListSet_clear(result);

    struct LinkNode * node = a->m_head;
    while(node != NULL) {
        if(LinkListSet_find(b, node->m_value) == NULL)
            LinkListSet_insert(result, node->m_value);
        node = node->m_next;
    }//while
}//LinkListSet_diff(result, a, b)

