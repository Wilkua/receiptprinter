#include "Receipt.h"
#include "escpos.h"

namespace RP {

Receipt & Receipt::align_text(uint8_t n) {
    char buf[] {ESC, 'a', static_cast<char>(n)};
    m_data.write(buf, 3);

    return *this;
}

Receipt & Receipt::barcode(uint8_t mode, const std::string &data) {
    // uint8_t n = std::strlen(s);
    char buf[] = {GS, 'k', static_cast<char>(mode), static_cast<char>(data.size())};
    m_data.write(buf, 4);
    m_data << data;

    return *this;
}

Receipt & Receipt::barcode(uint8_t mode, const void *data, size_t size) {
    char buf[] = {GS, 'k', static_cast<char>(mode), static_cast<char>(size)};
    m_data.write(buf, 4);
    m_data.write(reinterpret_cast<const char *>(data), size);

    return *this;
}

Receipt & Receipt::barcode_height(uint8_t n) {
    char buf[] = {GS, 'h', static_cast<char>(n)};
    m_data.write(buf, 3);

    return *this;
}

Receipt & Receipt::barcode_hri_font(uint8_t n) {
    char buf[] {GS, 'f', static_cast<char>(n)};
    m_data.write(buf, 3);

    return *this;
}

Receipt & Receipt::barcode_hri_pos(uint8_t n) {
    char buf[] {GS, 'H', static_cast<char>(n)};
    m_data.write(buf, 3);

    return *this;
}

Receipt & Receipt::barcode_width(uint8_t n) {
    char buf[] {GS, 'w', static_cast<char>(n)};
    m_data.write(buf, 3);

    return *this;
}

Receipt & Receipt::character_font(uint8_t n) {
    char buf[] {ESC, 'M', static_cast<char>(n)};
    m_data.write(buf, 3);

    return *this;
}

Receipt & Receipt::feed_and_cut() {
    const char buf[] = {GS, 'V', 66, 0};
    m_data.write(buf, 4);

    return *this;
}

Receipt & Receipt::feed_lines(uint8_t n) {
    char buf[] {ESC, 'd', static_cast<char>(n)};
    m_data.write(buf, 3);

    return *this;
}

Receipt & Receipt::font_attributes(uint8_t n) {
    char buf[] {ESC, '!', static_cast<char>(n)};
    m_data.write(buf, 3);

    return *this;
}

Receipt & Receipt::font_magnification(uint8_t n) {
    char buf[] {GS, '!', static_cast<char>(n)};
    m_data.write(buf, 3);

    return *this;
}

std::string Receipt::output() const {
    return m_data.str();
}

Receipt & Receipt::reset() {
    const char buf[] {ESC, '@', ESC, 2};
    m_data.write(buf, 4);

    return *this;
}

Receipt & Receipt::text(const std::string &txt) {
    m_data << txt;

    return *this;
}

Receipt & Receipt::text_line(const std::string &txt) {
    m_data << txt << CR << LF;

    return *this;
}

} // namespace RP
