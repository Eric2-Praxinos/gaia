class Node;

namespace nGaia {
namespace nEngine {

class Window {
public:
	~Window();
	Window(int iX, int iY, int iW, int iH);

public:
	int X() const;
	int Y() const;
	int W() const;
	int H() const;

public:
	const Node* Node() const;

private:
	const ::Node* node;
};

}
}