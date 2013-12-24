/**
 * list.c includes functions to display a WAV sound's headers (metadata)
 *
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

PUBLIC int list(char *filename) {

	FILE *fp;

	// Open wav file
	if ((fp = fopen(filename, "rb")) == NULL ) {
		printf("Error: Unable to open file %s\n", filename);
		return EXIT_FAILURE;
	}

	RIFFHEADER *riff_header;
	FMTHEADER *fmt_header;
	DATAHEADER *data_header;

	/**
	 * Read headers
	 */
	if(readRiffHeader(fp, &riff_header) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	if(readFmtHeader(fp, &fmt_header) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}
	if(readDataHeader(fp, &data_header) == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	printf("\nFile: %s\n", filename);
	printf("--------------------\n");
	printf("RIFF_CHUNK_HEADER\n");
	printf("=================\n");
	printf("chunkID: %.*s\n", sizeof(riff_header->id), riff_header->id);
	printf("chunkSize: %d\n", riff_header->size);
	printf("format: %.*s\n", sizeof(riff_header->format), riff_header->format);
	printf("\n");
	printf("FMT_SUBCHUNK_HEADER\n");
	printf("===================\n");
	printf("subChunk1ID: %.*s\n", sizeof(fmt_header->id), fmt_header->id);
	printf("subChunk1Size: %d\n", fmt_header->size);
	printf("audioFormat: %hu\n", fmt_header->audioFormat);
	printf("numChannels: %hu\n", fmt_header->numChannels);
	printf("sampleRate: %d\n", fmt_header->sampleRate);
	printf("byteRate: %d\n", fmt_header->byteRate);
	printf("blockAlign: %hu\n", fmt_header->blockAlign);
	printf("bitsPerSample: %hu\n", fmt_header->bitsPerSample);
	printf("\n");
	printf("DATA_SUBCHUNK_HEADER\n");
	printf("====================\n");
	printf("subChunk2ID: %.*s\n", sizeof(data_header->id), data_header->id);
	printf("subChunk2Size: %d\n\n", data_header->size);

	/**
	 * Free resources
	 */
	free(riff_header);
	free(fmt_header);
	free(data_header);

	fclose(fp);

	return EXIT_SUCCESS;
}
