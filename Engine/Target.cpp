#include "Target.h"

Target::Target(std::mt19937& rng, std::uniform_int_distribution<int>& vdist,
	           std::uniform_int_distribution<int>& hdist, const Snake& snek)
	:
	rng(rng),
	vdist(vdist),
	hdist(hdist)
{
	Respawn(snek);
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
