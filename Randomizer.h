#ifndef _RANDOMIZER_H_

#define _RANDOMIZER_H_
/*
 * Just randomizer.
 * Exists for example only
 * */
#include <random>
#include <chrono>


class Randomizer
{
private:
	std::default_random_engine generator;
	int from, to;
	void checkRange();
public:
	Randomizer();
	Randomizer(int from_, int to_);
	int getRandomValue();
	void setRange(int from_,int to_);
	void changeSeed(int v1, int v2);
};

#endif
