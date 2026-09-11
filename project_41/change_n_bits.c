#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned long u32;
typedef unsigned long long u64;

#define BITS_IN_ELEM 32

enum _level {
    DEBUG,
    INFO
};

#ifdef SET_DEBUG
int level = DEBUG;
#else
int level = INFO;
#endif

#define print_debug(...)        \
do {                            \
    if (level <= DEBUG)         \
        printf(__VA_ARGS__);    \
} while (0)

#define print_info(...)         \
do {                            \
    if (level <= INFO)          \
        printf(__VA_ARGS__);    \
} while (0)

int read_int_from_stdin(const char *prompt, int base, u32 *out)
{
    char buffer[128];
    char *endptr;
    long value;

    if (!out)
        return -1;

    if (prompt)
        print_info("%s", prompt);

    if (!fgets(buffer, sizeof(buffer), stdin))
        return -1;

    value = strtol(buffer, &endptr, base);
    if (endptr == buffer)
        return -1;

    while (*endptr == ' ' || *endptr == '\t')
        endptr++;

    if (*endptr != '\n' && *endptr != '\0')
        return -1;

    *out = (int)value;

    return 0;
}


void __get_nth_bits(u32 *arr, u32 num_bits, u32 offset, u64 *val)
{
    print_debug("num_bits %lu offset %lu\n", num_bits, offset);

    u32 elem = offset / BITS_IN_ELEM;
    u32 shift = BITS_IN_ELEM - num_bits - (offset % BITS_IN_ELEM);
    u64 mask = ((1ULL << num_bits) - 1) << shift;

    print_debug("elem %lu shift %lu mask 0x%llx\n", elem, shift, mask);

    *val = (arr[elem] & mask) >> shift;
}

int get_nth_bits(u32 *arr, u32 num_elems, u32 num_bits, u32 offset, u64 *val)
{
    if (!arr || !val) {
        print_info("Invalid NULL args\n");
        return -1;
    }

    if (offset + num_bits >= num_elems * BITS_IN_ELEM) {
        print_info("To big offset\n");
        return -1;
    }

    int rel_offset = offset % BITS_IN_ELEM;
    int elem = offset / BITS_IN_ELEM;

    if (rel_offset + num_bits > BITS_IN_ELEM) {
        u32 off1 = offset, off2 = (elem + 1) * BITS_IN_ELEM;
        u32 num_bits1 = BITS_IN_ELEM - rel_offset, num_bits2 = num_bits - num_bits1;
        u64 val1, val2;

        __get_nth_bits(arr, num_bits1, off1, &val1);
        __get_nth_bits(arr, num_bits2, off2, &val2);

        print_debug("val1 0x%llx val2 0x%llx\n", val1, val2);

        *val = val1 << num_bits2 | val2;

        return 0;
    }

    __get_nth_bits(arr, num_bits, offset, val);

    return 0;
}

int main(int argc, char **argv)
{
    if (argc > 1) {
        print_info("Wrong Input\n");
        return -1;
    }

    srand(time(NULL));

    u32 num_elems = rand() % 10 + 1; // number between 1-10

    u32 *arr = malloc(sizeof(u32) * num_elems);
    if (!arr)
        return -1;

    int rc;

    for (int i = 0; i < num_elems; i++)
        arr[i] = rand();

    print_info("Array (%lu bits):\n", num_elems * BITS_IN_ELEM);
    for (int i = 0; i < num_elems; i++)
        print_info("%lx ", arr[i]);

    printf("\n\n");

    u32 num_bits;
    if (read_int_from_stdin("Set num bits\n", 10, &num_bits) || num_bits == 0 || num_bits >= 64) {
        print_info("Invalid number of bits\n");
        rc = -1;
        goto out;
    }

    u32 offset;
    if (read_int_from_stdin("Set offset\n", 10, &offset) || offset < 0) {
        print_info("Invalid offset\n");
        rc = -1;
        goto out;
    }

    print_debug("\nnum_bits = %lu, offset = %lu\n", num_bits, offset);

    u64 val;

    rc = get_nth_bits(arr, num_elems, num_bits, offset, &val);
    if (!rc)
        print_info("val = 0x%llx\n", val);

out:
    free(arr);
    return rc;
}
