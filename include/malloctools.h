#ifndef MALLOCTOOLS
#define MALLOCTOOLS

#define MALLOC_CHECK(ptr) \
    if ((ptr) == NULL) { \
        fprintf(stderr, "Erreur d'allocation mémoire.\n"); \
        exit(1); \
    }

#endif