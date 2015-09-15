#ifndef DHT_H
#define DHT_H

#include <stdio.h>
#include <avr/io.h>

/*************************************************************************
 Title  :   C include file for the DHT library (dht.c)
 Author:    Andreas Wilhelm <info@avedo.net> http://avedo.net
 File:      $Id: dht.h,v 0.1 2015/07/16 13:45:07 awilhelm Exp $
 Software:  AVR-GCC 4.x
 Hardware:  any AVR device
***************************************************************************/

/**
 @mainpage
 Basic library for the DHTxx temperature and humidity sensor family
 @author Andreas Wilhelm info@avedo.net http://avedo.net
 @copyright (C) 2015 Andreas Wilhelm, Apache License Version 2

 @file
 @defgroup avedo DHTxx library <dht.h>
 @code #include <dht.h> @endcode

 @brief Basic routines for interfacing with the DHTxx temperature and humidity sensor family as specified in http://www.micro4you.com/files/sensor/DHT11.pdf 
 and https://www.sparkfun.com/datasheets/Sensors/Temperature/DHT22.pdf.

 @author Andreas Wilhelm info@avedo.net http://avedo.net
 @version 0.1
 @copyright (C) 2015 Andreas Wilhelm, Apache License Version 2
*/

/**@{*/

/*
 * All DHT specific definitions below can be defined in a seperate 
 * dht_config.h file instead of modiying this library.
 * To use this file just add -D_DHT_CONFIG to the CDEFS section in 
 * the Makefile. All definitions specified there will override the default ones.
 */
#ifdef _DHT_CONFIG
#include "dht_config.h"
#endif

/**
 * @name Definitions of the Data Pin
 *
 * The four lines of a DHTxx temperature and humidity sensor
 * connect to VCC (3 to 5V power), Data in/out, nothing and GND. 
 * You can change the pin used by the data port by adjusting 
 * DHT_DATA_DDR, DHT_DATA_PORT, DHT_DATA_PIN and DHT_DATA.
 * 
 * Normally the data pin of the DHT is mapped to PORTD, PIND and PD0.
 * 
 * Adjust these definitions to your needs. These definitions could also 
 * be defined in a seperate include file dht_config.h instead of 
 * modifying this file. To use the definitions from the file, 
 * just add -D_DHT_CONFIG to the CDEFS section in
 * the Makefile. All definitions specified there will override the default ones.
 */
#ifndef DHT_DATA_DDR
#define DHT_DATA_DDR DDRD
#endif

#ifndef DHT_DATA_PORT
#define DHT_DATA_PORT PORTD
#endif

#ifndef DHT_DATA_PIN
#define DHT_DATA_PIN PIND
#endif

#ifndef DHT_DATA
#define DHT_DATA PD0
#endif

/**
 * @name Definition of the DHT type.
 * 
 * You can adjust the type, .
 * 
 * Adjust this definition to your needs. This definition could also         
 * be defined in a seperate include file dht_config.h instead of           
 * modifying this file. To use the definitions from the file,                   
 * just add -D_DHT_CONFIG to the CDEFS section in                     
 * the Makefile. All definitions specified there will override the default ones.
 */
#define DHT_DHT11 0
#define DHT_DHT22 1

#ifndef DHT_TYPE
#define DHT_TYPE DHT11
#endif

/**
 * @name Definition of connection timeout 
 * 
 * This timeout can be adjusted, if you have problems fetching the data.
 * 
 * Adjust this definition to your needs. This definition could also         
 * be defined in a seperate include file dht_config.h instead of           
 * modifying this file. To use the definitions from the file,                   
 * just add -D_DHT_CONFIG to the CDEFS section in                     
 * the Makefile. All definitions specified there will override the default ones.
 */
#ifndef DHT_TIMEOUT
#define DHT_TIMEOUT 200
#endif

// Functions.
#if DHT_TYPE == DHT_11
extern int8_t dht_fetch(int8_t *temperature, int8_t *humidity);
#else
extern int8_t dht_fetch(float *temperature, float *humidity);
#endif

#endif // DHT_H
