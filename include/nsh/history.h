// history.h - Command history integration
#ifndef NSH_HISTORY_H
#define NSH_HISTORY_H

#include <stdint.h>

#define HISTORY_FILE ".nsh_history"

#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__)
# error "HISTORY_FLAG_TAG assumes little-endian"
#endif

typedef uint16_t history_flag_tag_t;

#define HISTORY_FLAG_TAG(a, b) \
    (((uint16_t)(unsigned char)(a)) | \
     ((uint16_t)(unsigned char)(b) << 8))

#define HISTORY_FLAG_TAG2(s) \
    HISTORY_FLAG_TAG((s)[0], (s)[1])

static inline history_flag_tag_t make_history_flag_tag(const char *flag)
{
    history_flag_tag_t tag = 0;

    if (!flag)
        return 0;
    for (int i = 0; i < 2 && flag[i]; i++)
        tag |= (history_flag_tag_t)(unsigned char)flag[i] << (i * 8);
    return tag;
}

enum history_flag {
    HISTORY_FLAG_H = HISTORY_FLAG_TAG('-', 'h'),
    HISTORY_FLAG_C = HISTORY_FLAG_TAG('-', 'c'),
    HISTORY_FLAG_W = HISTORY_FLAG_TAG('-', 'w'),
    HISTORY_FLAG_R = HISTORY_FLAG_TAG('-', 'r'),
    HISTORY_FLAG_D = HISTORY_FLAG_TAG('-', 'd')
};

int init_history(char *path);

#endif // NSH_HISTORY_H
