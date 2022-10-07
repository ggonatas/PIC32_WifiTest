/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <string.h>

#include "definitions.h"                // SYS function prototypes
#include "wifly.h"

/* Messages for UART6 output */
uint8_t newline[] = "\r\n";
uint8_t welcome_msg[] = "WiFly Click Testing\r\nInitializing system...\r\n";
uint8_t command_msg[] = "Switching to command mode... ";
uint8_t cmd_ok[] = "Success.\r\n";
uint8_t cmd_fail[] = "Failed.\r\n";
uint8_t restart_msg[] = "Please reset system and try again.\r\n";

uint8_t menu_selection[] = "Please select and option:\r\n"
        "1. Scan for networks\r\n"
        "2. Set saved SSID\r\n"
        "3. Set saved password\r\n"
        "4. Connect to a saved network\r\n"
        "5. Enable auto-join\r\n"
        "6. Set RN131 as TCP client\r\n"
        "7. Exit command mode (run data demo)\r\n"
        "Option: ";

uint8_t ssid_prompt[] = "Enter SSID: ";
uint8_t password_prompt[] = "Enter password: ";



/* Command response buffer */
char cmd_response_buf[4];
/* Menu response buffer */
char menu_response_buf[3];
/* Scan list buffer */
char network_list[512];
uint16_t network_list_size = 0;
/* SSID and password buffers */
char ssid[20];
char password[30];
WIFLY_RESPONSE status;

void delay_500ms(void);

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    /* Disable Timer interrupts */
    TMR2_InterruptDisable();
    TMR4_InterruptDisable();
    
    /* Delay to allow RN131 init time */
    delay_500ms();
    
    /* Print initial statements */
    UART6_Write(welcome_msg, sizeof(welcome_msg));
    UART6_Write(command_msg, sizeof(command_msg));
    
    /* Send command mode message */
    enterCommandMode(cmd_response_buf);
    
    /* Verify command mode entered */
    if (strncmp(cmd_response_buf, CMD_RESPONSE_EXP, 3) != 0)
    {
        UART6_Write(cmd_fail, sizeof(cmd_fail));
        UART6_Write(restart_msg, sizeof(restart_msg));
        while( true );
    }
    
    /* Set baud rate to 115200 */
    //sendCommand(SET_BAUDRATE_115200, cmd_response_buf);
    
    /* Set DCHP */
    sendCommand(ENABLE_DHCP, cmd_response_buf);
    
    /* Enter control loop */
    while( true )
    {
        /* Print OK message */
        UART6_Write(cmd_ok, sizeof(cmd_ok));
        /* Print selection menu */
        UART6_Write(menu_selection, sizeof(menu_selection));
        /* Wait for user input */
        UART6_Read(menu_response_buf, 1);
        
        /* Do task */
        switch(menu_response_buf[0])
        {
            case '1':   //Scan for networks
            {
                /* Run network scan operation */
                scanForNetworks(network_list);
                /* Print list of networks to PC terminal */
                UART6_Write(network_list, network_list_size);
                /* Exit switch */
                break;
            }
            case '2':   //Set SSID
            {
                UART6_Write(ssid_prompt, sizeof(ssid_prompt));
                readTerminalString(ssid);
                status = setSSID(ssid);
                UART6_Write(newline, sizeof(newline));
                if(status == SUCCESS)
                    UART6_Write(cmd_ok, sizeof(cmd_ok));
                else
                    UART6_Write(cmd_fail, sizeof(cmd_fail));
                break;
            }
            case '3':   //Set password
            {
                UART6_Write(password_prompt, sizeof(password_prompt));
                readTerminalString(password);
                status = setPassword(password);
                UART6_Write(newline, sizeof(newline));
                if(status == SUCCESS)
                    UART6_Write(cmd_ok, sizeof(cmd_ok));
                else
                    UART6_Write(cmd_fail, sizeof(cmd_fail));
                break;
                break;
            }
            case '4':   //Connect to saved network
            {
                
            }
        }
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}

void delay_500ms(void)
{
    /*Set period */
    PR2 = 1562496U;
    //Start Timer 2
    TMR2_Start();
    //Wait for IF flag to set
    while(IFS0bits.T3IF == 0);
}

/*******************************************************************************
 End of File
*/

