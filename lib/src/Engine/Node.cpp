#include "Node.h"

namespace nGaia {
namespace nEngine {

Node::~Node()
{

}

Node::Node(int iX, int iY, int iW, int iH) :
	x(iX),
	y(iY),
	w(iW),
	h(iH)
{

}

int
Node::X() const {
	return x;
}

int
Node::Y() const {
	return y;
}

int
Node::Width() const {
	return w;
}

int
Node::Height() const {
	return h;
}

}
}