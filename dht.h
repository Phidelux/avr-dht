#ifndef DHT_H
#define DHT_H

#include <stdio.h>
#include <avr/io.h>

#ifdef DHT_CONFIG
#include "dht_config.h"
#endif

// Setup the data port.
#define DHT_DDR DDRD
#define DHT_PORT PORTD
#define DHT_PIND PIND
#define DHT_PIN PD0

// Available sensor types.
#define DHT_DHT11
#define DHT_DHT22
#define DHT_type DHT11

// Connection timeout.
#define DHT_TIMEOUT 200

// Functions.
#if DHT_TYPE == DHT_11
extern int8_t dht_fetch(int8_t *temperature, int8_t *humidity);
#else
extern int8_t dht_fetch(float *temperature, float *humidity);
#endif

#endif // DHT_H
