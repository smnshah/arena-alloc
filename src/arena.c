#include "arena.h"
#include <stdlib.h>

#define ARENA_ALIGN sizeof(void*)
#define ALIGN_UP_POW2(val, align) (((val) + (align) - 1) & ~((align) - 1))

struct Arena {
	unsigned char *base;
	size_t capacity;
	size_t pos;
};

Arena* arena_create(size_t capacity) {
	Arena *arena = malloc(sizeof *arena);
	if (!arena) { 
		return NULL; 
	}
	
	arena->base = malloc(capacity);
	if (!arena->base) {
		free(arena);
		return NULL;
	}

	arena->capacity = capacity;
	arena->pos = 0;

	return arena;
}

void arena_destroy(Arena *arena) {
	if (!arena) { 
		return; 
	}

	free(arena->base);
	free(arena);
}

void* arena_alloc(Arena *arena, size_t size) {
	if (!arena) {
		return NULL;
	}

	size_t pos_aligned = ALIGN_UP_POW2(arena->pos, ARENA_ALIGN);
	size_t new_pos = pos_aligned + size;
	
	if (new_pos > arena->capacity) { 
		return NULL; 
	}

	arena->pos = new_pos;
	return arena->base + pos_aligned;
}

void arena_reset(Arena *arena) {
	if (!arena) { 
		return; 
	}
	
	arena->pos = 0;
}


