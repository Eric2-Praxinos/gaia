#pragma once

namespace nGaia {
namespace nEngine {

class Node {
public:
	/** Destructor */
	virtual ~Node() = 0;

	/** Constructor */
	Node(int iX, int iY, int iW, int iH);

public:
	int X() const;
	int Y() const;
	int Width() const;
	int Height() const;

public:
	virtual void Draw() const = 0;

private:
	//TODO: should become a shape
	int x;
	int y;
	int w;
	int h;
};

}
}