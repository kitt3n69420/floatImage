// #define _CRT_SECURE_NO_WARNINGS // If you atr using VC++, uncomment this.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct {
	float l[256];
	int ptr;
} stack;

void putst(stack *f, float v) {
	f->ptr++;
	f->l[f->ptr] = v;
}
void printst(stack f) {
	int i = 0;
	printf("stack : [ ");
	for (i = 0; i < f.ptr+1; i++) {
		printf("%f ", f.l[i]);
	}
	printf("]\n");
	return;
}
float popst(stack *f) {
	if (f->ptr > -1)f->ptr--;
	return f->l[f->ptr + 1];
}
float andf(float f1, float f2) {
	long long l1 = f1 * 8388608.0;
	long long l2 = f2 * 8388608.0;
	return (l1 & l2) / 8388608.0;
}

float orf(float f1, float f2) {
	long long l1 = f1 * 8388608.0;
	long long l2 = f2 * 8388608.0;
	return (l1 | l2) / 8388608.0;
}

float xorf(float f1, float f2) {
	long long l1 = f1 * 8388608.0;
	long long l2 = f2 * 8388608.0;
	return (l1 ^ l2) / 8388608.0;
}

float calcStr(char* s, stack * f, float x, float y) {

	f->ptr = -1;
	f->l[0] = 0;
	int i = 0;
	float ta = 0;
	float tb = 0;
	while (s[i]) {
		switch (s[i]) {
		case 'x':
			putst(f, x);
			break;
		case 'y':
			putst(f, y);
			break;

		case '0':
			putst(f, 0);
			break;
		case '1':
			putst(f, 1);
			break;
		case '2':
			putst(f, 2);
			break;
		case '3':
			putst(f, 3);
			break;
		case '4':
			putst(f, 4);
			break;
		case '5':
			putst(f, 5);
			break;
		case '6':
			putst(f, 6);
			break;
		case '7':
			putst(f, 7);
			break;
		case '8':
			putst(f, 8);
			break;
		case 'v':
			putst(f, -1);
			break;
		case 'f':
			putst(f, -2);
			break;
		case 'g':
			putst(f, -3);
			break;
		case 'h':
			putst(f, -4);
			break;
		case 'j':
			putst(f, -5);
			break;
		case 'k':
			putst(f, -6);
			break;
		case 'l':
			putst(f, -7);
			break;
		case '9':
			putst(f, -8 );
			break;
		case 'p':
			putst(f, popst(f) + popst(f));
			break;
		case 'z':
			putst(f, popst(f) - popst(f));
			break;
		case 'm':
			putst(f, popst(f) * popst(f));
			break;
		case 'd':
			ta = popst(f);
			tb = popst(f);
			
			putst(f, (tb == 0 ? 0.0: ta/tb));
			break;
		case 'w':
			putst(f, fmodf(popst(f) , popst(f)));
			break;
		case 'a':
			putst(f, andf(popst(f), popst(f)));
			break;
		case 'o':
			putst(f, orf(popst(f), popst(f)));
			break;
		case 'e':
			putst(f, xorf(popst(f), popst(f)));
			break;
		case 'q':
			putst(f, powf(popst(f), 2));
			break;
		case 'u':
			putst(f, powf(popst(f), 3));
			break;
		case 'r':
			putst(f, sqrt(popst(f)));
			break;
		case 'b':
			putst(f, cbrt(popst(f)));
			break;
		case 'n':
			putst(f, -1*(popst(f)));
			break;
		case 'i':
			ta = popst(f);
			putst(f, (ta == 0 ? 0 : 1/ta));
			break;
		case 's':
			putst(f, sinf(popst(f)));
			break;
		case 'c':
			putst(f, cosf(popst(f)));
			break;
		case 't':
			putst(f, tanf(popst(f)));
			break;
		}
		i++;
	}
	ta = popst(f);
	if (ta > 1)ta = 1;
	if (ta < -1)ta = -1;
	//printf("%f %f %f\n", x, y, ta);
	//printst(*f);
	return ta;
}
int main(void) {
	stack st;
	char nums[32] = "0123456789vfghjklxxxxyyyy6789kl5";
	char bops[8] = "pzmdwaeo";
	char uops[9] = "qrubinsct";
	unsigned char bmpHeader[54] = {
		0x42, 0x4D, 0x36, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00,
		0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02,
		0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	unsigned char* img = (char *)malloc(54 + 512 * 512 * 3);
	if (img == NULL)return -1;
	int i = 0;
	int j = 0;
	int k = 0;
	int v = 0;
	for (i = 0; i < 54; i++)img[i] = bmpHeader[i];
	int pos = 54;
	int x = 0;
	int y = 0;
	char strings[3][100] = {
		{0},
		{0},
		{0}
	};
	srand(time(NULL));
	int sr = 0;
	int sp = 0;
	int imgnum = 0;
	for (imgnum = 0; imgnum < 1000; imgnum++) {
		pos = 54;
		x = 0;
		y = 0;
		i = 0;
		j = 0;
		k = 0;
		v = 0;
		for (i = 0; i < 256; i++)st.l[i] = 0.0;
		st.ptr = 0;

		for (i = 0; i < 3; i++) {
			for (j = 0; j < 100; j++) {
				strings[i][j] = 0;
			}
		}
		for (i = 0; i < 3; i++) {
			sr = (rand() & 7) + 4;
			sp = 0;
			int rp = 0;
			strings[i][sp] = nums[rand() % 32];
			sp++;
			for (j = 0; j < sr; j++) {
				int sel = rand() & 1;
				if (sel) { //문자 2개 중간에 끼우기
					rp = rand() % (sp + 1);
					for (k = sp; k > rp - 1; k--)strings[i][k + 2] = strings[i][k];
					sp+=2;
					strings[i][rp] = nums[rand() % 32];
					strings[i][rp+1] = bops[rand() % 8];
				}
				else { //1개 끼우기
					rp = rand() % (sp + 1);
					for (k = sp; k > rp - 1; k--)strings[i][k + 1] = strings[i][k];
					sp += 1;
					strings[i][rp] = uops[rand() % 9];
				}
			}
		}
		for (x = 0; x < 512; x++) {
			for (y = 0; y < 512; y++) {
				v = ((1 + calcStr(strings[2], &st, x / 256.0 - 1, y / 256.0 - 1)) * 128);
				if (v < 0)v = 0;
				if (v > 255)v = 255;
				img[pos++] = v;
				v = ((1 + calcStr(strings[1], &st, x / 256.0 - 1, y / 256.0 - 1)) * 128);
				if (v < 0)v = 0;
				if (v > 255)v = 255;
				img[pos++] = v;
				v = ((1 + calcStr(strings[0], &st, x / 256.0 - 1, y / 256.0 - 1)) * 128);
				if (v < 0)v = 0;
				if (v > 255)v = 255;
				img[pos++] = v;
			}
		}
		printf("%d %s %s %s\n", imgnum, strings[0], strings[1], strings[2]);
		char b[100] = { 0 };
		sprintf(b, "images/%s_%s_%s.bmp", strings[0], strings[1], strings[2]);
		FILE* myImg = fopen(b, "wb");
		fwrite(img, 1, 54 + 512 * 512 * 3, myImg);
		fclose(myImg);
	}


	free(img);
	return 0;
}
