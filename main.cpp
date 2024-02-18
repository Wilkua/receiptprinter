#define WIN32_LEAN_AND_MEAN

#include <tchar.h>
#include <iostream>
#include <windows.h>

#include "rp.h"

int _tmain(int argc, const TCHAR *argv[]) {
    if (argc < 2) {
        std::wcerr << L"Too few argumetns" << std::endl;
        std::wcerr << argv[0] << L" <COM>" << std::endl;

        return 1;
    }

    printer_t printer = RP::CreatePrinter();
    RP::ConfigureSerial(printer, argv[1], CBR_19200, 8, NOPARITY, ONESTOPBIT);

    const uint8_t FONT_HEADER = (PRINT_FONT1 | PRINT_DBLH | PRINT_DBLW);
    const uint8_t FONT_TALL = (PRINT_FONT1 | PRINT_DBLH);
    const uint8_t FONT_NORMAL = PRINT_FONT1;

    RP::Reset(printer);
    RP::SetFontAndAttributes(printer, FONT_HEADER);
    RP::Justify(printer, JUSTIFY_CENTER);
    RP::Puts(printer, "Chickin' Shack");

    RP::SetFontAndAttributes(printer, FONT_NORMAL);
    RP::Puts(printer, "17 FEB 2024\n");
    RP::SetFontAndAttributes(printer, FONT_TALL);
    RP::Puts(printer, "Order # 04200176");
    RP::FeedLines(printer, 2);
    RP::SetFontAndAttributes(printer, FONT_NORMAL);
    RP::Justify(printer, JUSTIFY_LEFT);
    RP::Puts(printer,
             "-------------------------------------------\n"
             "1  BD STP CMB                          9.49\n"
             "     +SPC SAUCE                            \n"
             "1  LTLBRD MEAL                         4.99\n"
             "      FRSH FRT                             \n"
             "1  LG DT CK                            1.99\n"
             "1  SM LMND                             0.99\n"
             "-------------------------------------------\n"
             );
    RP::Justify(printer, JUSTIFY_RIGHT);
    RP::Puts(printer,
             "SUBTOTAL    17.46\n"
             "TAX          1.20\n"
             );
    RP::SetFontAndAttributes(printer, FONT_TALL);
    RP::Puts(printer, "TOTAL       18.60");
    RP::SetFontAndAttributes(printer, FONT_NORMAL);
    RP::Justify(printer, JUSTIFY_LEFT);
    RP::FeedLines(printer, 1);
    RP::SetCharacterFont(printer, CHR_FONT_B);
    RP::Puts(printer, "Thank you for choosing our restaurant. We know you have a lot of choices when it comes to fast food,"
             " so we want to make sure you know how much you mean to us. In that regard, we offer a 100% money-back guarantee"
             " with every purchase. If, for any reason, you are not satisfied with your meal you may request a partial or"
             "full refund. Please keep in mind, the restaurant manager may choose to deny your refund at their discretion."
             " If you believe this is in error, you may submit a full, detailed report of your complaint of your meal, as"
             " well as a photocopy of your receipt, to our corporate customer care team via email. More information and the"
             " email address of the care team is available on our website, printed below.\n");
    RP::SetCharacterFont(printer, CHR_FONT_A);
    RP::SetFontAndAttributes(printer, FONT_HEADER);
    RP::Justify(printer, JUSTIFY_CENTER);
    RP::Puts(printer, "THANK YOU");
    RP::SetFontAndAttributes(printer, FONT_NORMAL);
    RP::Puts(printer, "www.chickinshack.com");
    RP::FeedLines(printer, 4);
    RP::SetBarcodeHRIPos(printer, HRI_NONE);
    RP::PutBarcode(printer, BCM_CODE93, "04200176");
    RP::FeedLines(printer, 4);
    RP::FeedAndCut(printer);

    CloseHandle(printer.file);

    return 0;
}
