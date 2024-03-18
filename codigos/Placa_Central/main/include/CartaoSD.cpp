/**
 * Project Classes Placa Central
 */


#include "CartaoSD.h"

/**
 * CartaoSD implementation
 */

/**
 * @return bool
 */
bool CartaoSD::Setup() {
    SPI1.setRX(SD_RXPIN); // MISO
    SPI1.setTX(SD_TXPIN); // MOSI
    SPI1.setSCK(SD_SCKPIN);
    SPI1.setCS(SD_CSPIN);
    SPI1.begin(true);
    if(SD.begin(SD_CSPIN, SPI1)){
        digitalWrite(LED_BUILTIN, HIGH);
    }
    return;
}

/**
 * @return bool
 */
bool CartaoSD::Test() {
    return;
}

/**
 * @return bool
 */
bool CartaoSD::TestChosen(int escolhido) {
    return;
}

/**
 * @return void
 */
void CartaoSD::criarArquivoDados() {
    return;
}

/**
 * @return void
 */
void CartaoSD::sdCardSetup() {
    return;
}

/**
 * @param int
 * @param int
 * @param int
 * @param float float
 * @return void
 */
void CartaoSD::writeData(int a, int b, int c, float d, float e) {
    return;
}

/**
 * @return bool
 */
bool CartaoSD::testarCartaoSD() {
    return false;
}


/**
 * @return string
 */
String CartaoSD::getNomeArquivo() {
    return "";
}