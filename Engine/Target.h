#pragma once

#include "Snake.h"
#include <random>

class Target
{
public:
	Target(std::mt19937& rng, std::uniform_int_distribution<int>& vdist,
		   std::uniform_int_distribution<int>& hdist, const Snake& snek);
	void Respawn(const Snake& snek);
	bool IsAt(const Location& l) const;
private:
	Location loc = { 0, 0 };
	std::mt19937& rng;
	std::uniform_int_distribution<int>& vdist;
	std::uniform_int_distribution<int>& hdist;
};