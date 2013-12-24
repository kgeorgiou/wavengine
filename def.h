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

#ifndef DEF_H_
#define DEF_H_

/* Define public and private modifiers to use on functions */
#define PUBLIC
#define PRIVATE static

/* Library Inclusion */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define byte, word and dword types */
typedef unsigned char byte;
typedef unsigned short int word;
typedef unsigned int dword;

typedef struct {
	byte id[4];
	dword size;
	byte format[4];
}__attribute__((packed)) RIFFHEADER;

typedef struct {
	byte id[4];
	dword size;
	word audioFormat;
	word numChannels;
	dword sampleRate;
	dword byteRate;
	word blockAlign;
	word bitsPerSample;
}__attribute__((packed)) FMTHEADER;

typedef struct {
	byte id[4];
	dword size;
}__attribute__((packed)) DATAHEADER;

/* Main functions of the wavengine*/
PUBLIC int list(char *filename);
PUBLIC int mono(char *filename);
PUBLIC int chop(char *filename, int start, int end);
PUBLIC int reverse(char *filename);
// TODO: PUBLIC int similarity(char *filename, char *filename2);

/* Auxiliary functions */
PUBLIC int readRiffHeader(FILE *fp, RIFFHEADER **riff_header);
PUBLIC int writeRiffHeader(FILE *fp_out, RIFFHEADER *riff_header);

PUBLIC int readFmtHeader(FILE *fp, FMTHEADER **fmt_header);
PUBLIC int writeFmtHeader(FILE *fp_out, FMTHEADER *fmt_header);

PUBLIC int readDataHeader(FILE *fp, DATAHEADER **data_header);
PUBLIC int writeDataHeader(FILE *fp, DATAHEADER *data_header);

PUBLIC int readAudio(FILE *fp, byte **audio_in, int size);

#endif /* DEF_H_ */
