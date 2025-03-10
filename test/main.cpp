#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <windows.h>

#include "escpos.h"
#include "printer/epson.h"
#include "Receipt.h"

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        std::cerr << "Too few argumetns" << std::endl;
        std::cerr << argv[0] << " <COM>" << std::endl;

        return 1;
    }

    const uint8_t FONT_HEADER = (PRINT_FONT1 | PRINT_DBLH | PRINT_DBLW);
    const uint8_t FONT_TALL = (PRINT_FONT1 | PRINT_DBLH);
    const uint8_t FONT_NORMAL = PRINT_FONT1;

    RP::Receipt test_receipt;
    test_receipt.font_attributes(FONT_HEADER)
        .align_text(JUSTIFY_CENTER)
        .text_line("Chickin' Shack");

    test_receipt.font_attributes(FONT_NORMAL)
        .text_line("17 FEB 2024")
        .feed_lines(1)
        .font_attributes(FONT_TALL)
        .text_line("Order # 04200176")
        .feed_lines(2);

    test_receipt
        .font_attributes(FONT_NORMAL)
        .align_text(JUSTIFY_LEFT)
        .text(
            "-------------------------------------------\n"
            "1  BD STP CMB                          9.49\n"
            "     +SPC SAUCE                            \n"
            "1  LTLBRD MEAL                         4.99\n"
            "      FRSH FRT                             \n"
            "1  LG DT CK                            1.99\n"
            "1  SM LMND                             0.99\n"
            "-------------------------------------------\n"
        )
        .align_text(JUSTIFY_RIGHT)
        .text(
            "SUBTOTAL    17.46\n"
            "TAX          1.20\n"
        )
        .font_attributes(FONT_TALL)
        .text_line("TOTAL       18.60");

    test_receipt
        .font_attributes(FONT_NORMAL)
        .align_text(JUSTIFY_LEFT)
        .character_font(CHR_FONT_B)
        .feed_lines(1)
        .text(
            "Thank you for choosing our restaurant. We know you have a lot of choices when it comes to fast food,"
            " so we want to make sure you know how much you mean to us. In that regard, we offer a 100% money-back guarantee"
            " with every purchase. If, for any reason, you are not satisfied with your meal you may request a partial or"
            "full refund. Please keep in mind, the restaurant manager may choose to deny your refund at their discretion."
            " If you believe this is in error, you may submit a full, detailed report of your complaint of your meal, as"
            " well as a photocopy of your receipt, to our corporate customer care team via email. More information and the"
            " email address of the care team is available on our website, printed below.\n"
        )
        .character_font(CHR_FONT_A)
        .font_attributes(FONT_HEADER)
        .align_text(JUSTIFY_CENTER)
        .text_line("THANK YOU")
        .font_attributes(FONT_NORMAL)
        .text_line("www.chickinshack.com")
        .feed_lines(4);

    test_receipt
        .barcode_hri_pos(HRI_NONE)
        .barcode(BCM_CODE93, "04200176")
        .feed_lines(4)
        .feed_and_cut();


    std::cout << test_receipt.output();

    return 0;
}
