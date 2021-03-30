#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

static struct termios oldt;

void restore_terminal_settings(void)
{
	tcsetattr(0, TCSANOW, &oldt);  /* Apply saved settings */
}

void disable_waiting_for_enter(void)
{
	struct termios newt;

	/* Make terminal read 1 char at a time */
	tcgetattr(0, &oldt);  /* Save terminal settings */
	newt = oldt;  /* Init new settings */
	newt.c_lflag &= ~(ICANON | ECHO);  /* Change settings */
	tcsetattr(0, TCSANOW, &newt);  /* Apply settings */
	atexit(restore_terminal_settings); /* Make sure settings will be restored when program ends  */
}

#if 1
int main()
{
	char question[100] = "Answer the following: ";
	char buf[100];
	int ch, i, fill, len;

	len = strlen(question);

	while (1) {
		i = 0;
		fill = 1;

		disable_waiting_for_enter();

		/* Key reading loop */
		while (1) {
			ch = getchar();

			if (ch == '\n') break;

			if (fill && ch == '.') {
				buf[i] = 0;
				fill = 0;
			}

			if (fill)
				buf[i] = (char)ch;

			if (i < len) {
				printf("%c", question[i]);
			} else if (ch == 127) {
				putchar(8);
				putchar(' ');
				putchar(8);
			} else {
				printf("%c", ch);
			}

			i++;
		}

		printf("\nThe answer is: %s\n", buf);

		restore_terminal_settings();

		printf("Again? ");
		scanf("%s", buf);
		if (!strcmp(buf, "no")) break;

		printf("Next question...\n");
		getchar();
	}

	return 0;
}
#else
int main()
{
	int ch, i, fill, len;

//	disable_waiting_for_enter();

	while (1) {
		ch = getchar();
		if (ch == 'q') return 0;
#if 0
		if (ch == 127)
			putchar(8);
		else
			putchar(ch);
#else
		printf("char = %c\n", ch);
#endif
	}

	return 0;
}
#endif
