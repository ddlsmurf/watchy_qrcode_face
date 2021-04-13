#include <Watchy.h>
#include "qrencode.h"

static String zeroPadded(int number) {
    String result(number);
    if (number >= 10)
        return result;
    return String("0") + result;
}

class WatchyQRCode : public Watchy {
public:
    WatchyQRCode() {};
    void drawWatchFace() {
        String time = zeroPadded(currentTime.Hour) + ":" + zeroPadded(currentTime.Minute);
        QRcode *q = QRcode_encodeString(time.c_str(), 0, QR_ECLEVEL_Q, QR_MODE_8, 1);
        const unsigned int spacer = 3,
                           squareCount = q->width + 2 * spacer,
                           squareSize = DISPLAY_WIDTH / squareCount,
                           offset = (DISPLAY_WIDTH - (q->width * squareSize)) / 2;
        display.fillScreen(GxEPD_WHITE);
        for (int y = 0; y < q->width; y++)
            for (int x = 0; x < q->width; x++)
                if (q->data[y * q->width + x] & 1)
                    display.fillRect(offset + x * squareSize,
                                     offset + y * squareSize,
                                     squareSize,
                                     squareSize,
                                     GxEPD_BLACK);
        QRcode_free(q);
    }
};

WatchyQRCode watchy;

void setup(){
    watchy.init();
}

void loop(){}



