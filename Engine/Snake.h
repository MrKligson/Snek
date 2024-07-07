#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "Board.h"
#include <vector>

class Snake
{
private:
	class Segment
	{
	public:
		Segment(const Location& l);
		Segment(const Location& l, int padding, Color c);
		void MoveBy(const Location& delta);
		void Follow(const Segment& next);
		void Draw(Board& brd) const;
		void SetColor(Color c);
		Color GetColor() const;
		const Location& GetLocation() const;
		void SetLocation(const Location& l);

	private:
		Location loc = { 0,0 };
		Color c;
		int padding = 1;
	};
	
public:
	Snake(Keyboard& kbd, const Board& brd);
	//Snake(Keyboard& kbd, const Board& brd, bool testSnake);
	bool IsPreparingToMove();
	bool Move(const Board& brd);
	Location GetHeadLocation() const;
	bool IsInLocation(const Location& l, int skipNTailSegments) const;
	void Grow();
	bool CanGrow() const;
	size_t Size();
	void Draw(Board& brd) const;
	void RotateColors();
private:
	void HandleInput();

private:
	static constexpr Color headColor = Colors::Yellow;
	const Color bodycolors[4] = {
		{ 159, 230, 77 },
		{ 215, 230, 77 },
		{ 159, 230, 77 },
		{ 44, 253, 51 }
	};
	std::vector<Segment> segments;
	const int maxSegments;
	Location tailPrevious;
	int moveCounter = 0;
	static constexpr int movePeriod = 20;
	Location moveDelta = { 1, 0 };
	Keyboard& kbd;
};