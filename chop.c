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

PRIVATE int max(int a, int b);
PRIVATE int min(int a, int b);

PUBLIC int chop(char *filename, int start, int end) {

	if(end < start) {
		printf("Invalid parameters, end point can't be less than start point.\n");
		return EXIT_FAILURE;
	}

	FILE *fp;
	FILE *fp_out;

	char *filename_out;

	// Open wav file
	if ((fp = fopen(filename, "rb")) == NULL ) {
		printf("Error: Unable to open file %s\n", filename);
		return EXIT_FAILURE;
	}

	RIFFHEADER *riff_header;
	FMTHEADER *fmt_header;
	DATAHEADER *data_header;
	byte *audio_in;

	/**
	 * Read headers
	 */
	if (readRiffHeader(fp, &riff_header) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	if (readFmtHeader(fp, &fmt_header) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	if (readDataHeader(fp, &data_header) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	int totalSeconds = data_header->size / fmt_header->byteRate;

	// If start is negative, set it to zero
	start = max(0, start);
	// If end exceeds the total length, set it to the last second
	end = min(totalSeconds, end);

	// End if end point is less than the start point
	if(start > totalSeconds) {
		printf("Start point is out of audio's bounds.\n");
		fclose(fp);
		return EXIT_FAILURE;
	}

	// Read audio
	if (readAudio(fp, &audio_in, data_header->size) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	fclose(fp);

	if ((filename_out = (char *) malloc(strlen(filename) + 5)) == NULL ) {
		printf("Error, unable to allocate memory for output filename\n");
		return EXIT_FAILURE;
	}

	strcpy(filename_out, "chop-");
	strcat(filename_out, filename);

	if ((fp_out = fopen(filename_out, "wb")) == NULL ) {
		printf("Error, unable to create file %s\n", filename_out);
		fclose(fp);
		return EXIT_FAILURE;
	}

	// Calculate byte to begin chopping from
	int chopFrom = start * fmt_header->byteRate;
	// Calculate chop length
	int chopSize = (end - start) * fmt_header->byteRate;

	// Update headers accordingly
	riff_header->size = riff_header->size - data_header->size;
	data_header->size = chopSize;
	riff_header->size = riff_header->size + data_header->size;

	/**
	 * Write headers
	 */
	if (writeRiffHeader(fp_out, riff_header) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	if (writeFmtHeader(fp_out, fmt_header) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	if (writeDataHeader(fp_out, data_header) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	// Write chopped part in the new file
	if(fwrite(&audio_in[chopFrom], chopSize, 1, fp_out) < 1) {
		printf("Error, data omissions while writing mono data in file %s\n",
				filename_out);
		fclose(fp_out);
		return EXIT_FAILURE;
	}

	/**
	 * Free resources
	 */
	fclose(fp_out);
	free(audio_in);
	free(riff_header);
	free(fmt_header);
	free(data_header);
	free(filename_out);

	return EXIT_SUCCESS;
}

PRIVATE int max(int a, int b) {
	if(a > b) {
		return a;
	}
	return b;
}

PRIVATE int min(int a, int b) {
	if(a < b) {
		return a;
	}
	return b;
}

