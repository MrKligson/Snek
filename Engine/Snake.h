#pragma once

#include "Graphics.h"
#include "Keyboard.h"
#include "Board.h"

class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& l);
		void InitBody(int padding, Color c);
		void MoveBy(const Location& delta);
		void Follow(const Segment& next);
		void Draw(Board& brd) const;
		const Location& GetLocation() const;

	private:
		Location loc = { 0,0 };
		Color c;
		int padding = 1;
		bool isInitialized = false;
	};
	
public:
	Snake(Keyboard& kbd, Location head);
	bool WillMove();
	void Move();
	Location GetNextHeadLocation() const;
	bool IsInLocation(const Location& l, int skipNTailSegments) const;
	bool Grow();
	void Draw(Board& brd) const;
private:
	void HandleInput();

private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr int nSegmentsMax = Board::cols * Board::rows;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
	int moveCounter = 0;
	static constexpr int movePeriod = 20;
	Location moveDelta = { 0, 1 };
	Keyboard& kbd;
};