#include <cstring>
#define WIN32_LEAN_AND_MEAN

#include <tchar.h>
// #include <iostream>
#include <Windows.h>

#include "rp.h"

static DWORD WriteToPrinter(HANDLE file, const void *buf, size_t n) {
    DWORD bytesWritten = 0;
    WriteFile(file, buf, n, &bytesWritten, NULL);

    return bytesWritten;
}

printer_t RP::CreatePrinter() {
    return printer_t {};
}

int RP::ConfigureSerial(
    printer_t &printer,
    const TCHAR *path,
    DWORD baud,
    BYTE byteSize,
    BYTE parity,
    BYTE stopBits
) {
    HANDLE com = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (com == INVALID_HANDLE_VALUE) {
        return GetLastError();
    }

    DCB serial_params = {0};
    serial_params.DCBlength = sizeof(serial_params);

    GetCommState(com, &serial_params);
    serial_params.BaudRate = baud;
    serial_params.ByteSize = byteSize;
    serial_params.Parity = parity;
    serial_params.StopBits = stopBits;

    if (parity == NOPARITY) {
        serial_params.fParity = FALSE;
    } else {
        serial_params.fParity = TRUE;
    }
    serial_params.fOutxCtsFlow = FALSE;
    serial_params.fRtsControl =RTS_CONTROL_DISABLE;

    serial_params.fOutxDsrFlow = TRUE;
    serial_params.fDtrControl = DTR_CONTROL_HANDSHAKE;

    serial_params.fTXContinueOnXoff = TRUE;
    serial_params.fOutX = FALSE;
    serial_params.fInX = FALSE;
    serial_params.fNull = FALSE;
    SetCommState(com, &serial_params);

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(com, &timeouts);

    printer.file = com;

    return 0;
}

void RP::FeedAndCut(printer_t &printer) {
    const uint8_t buf[] = {GS, 'V', 66, 0};
    int bytesWritten = WriteToPrinter(printer.file, reinterpret_cast<const void *>(buf), sizeof(buf));

    // std::cerr << "[FeedAndCut] bytesWritten=" << bytesWritten << std::endl;
}

void RP::FeedLines(printer_t &printer, uint8_t n) {
    const uint8_t buf[] {ESC, 'd', n};
    int bytesWritten = WriteToPrinter(printer.file, reinterpret_cast<const void *>(buf), 3);

    // std::cerr << "[FeedLines] bytesWritten=" << bytesWritten << std::endl;
}

void RP::Justify(printer_t &printer, uint8_t just) {
    const uint8_t buf[] = {ESC, 'a', just};
    int bytesWritten = WriteToPrinter(printer.file, reinterpret_cast<const void *>(buf), sizeof(buf));

    // std::cerr << "[Justify] bytesWritten=" << bytesWritten << std::endl;
}

void RP::Open(printer_t &printer) {}

void RP::Puts(printer_t &printer, const char *s) {
    size_t n = std::strlen(s);
    int bytesWritten = WriteToPrinter(printer.file, reinterpret_cast<const void *>(s), n);

    const uint8_t buf[] = {CR, LF};
    bytesWritten += WriteToPrinter(printer.file, reinterpret_cast<const void *>(buf), sizeof(buf));

    // std::cerr << "[Puts] input strlen=" << n << ", bytesWritten=" << bytesWritten << std::endl;
}

void RP::PutBarcode(printer_t &printer, uint8_t mode, const char *s) {
    uint8_t n = std::strlen(s);
    const uint8_t buf[] = {GS, 'k', mode, n};
    WriteToPrinter(printer.file, reinterpret_cast<const void *>(buf), sizeof(buf));
    WriteToPrinter(printer.file, reinterpret_cast<const void *>(s), n);
}

void RP::PutBarcode(printer_t &printer, uint8_t mode, const void *data, uint8_t n) {
    const uint8_t buf[] = {GS, 'k', mode, n};
    WriteToPrinter(printer.file, reinterpret_cast<const void *>(buf), sizeof(buf));
    WriteToPrinter(printer.file, data, n);
}

void RP::Reset(printer_t &printer) {
    const uint8_t buf[] = {ESC, '@', ESC, 2};
    int bytesWritten = WriteToPrinter(printer.file, reinterpret_cast<const void *>(buf), sizeof(buf));

    // std::cerr << "[Reset] bytesWritten=" << bytesWritten << std::endl;
}

void RP::SetBarcodeHRIFont(printer_t &printer, uint8_t n) {
    const uint8_t buf[] = {GS, 'f', n};
    WriteToPrinter(printer.file, reinterpret_cast<const void *>(buf), sizeof(buf));
}

void RP::SetBarcodeHeight(printer_t &printer, uint8_t n) {
    const uint8_t buf[] = {GS, 'h', n};
    WriteToPrinter(printer.file, reinterpret_cast<const void *>(buf), sizeof(buf));
}

void RP::SetBarcodeHRIPos(printer_t &printer, uint8_t n) {
    const uint8_t buf[] = {GS, 'H', n};
    WriteToPrinter(printer.file, reinterpret_cast<const void *>(buf), sizeof(buf));
}

void RP::SetBarcodeWidth(printer_t &printer, uint8_t n) {
    const uint8_t buf[] {GS, 'w', n};
    WriteToPrinter(printer.file, reinterpret_cast<const void *>(buf), sizeof(buf));
}

void RP::SetCharacterFont(printer_t &printer, uint8_t n) {
    const uint8_t buf[] = {ESC, 'M', n};
    int bytesWritten = WriteToPrinter(printer.file, reinterpret_cast<const void *>(buf), sizeof(buf));
}

void RP::SetFontAndAttributes(printer_t &printer, uint8_t attr) {
    const uint8_t buf[] = {ESC, '!', attr};
    int bytesWritten = WriteToPrinter(printer.file, reinterpret_cast<const void *>(buf), sizeof(buf));

    // std::cerr << "[SetFontAndAttributes] bytesWritten=" << bytesWritten << std::endl;
}

void RP::SetFontMagnification(printer_t &printer, uint8_t n) {
    const uint8_t buf[] = {GS, '!', n};
    int bytesWritten = WriteToPrinter(printer.file, reinterpret_cast<const void *>(buf), sizeof(buf));
}
