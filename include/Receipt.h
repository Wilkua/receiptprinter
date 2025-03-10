#ifndef _RECEIPT_H_
#define _RECEIPT_H_

#include <stdint.h>
#include <sstream>
#include <string>

namespace RP {

/// Receipt is an opaque token for storing arbitrary structs
/// representing receipt items. These are implementation dependenct.
class Receipt {
    std::stringstream m_data;

public:
    Receipt() { reset(); }

    Receipt & align_text(uint8_t n);
    Receipt & barcode(uint8_t mode, const std::string &data);
    Receipt & barcode(uint8_t mode, const void *data, size_t size);
    Receipt & barcode_height(uint8_t n);
    Receipt & barcode_hri_font(uint8_t n);
    Receipt & barcode_hri_pos(uint8_t n);
    Receipt & barcode_width(uint8_t n);
    Receipt & character_font(uint8_t n);
    Receipt & feed_and_cut();
    Receipt & feed_lines(uint8_t num);
    Receipt & font_attributes(uint8_t n);
    Receipt & font_magnification(uint8_t n);
    std::string output() const;
    Receipt & reset();
    Receipt & text(const std::string &txt);
    Receipt & text_line(const std::string &txt);
};

} // namespace RP

#endif
