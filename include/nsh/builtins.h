// builtins.h
#ifndef NSH_BUILTINS_H
#define NSH_BUILTINS_H
#include <stdint.h>
#include <string.h>

#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__)
# error "TAG4/make_tag supposent little-endian"
#endif

typedef int (*builtin_fn)(int argc, char **argv, char **envp);

typedef struct builtins_s {
    uint32_t   tag;     // 4 premiers octets du nom packés (little-endian)
    const char *name;   // pour vérification finale
    builtin_fn  function;
} builtins_t;

typedef builtins_t builtin_t;

// Little-endian packing: 'a' -> least-significant byte. Must match make_tag().
// Pack 4 chars (uses '\0' for short names)
#define TAG4(a,b,c,d) \
    ( ((uint32_t)(unsigned char)(a)      ) | \
      ((uint32_t)(unsigned char)(b) <<  8) | \
      ((uint32_t)(unsigned char)(c) << 16) | \
      ((uint32_t)(unsigned char)(d) << 24) )

// Depuis un littéral de chaîne (<=4 chars)
#define TAG4S(s) TAG4((s)[0], (s)[1], (s)[2], (s)[3])

#define TAG4L(s) \
  TAG4( ((sizeof(s)>0)?(s)[0]:0), ((sizeof(s)>1)?(s)[1]:0), \
        ((sizeof(s)>2)?(s)[2]:0), ((sizeof(s)>3)?(s)[3]:0) )

static inline uint32_t make_tag(const char *s) {
    uint32_t tag = 0;
    for (int i = 0; i < 4 && s[i]; i++)
        tag |= (uint32_t)(unsigned char)s[i] << (i * 8);
    return tag;
}

// Comparaison rapide: tag puis strcmp
static inline int builtin_match(uint32_t tag, const char *name, const char *q) {
    return (tag == make_tag(q)) && (strcmp(name, q) == 0);
}

extern const builtins_t BUILTIN_TAB[];

#endif // NSH_BUILTINS_H
