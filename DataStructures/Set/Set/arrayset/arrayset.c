#include "arrayset.h"
// Standard
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ArraySet *
ArraySet_create(int element_num) {
    struct ArraySet * set =
        (struct ArraySet *)(malloc(sizeof(struct ArraySet)));
    set->m_arr = (int *)(malloc(element_num * sizeof(int)));
    set->m_arrsize = element_num;
    set->m_size = 0;

    return set;
}//ArraySet_create(element_num)

void
ArraySet_destroy(struct ArraySet * set) {
    free(set->m_arr);
    free(set);
}//ArraySet_destroy(set)

int
ArraySet_size(const struct ArraySet * set) {
    return set->m_size;
}//ArraySet_size(set)

int
ArraySet_maxsize(const struct ArraySet * set) {
    return set->m_arrsize;
}//ArraySet_maxsize(set)

int
ArraySet_insert(struct ArraySet * set, int value) {
    if(ArraySet_find(set, value) != -1)
        return 0;
    if(set->m_size == set->m_arrsize)
        return -1;
    set->m_arr[set->m_size] = value;
    ++set->m_size;
    return 1;
}//ArraySet_insert(set, value)

int
ArraySet_delete(struct ArraySet * set, int value) {
    int index = ArraySet_find(set, value);
    if(index == -1)
        return 0;
    memcpy(&set->m_arr[index], &set->m_arr[index+1],
            (set->m_size - index) * sizeof(int));
    --set->m_size;
    return 1;
}//ArraySet_delete(set, value)

int
ArraySet_find(const struct ArraySet * set, int value) {
    int i;
    for(i = 0; i < set->m_size; ++i) {
        if(set->m_arr[i] == value)
            return i;
    }//for
    return -1;
}//ArraySet_find(set, value)

void
ArraySet_printall(const struct ArraySet * set) {
    int i;
    printf("{ ");
    for(i = 0; i < set->m_size-1; ++i) {
        printf("%d, ", set->m_arr[i]);
    }//for
    if(set->m_size > 0) {
        printf("%d }\n", set->m_arr[set->m_size-1]);
    } else {
        printf("}\n");
    }//if-else
}//ArraySet_printall(set)

void
ArraySet_clear(struct ArraySet * set) {
    set->m_size = 0;
}//ArraySet_clear(set)

void
ArraySet_union(struct ArraySet * result,
        const struct ArraySet * a,
        const struct ArraySet * b) {
    int i = 0;
    ArraySet_clear(result);
    for(i = 0; i < a->m_size; ++i)
        ArraySet_insert(result, a->m_arr[i]);
    for(i = 0; i < b->m_size; ++i)
        ArraySet_insert(result, b->m_arr[i]);
}//ArraySet_union(result, a, b)

void
ArraySet_intersect(struct ArraySet * result,
        const struct ArraySet * a,
        const struct ArraySet * b) {
    int i = 0;
    int value = 0;
    ArraySet_clear(result);
    for(i = 0; i < a->m_size; ++i) {
        value = a->m_arr[i];
        if(ArraySet_find(b, value) != -1)
            ArraySet_insert(result, value);
    }//for
    for(i = 0; i < b->m_size; ++i) {
        value = b->m_arr[i];
        if(ArraySet_find(a, value) != -1)
            ArraySet_insert(result, value);
    }//for
}//ArraySet_intersect(result, a, b)

void
ArraySet_diff(struct ArraySet * result,
        const struct ArraySet * a,
        const struct ArraySet * b) {
    int i = 0;
    int value = 0;
    ArraySet_clear(result);
    for(i = 0; i < a->m_size; ++i) {
        value = a->m_arr[i];
        if(ArraySet_find(b, value) == -1)
            ArraySet_insert(result, value);
    }//for
}//ArraySet_diff(result, a, b)

