#ifndef OBJ_POOL_H_INCLUDED
#define OBJ_POOL_H_INCLUDED

#include <stddef.h>
#include <stdio.h>
#include "obj.h"

/*
 * @todo keep objects  sorted by tab using a cache-frieldy list for fast inserting in arbitary place of pool  
 */

typedef uint32_t pool_idx;
constexpr pool_idx OBJ_POOL_BAD_IDX = (pool_idx)(-1);

struct ObjectPool {
    Object *objs;
    size_t nobjs;
    size_t capacity;
};

int obj_pool_init (ObjectPool *this_, size_t size);
int obj_pool_free (ObjectPool *this_);

pool_idx obj_pool_look_up (const ObjectPool *this_, Object obj);
pool_idx obj_pool_insert  (ObjectPool *this_, Object obj);
Object   obj_pool_get     (const ObjectPool *this_, pool_idx idx);
size_t   obj_pool_size    (const ObjectPool *this_);
size_t   obj_pool_dump    (const ObjectPool *this_, FILE *file);

inline ObjectPool obj_pool_destroyable() { return ObjectPool{ .objs = NULL, .nobjs = 0, .capacity = 0 }; }

#endif // OBJ_POOL_H_INCLUDED