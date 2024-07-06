#include "Snake.h"
#include <assert.h>

Snake::Snake(Keyboard& kbd, Location head)
	:
	kbd(kbd)
{
	kbd.DisableAutorepeat();

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

bool Snake::IsNotMoving()
{
	moveCounter++;
	if (nSegments == nSegmentsMax || moveCounter < movePeriod) {
		return true;
	}

	moveCounter = 0;
	HandleInput();
	return false;
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

bool Snake::IsInLocation(const Location& l, int skipNTailSegments) const
{
	for (int i = 0; i < nSegments - skipNTailSegments; i++) {
		if (segments[i].GetLocation() == l) {
			return true;
		}
	}
	return false;
}

bool Snake::Grow()
{
	nSegments++;
	return nSegments < nSegmentsMax;
}

void Snake::Draw(Board& brd) const
{
	for (int i = 1; i < nSegments; i++) {
		segments[i].Draw(brd);
	}
	segments[0].Draw(brd);
}

void Snake::RotateColors()
{
	if (nSegments < nSegmentsMax) {
		// lost, not won... No partylights!
		return;
	}

	moveCounter++;
	if (!(moveCounter % 5)) {
		return;
	}

	for (int i = 2; i < nSegments; i++) {
		segments[i].SetColor(segments[i - 1].GetColor());
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
			return;
		}
		if (key == VK_DOWN && moveDelta.y != -1) {
			moveDelta = { 0, 1 };
			return;
		}
		if (key == VK_LEFT && moveDelta.x != 1) {
			moveDelta = { -1, 0 };
			return;
		}
		if (key == VK_RIGHT && moveDelta.x != -1) {
			moveDelta = { 1, 0 };
			return;
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

void Snake::Segment::SetColor(Color c)
{
	assert(isInitialized);
	this->c = c;
}

Color Snake::Segment::GetColor() const
{
	assert(isInitialized);
	return c;
}

const Location& Snake::Segment::GetLocation() const
{
	assert(isInitialized);
	return loc;
}
