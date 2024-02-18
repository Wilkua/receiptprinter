#pragma once

#define WIN32_LEAN_AND_MEAN
#include <tchar.h>
#include <Windows.h>
#include <stdint.h>

#define LF  0x0A
#define FF  0x0C
#define CR  0x0D
#define ESC 0x1B
#define FS  0x1C
#define GS  0x1D

#define PRINT_FONT1 0x00
#define PRINT_FONT2 0x01
#define PRINT_EM    0x08
#define PRINT_DBLH  0x10
#define PRINT_DBLW  0x20
#define PRINT_UND   0x80

#define FONT_HEIGHT_X1 0x01
#define FONT_HEIGHT_X2 0x02
#define FONT_HEIGHT_X3 0x03
#define FONT_HEIGHT_X4 0x04
#define FONT_HEIGHT_X5 0x05
#define FONT_HEIGHT_X6 0x06
#define FONT_HEIGHT_X7 0x07
#define FONT_HEIGHT_X8 0x08

#define FONT_WIDTH_X1 0x00
#define FONT_WIDTH_X2 0x10
#define FONT_WIDTH_X3 0x20
#define FONT_WIDTH_X4 0x30
#define FONT_WIDTH_X5 0x40
#define FONT_WIDTH_X6 0x50
#define FONT_WIDTH_X7 0x60
#define FONT_WIDTH_X8 0x70

#define JUSTIFY_LEFT   0
#define JUSTIFY_CENTER 1
#define JUSTIFY_RIGHT  2

#define HRI_NONE  0
#define HRI_ABOVE 1
#define HRI_BELOW 2
#define HRI_BOTH  3

#define CHR_FONT_A     '0'
#define CHR_FONT_B     '1'
#define CHR_FONT_C     '2'
#define CHR_FONT_D     '3'
#define CHR_FONT_E     '4'
#define CHR_FONT_SPECA 'A'
#define CHR_FONT_SPECB 'B'

#define HRI_FONT_A     '0'
#define HRI_FONT_B     '1'
#define HRI_FONT_C     '2'
#define HRI_FONT_D     '3'
#define HRI_FONT_E     '4'
#define HRI_FONT_SPECA 'A'
#define HRI_FONT_SPECB 'B'

#define BCM_UPCA              'A'
#define BCM_UPCE              'B'
#define BCM_JAN13             'C'
#define BCM_EAN13             'C'
#define BCM_JAN18             'D'
#define BCM_EAN18             'D'
#define BCM_CODE39            'E'
#define BCM_ITF               'F'
#define BCM_CODABAR           'G'
#define BCM_CODE93            'H'
#define BCM_CODE128           'I'
#define BCM_GS1_128           'J'
#define BCM_GS1_DATABAR_OMNI  'K'
#define BCM_GS1_DATABAR_TRUNC 'L'
#define BCM_GS1_DATABAR_LTD   'M'
#define BCM_GS1_DATABAR_EXP   'N'
#define BCM_CODE128_AUTO      'O'

typedef struct _printer_t_TAG {
    HANDLE file;
    // need:
    //   OEM
    //   Model
    //   Firmware
    // Want:
    //   comType
} printer_t;

namespace RP {
    printer_t CreatePrinter();
    int ConfigureSerial(printer_t &printer, const TCHAR *path, DWORD baud, BYTE byteSize, BYTE parity, BYTE stopBits);
    void FeedAndCut(printer_t &printer);
    void FeedLines(printer_t &printer, uint8_t n);
    void Justify(printer_t &printer, uint8_t just);
    void Open(printer_t &printer);
    void PutBarcode(printer_t &printer, uint8_t mode, const char *data);
    void PutBarcode(printer_t &printer, uint8_t mode, const void *data, uint8_t n);
    void Puts(printer_t &printer, const char *c);
    void Reset(printer_t &printer);
    void SetBarcodeHRIFont(printer_t &printer, uint8_t n);
    void SetBarcodeHeight(printer_t &printer, uint8_t n);
    void SetBarcodeHRIPos(printer_t &printer, uint8_t n);
    void SetBarcodeWidth(printer_t &printer, uint8_t n);
    void SetCharacterFont(printer_t &printer, uint8_t n);
    void SetFontAndAttributes(printer_t &printer, uint8_t attr);
    void SetFontMagnification(printer_t &printer, uint8_t n);
};
