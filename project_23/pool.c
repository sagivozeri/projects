#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PEOPLE				10
#define NUM_ELEMENTS			20
#define NUM_SECONDS_PER_ELEM	(60 / NUM_ELEMENTS)

int arr[NUM_ELEMENTS] = {0};
int count = 0;
time_t prev_time, base_time;

int enter_pool()
{
	time_t curr_time;
	int prev_s, curr_s;
	int prev_idx, curr_idx;
	int rc = 0;

	time(&curr_time);

	prev_s = (prev_time - base_time) % 60;
	curr_s = (curr_time - base_time) % 60;

	prev_idx = prev_s / NUM_SECONDS_PER_ELEM;
	curr_idx = curr_s / NUM_SECONDS_PER_ELEM;

	printf("prev_s %d prev_idx %d curr_s %d curr_idx %d\n",
			prev_s, prev_idx, curr_s, curr_idx);

	/* More than 1 minute - clear the array */
	if (curr_time > prev_time + 60) {
		memset(arr, 0, NUM_ELEMENTS * sizeof(int));
		count = 0;
	} else { /* Less than 1 minute - clear all the elements which are between prev_idx (not inclusive) and curr_idx (inclusive) */
		while (prev_idx != curr_idx) {
			prev_idx = (prev_idx + 1) % NUM_ELEMENTS;
			count -= arr[prev_idx];
			arr[prev_idx] = 0;
		}

		if (count >= MAX_PEOPLE) {
			rc = -1;
			goto end;
		}
	}

	arr[curr_idx]++;
	count++;

	printf("Current count = %d\n", count);
end:
	prev_time = curr_time;
	return rc;
}

int main()
{
	int val, rc;
	time(&base_time);

	prev_time = base_time;

	printf("Enter 1 for new person 0 to exit\n");

	while (1) {
		scanf("%d", &val);
		if (!val)
			break;

		rc = enter_pool();
		if (rc)
			printf("No place in the pool\n");
	}

	return 0;
}
