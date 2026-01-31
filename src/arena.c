#include "arena.h"
#include <stdlib.h>

struct Arena {
	unsigned char *base;
	size_t capacity;
	size_t pos;
};

Arena* arena_create(size_t capacity) {
	Arena* arena = malloc(sizeof *arena);
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


