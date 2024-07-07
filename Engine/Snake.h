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
		void SetColor(Color c);
		Color GetColor() const;
		const Location& GetLocation() const;

	private:
		Location loc = { 0,0 };
		Color c;
		int padding = 1;
		bool isInitialized = false;
	};
	
public:
	Snake(Keyboard& kbd, Location head);
	bool IsNotMoving();
	bool Move(const Board& brd);
	Location GetHeadLocation() const;
	bool IsInLocation(const Location& l, int skipNTailSegments) const;
	bool Grow();
	void Draw(Board& brd) const;
	void RotateColors();
private:
	void HandleInput();

private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr int nSegmentsMax = Board::GetCellAmount();
	Segment segments[nSegmentsMax];
	int nSegments = 1;
	int moveCounter = 0;
	static constexpr int movePeriod = 20;
	Location moveDelta = { 0, 1 };
	Keyboard& kbd;
};