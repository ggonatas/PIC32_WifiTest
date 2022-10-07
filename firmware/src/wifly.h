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
extern char SET_BAUDRATE_115200[];
extern char ENABLE_DHCP[];
extern char SET_AUTH_WPA_WPA2[];

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
/* Join saved network sequence */
extern char JOIN_NETWORK[];

/*****************************************************************/

/*****************************************************************/
/************************ API Functions **************************/
/*****************************************************************/

/* Send packet to enter command mode */
void enterCommandMode(char *response);

/* Send general command */
void sendCommand(char *cmd, char *response);

/* Scan for available networks */
uint16_t scanForNetworks(char *network_list);

/* Set saved SSID*/
WIFLY_RESPONSE setSSID(char *ssid);

/* Set saved password */
WIFLY_RESPONSE setPassword(char *password);

/* Set WLAN SSID and password */
WIFLY_RESPONSE connectToNetwork(void);

/* Turn on auto-join feature */
WIFLY_RESPONSE enableAutoJoin(void);

/*****************************************************************/
/********************* Accessory Functions ***********************/
/*****************************************************************/

/* Read string from terminal and return number of chars read */
uint8_t readTerminalString(char *buffer);
/* Read an unknown amount of characters into the buffer */
uint16_t wifly_read(char *buffer);
/* Required delay before and after entering command mode */
void delay_250ms(void);

/*****************************************************************/

#endif /* _WIFLY_H */

/* *****************************************************************************
 End of File
 */
