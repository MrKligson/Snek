#include "Target.h"

Target::Target(std::mt19937& rng, std::uniform_int_distribution<int>& vdist, std::uniform_int_distribution<int>& hdist)
	:
	rng(rng),
	vdist(vdist),
	hdist(hdist)
{
}

void Target::Respawn(const Snake& snek)
{
	do {
		loc = { vdist(rng), hdist(rng) };
	} while (snek.IsInLocation(loc, 0));
}

bool Target::IsAt(const Location& l) const
{
	return loc == l;
}

void Target::Draw(Board& brd) const
{
	brd.DrawCell(loc, 0, Colors::Red);
}
