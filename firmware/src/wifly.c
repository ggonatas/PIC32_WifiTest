/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

#include <string.h>

#include "device.h"
#include "definitions.h"
#include "wifly.h"


char COMMAND_MODE[] = {'$','$','$'};
char CMD_RESPONSE_EXP[] = {'C','M','D'};

char RESPONSE_AOK[] = "AOK";
char RESPONSE_ERR[] = "ERR";

char SCAN_FOR_NETWORKS[] = "scan\r\n";              //{'S','C','A','N','\r'};
char SET_WLAN_SSID[] = "set wlan ssid ";
char SET_WLAN_PASSWORD[] = "set wlan pass ";
char ENABLE_WLAN_AUTOJOIN[] = "set wlan join 1\r\n";



void enterCommandMode(char *response)
{
    /* Wait 250 ms */
    delay_250ms();
    /* Write command mode string to RN131 */
    UART2_Write(COMMAND_MODE, sizeof(COMMAND_MODE));
    /* Wait for response */
    UART2_Read(response, 3);
    response[3] = '\0';
    /* Wait additional time for RN131 */
    delay_250ms();
}

uint16_t scanForNetworks(char *network_list)
{
    /* Send scan command */
    UART2_Write(SCAN_FOR_NETWORKS, sizeof(SCAN_FOR_NETWORKS));
    /* Perform read for network list */
    return wifly_read(network_list);
}

uint8_t setSSID(char *ssid)
{
    char ssid_packet[30];       //SSID name packet
    char response_packet[5];    //Response from RN131
    
    /* Create SSID packet for transmit */
    strcpy(ssid_packet, SET_WLAN_SSID);
    strcat(ssid_packet, ssid);
    
    /* Write SSID packet to save SSID */
    UART2_Write(ssid_packet, strlen(ssid_packet));
    /* Wait for response from RN131 */
    UART2_Read(response_packet, 3);
    response_packet[3] = '\0';
    /* Validate response from RN131 */
    if (strcmp(response_packet, RESPONSE_AOK) == 0) //Successfully set SSID
    {
        return SUCCESS;
    }
    /* Successful*/
    return FAILURE;
}

uint8_t setPassword(char *password)
{
    char password_packet[30];   //Password packet
    char response_packet[5];    //Response from RN131
    
    /* Create password packet */
    strcpy(password_packet, SET_WLAN_PASSWORD);
    strcat(password_packet, password);
    
    /* Write password packet */
    UART2_Write(password_packet, strlen(password_packet));
    /* Wait for response from RN131 */
    UART2_Read(response_packet, 3);
    response_packet[3] = '\0';
    /* Validate response from RN131 */
    if (strcmp(response_packet, RESPONSE_AOK) == 0) //Successfully set password
    {
        return SUCCESS;
    }
    
    /* Setting both SSID and password successful, return 0 */
    return FAILURE;
}

uint8_t connectToNetwork(void)
{
    return SUCCESS;
}

uint8_t enableAutoJoin(void)
{
    char response_packet[5];    //Response from RN131
    
    /* Write SSID packet to save SSID */
    UART2_Write(ENABLE_WLAN_AUTOJOIN, strlen(ENABLE_WLAN_AUTOJOIN));
    /* Wait for response from RN131 */
    UART2_Read(response_packet, 3);
    response_packet[3] = '\0';
    /* Validate response from RN131 */
    if (strcmp(response_packet, RESPONSE_ERR) == 0) //Failed to set SSID
    {
        return FAILURE;
    }
    return SUCCESS;
}

uint16_t wifly_read(char *buffer)
{
    /* Counter variable */
    uint16_t num_chars = 0;
    
    /* Loop until buffer full or timeout */
    while(num_chars < sizeof(buffer))
    {
        /*Set 500ms timeout period */
        PR4 = 49999998U;
        TMR4_Start();
        /* Wait for data */
        while(!(U2STA & _U2STA_URXDA_MASK))
        {
            if(IFS0bits.T5IF == 1)  //Timeout occurred
            {
                /* Return number read, read finished */
                return num_chars;
            }
        }
        /* Read character */
        buffer[num_chars++] = (char)UART2_ReadByte();
    }
    /* Buffer completely full, may have missed data */
    return num_chars;
}

void delay_250ms(void)
{
    /*Set period */
    PR2 = 781248U;
    //Start Timer 2
    TMR2_Start();
    //Wait for IF flag to set
    while(IFS0bits.T3IF == 0);
}

/* *****************************************************************************
 End of File
 */
