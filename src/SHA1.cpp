#include "SHA1/SHA1.h"
#include <iostream>
#include <iomanip>

SHA1::SHA1() {
	Kt = new unsigned int[4] {0X5A827999, 0X6ED9EBA1, 0X8F1BBCDC, 0XCA62C1D6};
	Hn = new unsigned int[5] {0X67452301, 0XEFCDAB89, 0X98BADCFE, 0X10325476, 0XC3D2E1F0};
	A = Hn[0], B = Hn[1], C = Hn[2], D = Hn[3], E = Hn[4];
	t = 0;
}

unsigned int *SHA1::update(unsigned char *message) {
	Wn = (unsigned int*)message;
	while (t < 80) {
		oneRound();
		t++;
	}
	Hn[0] += A;
	Hn[1] += B;
	Hn[2] += C;
	Hn[3] += D;
	Hn[4] += E;
	return Hn;
}

void SHA1::oneRound() {
	s = t & MASK;
	quarter = t * 4 / 80;
	if (t >= 16) {
		Wn[s] = circularLeftShift(Wn[(s + 13) & MASK] ^ Wn[(s + 8) & MASK] ^ Wn[(s + 2) & MASK] ^ Wn[s], 1);
	}
	temp = circularLeftShift(A, 5) + bitWiseFunction(B, C, D) + E + Wn[s] + Kt[quarter];
	E = D;
	D = C;
	C = circularLeftShift(B, 30);
	B = A;
	A = temp;
	std::cout << std::hex << std::setw(9) << A << ' ' << std::setw(9) << B << ' ' << std::setw(9) << C << ' ' << std::setw(9) << D << ' ' << std::setw(9) << E << ' ' << std::setw(9) << t << ' ' << std::setw(9) << quarter << std::endl;
}

unsigned int SHA1::bitWiseFunction(unsigned int B, unsigned int C, unsigned int D) {
	switch (quarter)
	{
	case 0:
		return ((B & C) | (~B & D));
	case 1:
		return (B ^ C ^ D);
	case 2:
		return ((B & C) | (B & D) | (C & D));
	case 3:
		return (B ^ C ^ D);
	default:
		break;
	}
}

unsigned int SHA1::circularLeftShift(unsigned int num, int shift) {
	num = (num << shift) | (num >> (32 - shift));
	return num;
}