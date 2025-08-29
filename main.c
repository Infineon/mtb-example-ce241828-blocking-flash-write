/******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the PSoC 4 Blocking Flash Write 
*              example for ModusToolbox.
*
* Related Document: See README.md 
*
*
*******************************************************************************
* Copyright 2024-2025, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

/*******************************************************************************
 * Include Header files
 *******************************************************************************/
#include "cy_pdl.h"
#include "cybsp.h"

/*******************************************************************************
* Global Variables
********************************************************************************/

/* Define and initialize data to write */
    uint32_t data[CY_FLASH_SIZEOF_ROW / sizeof(uint32_t)];

    uint32_t CY_FLASH_ADR       = 0x00008000UL;


/********************************************************************************
* Function Name: main
*********************************************************************************
* Summary:
* The main function performs the following actions:
*  1. Initializes the BSP
*  2. Calls the functions to configure and initialize Blocking Flash write
*  3. Reads the Blocking Flash write content if available
*  4. It writes flash memory row.
*  5. Light the LED_OK if the Blocking Flash write operation was successful. 
*     Or not, light the LED_ERROR
*
********************************************************************************/
int main(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init() ;
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Enable global interrupts */
    __enable_irq();

    cy_en_flashdrv_status_t status;
    /* Initialize data */
    memset(data, 0x5A, CY_FLASH_SIZEOF_ROW);
    Cy_GPIO_Write(LED_ERROR_PORT, LED_ERROR_NUM, CYBSP_LED_STATE_OFF);
    Cy_GPIO_Write(LED_OK_PORT, LED_OK_NUM, CYBSP_LED_STATE_OFF);
    /* Write data at the specified row address */
    status = Cy_Flash_WriteRow(CY_FLASH_ADR, data);
    if ((CY_FLASH_DRV_SUCCESS != status) || memcmp(data, (const void*)CY_FLASH_ADR
    , CY_FLASH_SIZEOF_ROW) != 0)
    {
        /* Handle error here */
        /* Turn the failure/User LED6 ON */
    Cy_GPIO_Write(LED_ERROR_PORT, LED_ERROR_NUM, CYBSP_LED_STATE_ON);
    }
    else
    {
        /* Turn the successful/User LED7 ON */
    Cy_GPIO_Write(LED_OK_PORT, LED_OK_NUM, CYBSP_LED_STATE_ON);
    }

    for (;;)
    {
    }
}

/* [] END OF FILE */
