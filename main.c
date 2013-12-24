/**
 * Copyright (C) 2013 Kyriakos Georgiou
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "def.h"

PRIVATE void printPreamble();
PRIVATE void printMenu();

int main(int argc, char *argv[]) {

	int i;

	printPreamble();

	if (argc < 2) {
		printMenu();
		return EXIT_FAILURE;
	}

	if (strcmp(argv[1], "-list") == 0) {
		for (i = 2; i < argc; i++) {
			list(argv[i]);
		}
	} else if (strcmp(argv[1], "-mono") == 0) {
		for (i = 2; i < argc; i++) {
			mono(argv[i]);
		}
	} else if (strcmp(argv[1], "-reverse") == 0) {
		for (i = 2; i < argc; i++) {
			reverse(argv[i]);
		}
	} else if (strcmp(argv[1], "-chop") == 0) {
		for (i = 2; i < argc - 2; i += 3) {

			if (strlen(argv[i + 1]) > 8 || strlen(argv[i + 2]) > 8) {
				printf(
						"Extremely big numbers given for start or end chop points.\n");
				continue;
			}

			int start;
			int end;

			if (strcmp(argv[i + 1], "0") == 0) {
				start = 0;
			} else if ((start = strtol(argv[i + 1], NULL, 10)) == 0L) {
				printf("Invalid number format for chop start point.\n");
				continue;
			}

			if (strcmp(argv[i + 2], "0") == 0) {
				end = 0;
			} else if ((end = strtol(argv[i + 2], NULL, 10)) == 0L) {
				printf("Invalid number format for chop start point.\n");
				continue;
			}

			chop(argv[i], start, end);
		}
	} else {
		printMenu();
	}

	return EXIT_SUCCESS;
}

PRIVATE void printPreamble() {
	printf("\n####################################################\n");
	printf("# wavengine  Copyright (C) 2013  Kyriakos Georgiou #\n"
			"# This program comes with ABSOLUTELY NO WARRANTY.  #\n"
			"# This is free software, and you are welcome to    #\n"
			"# redistribute it under certain conditions.        #\n");
	printf("####################################################\n\n");
}

PRIVATE void printMenu() {
	printf("List of available commands:\n");
	printf("./wavengine -list audio1.wav audio2.wav ... audioN.wav\n");
	printf("./wavengine -mono audio1.wav audio2.wav ... audioN.wav\n");
	printf("./wavengine -chop audio1.wav Xs Ys audio2.wav Xs Ys ... audioN.wav Xs Ys\n");
	printf("./wavengine -reverse audio1.wav audio2.wav ... audioN.wav\n");
}
