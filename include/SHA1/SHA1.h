#pragma once
#ifndef SHA1_H
#define SHA1_H

#define MASK 0XF

class SHA1
{
public:
	int t, s, quarter;
	unsigned int *Kt, *Hn, *Wn, temp, A, B, C, D, E;
	SHA1();
	unsigned int *update(unsigned char *Message);
	unsigned int circularLeftShift(unsigned int num, int shift);
	unsigned int bitWiseFunction(unsigned int B, unsigned int C, unsigned int D);
	void oneRound();
};

#endif // !SHA1_H