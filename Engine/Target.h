#pragma once

#include "Snake.h"
#include "Board.h"
#include <random>

class Target
{
public:
	Target(std::mt19937& rng, std::uniform_int_distribution<int>& vdist, std::uniform_int_distribution<int>& hdist);
	void Respawn(const Snake& snek);
	bool IsAt(const Location& l) const;
	void Draw(Board& brd) const;
private:
	Location loc = { 0, 0 };
	std::mt19937& rng;
	std::uniform_int_distribution<int>& vdist;
	std::uniform_int_distribution<int>& hdist;
};