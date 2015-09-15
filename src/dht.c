#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#include "dht.h"

#if DHT_TYPE == DHT11
int8_t dht_fetch(int8_t *temperature, int8_t *humidity) {
#else
int8_t dht_fetch(float *temperature, float *humidity) {
#endif
    // Data consists of decimal and integral parts. A complete data
    // transmission is 40bit, and the sensor sends higher data bit first.
    // Data format: 8bit integral RH data + 8bit decimal RH data
    // + 8bit integral T data + 8bit decimal T data + 8bit check sum
    uint8_t data[5];

    // Initialize buffer with zero.
    memset(data, 0, sizeof(data);

    // Configure the data pin as output port.
    DHT_DATA_DDR |= (1 << DHT_DATA);

    // Reset the communication by pulling the data pin high.
    DHT_DATA_PORT |= (1 << DHT_DATA);
    _delay_ms(100);

    // Send the start signal to the sensor.
    DHT_DATA_PORT &= ~(1 << DHT_DATA);

    #if DHT_TYPE == DHT_DHT11
    _delay_ms(20);
    #else
    _delay_ms(1000);
    #endif

    // Pull up voltage again, configure data pin as input port
    // and wait for response.
    DHT_DATA_PORT |= (1 << DHT_DATA);
    DHT_DATA_DDR &= ~(1 << DHT_DATA);
    _delay_ms(40);

    // Check start condition 1, eg. data pin is low for ~80us.
    if(DHT_DATA_PIN & (1 << DHT_DATA)) {
      // Error.
      return -1;
    }

    _delay_ms(80);

    // Check start condition 2, eg. data pin is high for ~80us.
    if(!(DHT_DATA_PIN & (1 << DHT_DATA))) {
      // Error.
      return -1;
    }

    // Wait until transmission starts (40us + 25 to center).
    _delay_us(65);

    // Each bit transmission starts with 50us low voltage, followed by 26-28us
    // high voltage for low bit and 70us high voltage for high bit.
    for(uint8_t byte = 0; byte < 5; byte++) {
      for(uint8_t bit = 7; bit >= 0; bit--) {
        // Check if data pin is low (~50us).
        if(DHT_DATA_PIN & (1 << DHT_DATA)) {
          // Error.
          return -1;
        }

        _delay_us(40);

        // Check if data pin is high.
        if(!(DHT_DATA_PIN & (1 << DHT_DATA))) {
          // Error.
          return -1;
        }

        _delay_us(40);

        // Check if received bit is high or low.
        if(DHT_DATA_PIN & (1 << DHT_DATA)) {
          // Bit is high.
          data[byte] |= (1 << bit);

          // Wait till end of transmission (~15us) and center in
          // start sequence (~25us).
          _delay_us(40);
        }
      }
    }

    // Verify the checksum stored as the last 8 bits.
    if(data[0] + data[1] + data[2] + data[3] == data[4]) {
      // Return temperature and humidity.
      #if DHT_TYPE == DHT_DHT11
        *temperature = bits[2];
        *humidity = bits[0];
      #else
        uint16_t rawHum = data[0]<<8 | data[1];
        uint16_t rawTmp = data[2]<<8 | data[3];

        if(rawTmp & 0x8000) {
          *temperature = (float)((rawTmp & 0x7FFF) / 10.0) * -1.0;
        } else {
          *temperature = (float)(rawTmp)/10.0;
        }

        *humidity = (float)(rawHum)/10.0;
      #endif

      return 0;
    }

    return -1;
}
