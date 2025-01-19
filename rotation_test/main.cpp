#include <iostream>
#include <tren/renderer.hpp>
#include <tren/utils.hpp>

int main() {
	std::cout << "Hello world!\n";

	tren::init();
	tren::attrOn(ATTR_ALT_SCREEN);
	tren::raw(true);

	float angle = 0;

	int x = 3;

	while (true) {
		char ch = std::cin.get();

		if (ch == 'q') {
			break;
		}

		tren::clear();

		std::string info = "Angle: " + std::to_string(angle);

		tren::drawText(1, 1, info.c_str());

		angle += ch == '<' ? -1 : ch == '>' ? 1 : 0;
		//x += ch == ',' ? -1 : ch == '.' ? 1 : 0;



		tren::drawRectFilled(10, 10, x, 3, '#');
		tren::drawRectRotated(5, 2, 4, 4, angle * 3.14 / 180);

		tren::refresh();
	}

	tren::raw(false);
	tren::attrOff(ATTR_ALT_SCREEN);
	tren::endwin();

	return 0;
}