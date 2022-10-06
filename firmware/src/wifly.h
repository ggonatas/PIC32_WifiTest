/* ************************************************************************** */
/** WiFly Module Control Header

  @Company
    George Gonatas

  @File Name
    WiFly.h

  @Summary
    Contains defines and functions to control the MikroE WiFly module click

  @Description
    Ease development for the RN131 module.
 */
/* ************************************************************************** */

#ifndef _WIFLY_H    /* Guard against multiple inclusion */
#define _WIFLY_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include "device.h"
#include "definitions.h"

typedef enum
{
    SUCCESS = 0x00,
    FAILURE = 0x01
} WIFLY_RESPONSE;

/*****************************************************************/
/*********************** COMMAND SEQUENCES ***********************/
/*****************************************************************/
    
/* Command mode sequence */    
extern char COMMAND_MODE[];
extern char CMD_RESPONSE_EXP[];

/* Response sequences */
extern char RESPONSE_AOK[];
extern char RESPONSE_ERR[];

/* Scan sequence */
extern char SCAN_FOR_NETWORKS[];
/* Set WLAN SSID sequence*/
extern char SET_WLAN_SSID[];
/* Set WLAN password sequence */
extern char SET_WLAN_PASSWORD[];
/* Enable auto-join */
extern char ENABLE_WLAN_AUTOJOIN[];

/*****************************************************************/

/*****************************************************************/
/************************ API Functions **************************/
/*****************************************************************/

/* Send packet to enter command mode */
void enterCommandMode(char *response);

/* Scan for available networks */
uint16_t scanForNetworks(char *network_list);

/* Set saved SSID*/
uint8_t setSSID(char *ssid);

/* Set saved password */
uint8_t setPassword(char *password);

/* Set WLAN SSID and password */
uint8_t connectToNetwork(void);

/* Turn on auto-join feature */
uint8_t enableAutoJoin(void);

/* Turn off auto-join feature */
uint8_t disableAutoJoin(void);

/*****************************************************************/
/********************* Accessory Functions ***********************/
/*****************************************************************/

/* Read an unknown amount of characters into the buffer */
uint16_t wifly_read(char *buffer);
/* Required delay before and after entering command mode */
void delay_250ms(void);

/*****************************************************************/

#endif /* _WIFLY_H */

/* *****************************************************************************
 End of File
 */
