#include <terminal/renderer.hpp>
#include <terminal/resources.hpp>

#include <iostream>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Default frame unit", "[renderer]") {
	tren::init(2, 2);
	tren::FrameUnit* buff_ptr = tren::getBuffer();
	tren::FrameUnit* virt_buff_ptr = tren::getVirtualBuffer();
	tren::FrameUnit defaultUnit;

	CHECK(tren::getBufferWidth() == 2);
	CHECK(tren::getBufferHeight() == 2);

	for (int j = 0; j < tren::getBufferHeight(); j++)
	{
		for (int i = 0; i < tren::getBufferWidth(); i++)
		{
			int pos = i + j * tren::getBufferWidth();
			REQUIRE(buff_ptr[pos].m_char == defaultUnit.m_char);
			REQUIRE(virt_buff_ptr[pos].m_char == defaultUnit.m_char);
			REQUIRE(buff_ptr[pos].m_char == virt_buff_ptr[pos].m_char);
		}
	}
	
	tren::endwin();
}

TEST_CASE("Drawing text", "[renderer]") {
	tren::init(2, 2);

	tren::TextDef textDef;

	textDef.content = "He\nll";

	tren::drawText(textDef);

	tren::refresh();

	tren::FrameUnit* buff_ptr = tren::getBuffer();
	tren::FrameUnit* virt_buff_ptr = tren::getVirtualBuffer();

	int buff_size = tren::getBufferWidth() * tren::getBufferHeight();

	REQUIRE(buff_ptr[0].m_char == 'H');
	REQUIRE(buff_ptr[1].m_char == 'e');
	REQUIRE(buff_ptr[2].m_char == 'l');
	REQUIRE(buff_ptr[3].m_char == 'l');

	tren::endwin();
}

TEST_CASE("Drawing pixel", "[renderer]") {
	tren::init(2, 2);

	tren::PixelDef pixelDef;
	pixelDef.unit = tren::FrameUnit();
	pixelDef.unit.m_char = 'H';

	tren::drawPixel(pixelDef);

	pixelDef.unit = tren::FrameUnit();
	pixelDef.unit.m_char = 'e';
	pixelDef.x++;

	tren::drawPixel(pixelDef);

	pixelDef.unit = tren::FrameUnit();
	pixelDef.unit.m_char = 'l';
	pixelDef.y++;

	tren::drawPixel(pixelDef);

	tren::refresh();

	tren::FrameUnit* buff_ptr = tren::getBuffer();
	tren::FrameUnit* virt_buff_ptr = tren::getVirtualBuffer();

	int buff_size = tren::getBufferWidth() * tren::getBufferHeight();

	REQUIRE(buff_ptr[0].m_char == 'H');
	REQUIRE(buff_ptr[1].m_char == 'e');
	REQUIRE(buff_ptr[2].m_char == 0);
	REQUIRE(buff_ptr[3].m_char == 'l');

	tren::endwin();
}