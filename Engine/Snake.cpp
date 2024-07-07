#include "Snake.h"
#include <assert.h>

Snake::Snake(Keyboard& kbd, const Board& brd)
	:
	kbd(kbd),
	maxSegments(brd.Size()),
	tailPrevious({ 0,0 })
{
	kbd.DisableAutorepeat();

	segments.reserve(maxSegments);
	segments.push_back(Segment(Location(brd.GetCols() / 2, brd.GetRows() / 2)));
}

//Snake::Snake(Keyboard& kbd, const Board& brd, bool testSnake)
//	: Snake(kbd, brd)
//{
//	segments[0].SetLocation({ 0,0 });
//	const int xMax = brd.GetCols() - 1;
//	for (int y = 0; y < brd.GetRows(); y++) {
//		for (int x = 0; x < brd.GetCols(); x++) {
//			if (x + y == 0) continue;
//			tailPrevious = { y % 2 ? xMax - x : x, y};
//			Grow();
//		}
//	}
//}

bool Snake::IsPreparingToMove()
{
	moveCounter++;
	if (moveCounter < movePeriod) {
		return false;
	}

	moveCounter = 0;
	return true;
}

bool Snake::Move(const Board& brd)
{
	HandleInput();

	const Location next = segments[0].GetLocation() + moveDelta;
	if (!brd.IsValid(next)) {
		return false;
	}

	tailPrevious = segments.back().GetLocation();

	bool alive = true;
	for (size_t i = segments.size() - 1; i > 0; i--) {
		segments[i].Follow(segments[i - 1]);
		if (alive && segments.size() > 3 && i < segments.size()) {
			alive = segments[i].GetLocation() != next;
		}
	}
	segments[0].MoveBy(moveDelta);
	return alive;
}

Location Snake::GetHeadLocation() const
{
	return segments[0].GetLocation();
}

bool Snake::IsInLocation(const Location& l, int tailSegmentsToSkip) const
{
	for (size_t i = 0; i < segments.size() - tailSegmentsToSkip; i++) {
		if (segments[i].GetLocation() == l) {
			return true;
		}
	}
	return false;
}

void Snake::Grow()
{
	const size_t i = segments.size();
	segments.push_back(Segment(tailPrevious, 2 + i % 2, bodycolors[i % 4]));
}

bool Snake::CanGrow() const
{
	return segments.size() < maxSegments;
}

size_t Snake::Size()
{
	return segments.size();
}

void Snake::Draw(Board& brd) const
{
	for (size_t i = 1; i < segments.size(); i++) {
		segments[i].Draw(brd);
	}
	segments[0].Draw(brd);
}

void Snake::RotateColors()
{
	moveCounter++;
	if (moveCounter % 5) {
		return;
	}

	size_t i;
	for (i = 2; i < segments.size(); i++) {
		segments[i - 1].SetColor(segments[i].GetColor());
	}
	segments[i - 1].SetColor(segments[1].GetColor());
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

Snake::Segment::Segment(const Location& l)
	:
	loc(l),
	c(Snake::headColor)
{
}

Snake::Segment::Segment(const Location& l, int padding, Color c)
	:
	loc(l),
	c(c),
	padding(padding)
{
}

void Snake::Segment::MoveBy(const Location& delta)
{
	loc = loc + delta;
}

void Snake::Segment::Follow(const Segment& next)
{
	loc = next.GetLocation();
}

void Snake::Segment::Draw(Board& brd) const
{
	brd.DrawCell(loc, padding, c);
}

void Snake::Segment::SetColor(Color c)
{
	this->c = c;
}

Color Snake::Segment::GetColor() const
{
	return c;
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}

void Snake::Segment::SetLocation(const Location& l)
{
	loc = l;
}
