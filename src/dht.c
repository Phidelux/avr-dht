#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#include "dht.h"

#if DHT_TYPE == DHT11
int8_t dht_fetch(int8_t *temperature, int8_t *humidity) {
#else
int8_t dht_fetch(float *temperature, float *humidity) {
#endif
    uint8_t data[4];
    uint8_t checksum;
    uint8_t i, j = 0;

    memset(data, 0, sizeof(data);
}
