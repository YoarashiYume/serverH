#include "Randomizer.h"

void Randomizer::checkRange()
{
	if (from > to)
		from ^= to ^= from ^= to;
}

Randomizer::Randomizer()
{
	generator.seed(time(0));
	from = 0;
	to = 1;
}

Randomizer::Randomizer(int from_, int to_)
{
	generator.seed(time(0));
	from = from_;
	to = to_;
	checkRange();
}

int Randomizer::getRandomValue()
{
	std::uniform_int_distribution<int> range(from, to);
	return range(generator);
}

void Randomizer::setRange(int from_, int to_)
{
	from = from_;
	to = to_;
	checkRange();
}

void Randomizer::changeSeed(int v1, int v2)
{
	generator.seed(v1*time(0)/v2);
}