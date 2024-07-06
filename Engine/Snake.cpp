#include "Snake.h"
#include <assert.h>

Snake::Snake(Keyboard& kbd, Location head)
	:
	kbd(kbd)
{
	segments[0].InitHead(head);

	Color bodycolors[] = {
		{ 159, 230, 77 },
		{ 215, 230, 77 },
		{ 159, 230, 77 },
		{ 44, 253, 51 }
	};

	for (int i = 1; i < nSegmentsMax; i++) {
		segments[i].InitBody(i % 2 + 2, bodycolors[i % 4]);
	}
}

bool Snake::WillMove()
{
	moveCounter++;
	if (nSegments == nSegmentsMax || moveCounter < movePeriod) {
		return false;
	}

	moveCounter = 0;
	HandleInput();
	return true;
}

void Snake::Move()
{
	if (nSegments >= nSegmentsMax) {
		return;
	}

	for (int i = nSegments; i > 0; i--) {
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(moveDelta);
}

Location Snake::GetNextHeadLocation() const
{
	return segments[0].GetLocation() + moveDelta;
}

bool Snake::IsHeadAt(const Location& l) const
{
	return segments[0].GetLocation() == l;
}

bool Snake::Grow()
{
	nSegments++;
	return nSegments < nSegmentsMax;
}

void Snake::Draw(Board& brd) const
{
	for each (Segment s in segments) {
		s.Draw(brd);
	}
}

void Snake::HandleInput()
{
	while (!kbd.KeyIsEmpty()) {
		const Keyboard::Event event = kbd.ReadKey();

		if (!event.IsPress()) {
			continue;
		}

		const UCHAR key = event.GetCode();
		if (key == VK_UP && moveDelta.y != 1) {
			moveDelta = { 0, -1 };
		}
		else if (key == VK_DOWN && moveDelta.y != -1) {
			moveDelta = { 0, 1 };
		}
		else if (key == VK_LEFT && moveDelta.x != 1) {
			moveDelta = { -1, 0 };
		}
		else if (key == VK_RIGHT && moveDelta.x != -1) {
			moveDelta = { 1, 0 };
		}
	}
}

void Snake::Segment::InitHead(const Location& l)
{
	assert(isInitialized == false);
	c = Snake::headColor;
	loc = l;
	isInitialized = true;
}

void Snake::Segment::InitBody(int padding, Color c)
{
	assert(isInitialized == false);
	this->c = c;
	this->padding = padding;
	isInitialized = true;
}

void Snake::Segment::MoveBy(const Location& delta)
{
	assert(isInitialized);
	loc = loc + delta;
}

void Snake::Segment::Follow(const Segment& next)
{
	assert(isInitialized);
	loc = next.GetLocation();
}

void Snake::Segment::Draw(Board& brd) const
{
	assert(isInitialized);
	brd.DrawCell(loc, padding, c);
}

const Location& Snake::Segment::GetLocation() const
{
	assert(isInitialized);
	return loc;
}
