#include "mem.h"
#include "defines.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_ALIGNMENT 8

Arena *create_arena(const u64 size, const u64 alignment) {
  assert((alignment & (alignment - 1)) == 0 && "alginment is not power of 2");
  Arena *arena = malloc(sizeof(Arena) + size);

  arena->size = size;
  arena->alignment = alignment;
  arena->seek = 0;
  arena->start_ptr = malloc(size);

  return arena;
}

Arena *create_arena_aligned(const u64 size) {
  return create_arena(size, DEFAULT_ALIGNMENT);
}

void *arena_alloc(Arena *arena, const u64 size) {
  u64 address = (u64)arena->start_ptr + arena->seek;
  u64 padding = arena->alignment - (address & (arena->alignment - 1));

  assert(arena->seek + padding <= arena->size && "not enough memory in arena");

  arena->seek += padding;
  return (void *)address;
}

void arena_free(Arena *arena) {
  arena->size = 0;
  arena->seek = 0;

  free(arena->start_ptr);
  free(arena);
}

Arena *arena_init() { return create_arena_aligned(Gigabyte(1)); }

void print_arena(Arena *arena) {
  printf("size, %lld\n", arena->size);
  printf("alignment, %lld\n", arena->alignment);
  printf("start_ptr, %p\n", arena->start_ptr);
  printf("seek: %lld\n\n", arena->seek);
}
