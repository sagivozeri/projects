#include <stdio.h>
#include <string.h>

#define BITS_PER_BYTE 8 
#define SIZE 10

typedef unsigned char u8;
typedef unsigned int u32;

void print_bits(u32 n)
{
    int i, bits = sizeof(n) * BITS_PER_BYTE;

    for (i = 0; i < bits; i++)
        printf("%d", (n >> (bits - i - 1)) & 0x1);
}

void print_array_bits(u32 *a, int n)
{
    int i, j, val;

    for (i = 0; i < n; i++) {
            val = a[i];
            printf("bits of (a[%d]): ", i);
            print_bits(a[i]);
            printf("\n");
    }
    printf("\n");
}

#define BIT(n)  (1 << (n))

void modify_elem(u32 *a, int n, int size, int idx, u32 val)
{
    int arr_elem_bits = sizeof(u32) * BITS_PER_BYTE;

    if (size > arr_elem_bits) {
        printf("Invalid elem size %d\n", size);
        return;
    }

    int location = size * idx;
    if (location + size > n * arr_elem_bits) {
        printf("Invalid idx %d for elem_size %d\n", idx, size);
        return;
    }

    int arr_idx = location / 32;
    int offset = location % 32;
    int shift_left = 32 - offset - size;

    if (shift_left < 0) {
        int val_1 = val >> (-shift_left);
        int val_2 = val << (32 + shift_left);
        int size_1 = size + shift_left;
        int size_2 = size - size_1;
        u32 mask_1 = ~(BIT(size_1) - 1);
        u32 mask_2 = BIT(32 - size_2) - 1; 
        a[arr_idx] = (a[arr_idx] & mask_1) | val_1;
        a[arr_idx + 1] = (a[arr_idx+1] & mask_2) | val_2;
    } else {
        int val_1 = val << shift_left;
        int mask_1 = size < 32 ? ~((BIT(size) - 1) << shift_left) : 0;
        a[arr_idx] = (a[arr_idx] & mask_1) | val_1;
    }
}

int main()
{
    u32 arr[SIZE];
    int i, j;
    
    memset(arr, 0xAAAAAAAA, SIZE * sizeof(u32));

    print_array_bits(arr, SIZE);
    modify_elem(arr, SIZE, 8, 2, 0x0);
    print_array_bits(arr, SIZE);
}