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
uint8_t welcome_msg[] = "WiFly Click Testing\r\nInitializing system...\r\n";
uint8_t command_msg[] = "Switching to command mode... ";
uint8_t cmd_mode_ok[] = "Success.\r\n";
uint8_t cmd_mode_fail[] = "Failed.\r\n";
uint8_t restart_msg[] = "Please reset system and try again.\r\n";

uint8_t menu_selection[] = "Please select and option:\r\n"
        "1. Scan for networks\r\n"
        "2. Set saved SSID\r\n"
        "3. Set saved password\r\n"
        "4. Connect to a known network\r\n"
        "5. Enable auto-join\r\n"
        "6. Disable auto-join\r\n"
        "7. Exit command mode (run data demo)\r\n"
        "Option: ";

/* Command response buffer */
char cmd_response_buf[4];
/* Menu response buffer */
char menu_response_buf[3];
/* Scan list buffer */
char network_list[512];
uint16_t network_list_size = 0;

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
    
    /* Print initial statements */
    UART6_Write(welcome_msg, sizeof(welcome_msg));
    UART6_Write(command_msg, sizeof(command_msg));
    
    /* Send command mode message */
    enterCommandMode(cmd_response_buf);
    
    /* Verify command mode entered */
    if (strncmp(cmd_response_buf, CMD_RESPONSE_EXP, 3) != 0)
    {
        UART6_Write(cmd_mode_fail, sizeof(cmd_mode_fail));
        UART6_Write(restart_msg, sizeof(restart_msg));
        while( true );
    }
    while( true )
    {
        /* Print OK message */
        UART6_Write(cmd_mode_ok, sizeof(cmd_mode_ok));
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
            case '2':   //Connect to a network
            {
                
            }
        }
    }
    
    
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}

/*******************************************************************************
 End of File
*/

