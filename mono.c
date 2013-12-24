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

PUBLIC int mono(char *filename) {

	FILE *fp;
	FILE *fp_out;

	RIFFHEADER *riff_header;
	FMTHEADER *fmt_header;
	DATAHEADER *data_header;

	byte *audio_in;

	int i = 0;

	char *filename_out;

	// Open wav file
	if ((fp = fopen(filename, "rb")) == NULL ) {
		printf("Error: Unable to open file %s\n", filename);
		return EXIT_FAILURE;
	}

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

	// Check if audio given is already a mono sound
	if (fmt_header->numChannels < 2) {
		printf("File %s is already a mono sound\n", filename);
		fclose(fp);
		return EXIT_SUCCESS;
	}

	// Check if audio has more than 2 channels
	if (fmt_header->numChannels > 2) {
		printf("File %s has more than 2 channels\n", filename);
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

	strcpy(filename_out, "mono-");
	strcat(filename_out, filename);

	// Adjust the size indicators in headers
	int originalTotalSize = data_header->size;
	data_header->size = data_header->size / 2;
	riff_header->size = riff_header->size - data_header->size;

	// Adjust bytes per sample and number of channels in headers.
	// Also store some of the variables that will help in extracting the new audio
	int bytesPerSamplePerChannel = fmt_header->bitsPerSample / 8;
	int bytesPerSample = bytesPerSamplePerChannel * 2;
	fmt_header->blockAlign = fmt_header->blockAlign / 2;
	fmt_header->byteRate = fmt_header->byteRate / 2;
	fmt_header->numChannels = 1;

	if ((fp_out = fopen(filename_out, "wb")) == NULL ) {
		printf("Error, unable to create file %s\n", filename_out);
		fclose(fp);
		return EXIT_FAILURE;
	}

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

	// Writes new audio data, skipping the right channel of the original track
	for (i = 0; i < originalTotalSize; i += bytesPerSample) {
		if (fwrite(&audio_in[i], bytesPerSamplePerChannel, 1, fp_out) < 1) {
			printf("Error, data omissions while writing mono data in file %s\n",
					filename_out);
			fclose(fp_out);
			return EXIT_FAILURE;
		}
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

