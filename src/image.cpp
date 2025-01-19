#include "image.hpp"

#include <fstream>

Image::Image() : m_width(0), m_height(0)
{
}

Image::Image(std::string path) : Image() {
    if (path_exists(path)) {
        read(path);
    }
    else {
        std::string msg = "Cannot open image: ";
        msg += path;
        throw std::exception(msg.c_str());
    }
}

Image::~Image() {
    // Clear colors
    /*for (auto& u : m_frame_units) {
        u.destroy_colors();
    }*/
}

void Image::load(std::string path)
{
    if (!path_exists(path)) {
        std::string msg = "Cannot open image: ";
        msg += path;
        throw std::exception(msg.c_str());
    }
    read(path);
}

void Image::read(std::string path) {
    std::ifstream f;
    f.open(path, std::ios::binary);
    if (f.fail()) {
        f.close();
        return;
    }

    // Read image size

    f.read(reinterpret_cast<char*>(&m_width), sizeof m_width);
    f.read(reinterpret_cast<char*>(&m_height), sizeof m_height);

    // Read image data

    for (int j = 0; j < m_height; j++) {
        for (int i = 0; i < m_width; i++) {
            color bg_col;
            color fg_col;
            unsigned char ch = 0;

            f.read(reinterpret_cast<char*>(&ch), sizeof ch);
            // background
            f.read(reinterpret_cast<char*>(&bg_col), sizeof color);
            // foreground
            f.read(reinterpret_cast<char*>(&fg_col), sizeof color);

            m_frame_units.push_back(FrameUnit(ch, bg_col, fg_col, i, j));
        }
    }

    f.close();
}

bool Image::path_exists(std::string p) {
    std::ifstream f;
    f.open(p, std::ios::binary);
    if (f.fail()) {
        f.close();
        return false;
    }
    f.close();
    return true;
}

std::vector<FrameUnit> Image::get_frame_units() const {
    return m_frame_units;
}

unsigned int Image::get_width() const {
    return m_width;
}

unsigned int Image::get_height() const {
    return m_height;
}