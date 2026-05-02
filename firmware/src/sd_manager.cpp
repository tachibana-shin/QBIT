#include "sd_manager.h"
#include "settings.h"
#include <SD.h>
#include <SPI.h>

static bool _sdReady = false;
static SPIClass *_sdSpi = nullptr;

bool sdManagerInit() {
    _sdReady = false;

    uint8_t cs   = getPinSdCS();
    uint8_t mosi = getPinSdMOSI();
    uint8_t clk  = getPinSdCLK();
    uint8_t miso = getPinSdMISO();

    Serial.printf("SD: Initializing SPI (CS=%u, MOSI=%u, CLK=%u, MISO=%u)\n",
                  cs, mosi, clk, miso);

    _sdSpi = new SPIClass(FSPI);
    _sdSpi->begin(clk, miso, mosi, cs);

    if (!SD.begin(cs, *_sdSpi)) {
        Serial.println("SD: Card mount failed (no card or bad wiring)");
        return false;
    }

    uint8_t cardType = SD.cardType();
    if (cardType == CARD_NONE) {
        Serial.println("SD: No card detected");
        return false;
    }

    Serial.print("SD: Card type: ");
    switch (cardType) {
        case CARD_MMC:  Serial.println("MMC"); break;
        case CARD_SD:   Serial.println("SDSC"); break;
        case CARD_SDHC: Serial.println("SDHC"); break;
        default:        Serial.println("UNKNOWN"); break;
    }

    Serial.printf("SD: Card size: %llu MB\n", SD.cardSize() / (1024 * 1024));

    if (!SD.exists("/QBit")) {
        Serial.println("SD: /QBit folder not found -- creating...");
        if (!SD.mkdir("/QBit")) {
            Serial.println("SD: Failed to create /QBit folder");
            return false;
        }
        Serial.println("SD: /QBit folder created");
    }

    _sdReady = true;
    Serial.println("SD: Ready, /QBit folder exists");
    return true;
}

bool sdManagerIsReady() {
    return _sdReady;
}

fs::FS& sdManagerFS() {
    return SD;
}

uint64_t sdManagerTotalBytes() {
    return SD.totalBytes();
}

uint64_t sdManagerUsedBytes() {
    return SD.usedBytes();
}
