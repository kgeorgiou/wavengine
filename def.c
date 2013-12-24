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

PUBLIC int readRiffHeader(FILE *fp, RIFFHEADER **riff_header) {

	// Allocate memory for the RIFF header
	if ((*riff_header = (RIFFHEADER *) malloc(sizeof(RIFFHEADER))) == NULL ) {
		printf("Error: Not enough memory allocated for RIFF header\n");
		fclose(fp);
		return EXIT_FAILURE;
	}
	if (fread(*riff_header, sizeof(RIFFHEADER), 1, fp) < 1) {
		printf("Error: Information missing from file\n");
		fclose(fp);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

PUBLIC int writeRiffHeader(FILE *fp_out, RIFFHEADER *riff_header) {
	if ((fwrite(riff_header, sizeof(RIFFHEADER), 1, fp_out)) < 1) {
		printf("Error, data omissions while writing RIFF header in file\n");
		fclose(fp_out);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

PUBLIC int readFmtHeader(FILE *fp, FMTHEADER **fmt_header) {

	// Allocate memory for the RIFF header
	if ((*fmt_header = (FMTHEADER *) malloc(sizeof(FMTHEADER))) == NULL ) {
		printf("Error: Not enough memory allocated for RIFF header\n");
		fclose(fp);
		return EXIT_FAILURE;
	}
	if (fread(*fmt_header, sizeof(FMTHEADER), 1, fp) < 1) {
		printf("Error: Information missing from file\n");
		fclose(fp);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

PUBLIC int writeFmtHeader(FILE *fp_out, FMTHEADER *fmt_header) {
	if ((fwrite(fmt_header, sizeof(FMTHEADER), 1, fp_out)) < 1) {
		printf("Error, data omissions while writing RIFF header in file\n");
		fclose(fp_out);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

PUBLIC int readDataHeader(FILE *fp, DATAHEADER **data_header) {

	// Allocate memory for the RIFF header
	if ((*data_header = (DATAHEADER *) malloc(sizeof(DATAHEADER))) == NULL ) {
		printf("Error: Not enough memory allocated for RIFF header\n");
		fclose(fp);
		return EXIT_FAILURE;
	}
	if (fread(*data_header, sizeof(DATAHEADER), 1, fp) < 1) {
		printf("Error: Information missing from file\n");
		fclose(fp);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

PUBLIC int writeDataHeader(FILE *fp_out, DATAHEADER *data_header) {
	if ((fwrite(data_header, sizeof(DATAHEADER), 1, fp_out)) < 1) {
		printf("Error, data omissions while writing RIFF header in file\n");
		fclose(fp_out);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

PUBLIC int readAudio(FILE *fp, byte **audio_in, int size) {

	// Allocate memory for the actual audio data
	if ((*audio_in = (byte *) malloc(size)) == NULL ) {
		printf("Error, unable to allocate memory for audio data\n");
		fclose(fp);
		return EXIT_FAILURE;
	}
	if (fread(*audio_in, size, 1, fp) < 1) {
		printf("Error: Unable to read audio data from file\n");
		fclose(fp);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

