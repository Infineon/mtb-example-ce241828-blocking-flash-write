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
* (c) 2024-2025, Infineon Technologies AG, or an affiliate of Infineon
* Technologies AG. All rights reserved.
* This software, associated documentation and materials ("Software") is
* owned by Infineon Technologies AG or one of its affiliates ("Infineon")
* and is protected by and subject to worldwide patent protection, worldwide
* copyright laws, and international treaty provisions. Therefore, you may use
* this Software only as provided in the license agreement accompanying the
* software package from which you obtained this Software. If no license
* agreement applies, then any use, reproduction, modification, translation, or
* compilation of this Software is prohibited without the express written
* permission of Infineon.
* 
* Disclaimer: UNLESS OTHERWISE EXPRESSLY AGREED WITH INFINEON, THIS SOFTWARE
* IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING, BUT NOT LIMITED TO, ALL WARRANTIES OF NON-INFRINGEMENT OF
* THIRD-PARTY RIGHTS AND IMPLIED WARRANTIES SUCH AS WARRANTIES OF FITNESS FOR A
* SPECIFIC USE/PURPOSE OR MERCHANTABILITY.
* Infineon reserves the right to make changes to the Software without notice.
* You are responsible for properly designing, programming, and testing the
* functionality and safety of your intended application of the Software, as
* well as complying with any legal requirements related to its use. Infineon
* does not guarantee that the Software will be free from intrusion, data theft
* or loss, or other breaches ("Security Breaches"), and Infineon shall have
* no liability arising out of any Security Breaches. Unless otherwise
* explicitly approved by Infineon, the Software may not be used in any
* application where a failure of the Product or any consequences of the use
* thereof can reasonably be expected to result in personal injury.
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
