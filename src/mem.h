#ifndef MEM_H
#define MEM_H

#include "defines.h"

typedef struct {
  void *start_ptr;
  u64 size;
  u64 seek;
  u64 alignment;
} Arena;

Arena *create_arena(const u64 size, const u64 alignment);
Arena *create_arena_aligned(const u64 size);
Arena *arena_init();
void print_arena(Arena *arena);
void *arena_alloc(Arena *arena, const u64 size);
void arena_free(Arena *arena);

#endif // !MEM_H
