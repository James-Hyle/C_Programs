#include <stdio.h>
#define MAX_LINE 40

int main(void) {
	char buffer[MAX_LINE] = {};

	while (fgets(buffer, MAX_LINE, stdin) != NULL) {
		for (int i = 0; i < MAX_LINE - 1; i++) {
			if (buffer[i] == '\n') { buffer[i] = ' '; }
		}
		printf("%s", buffer);
	}
	return 0;
}