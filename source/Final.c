#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MK64F12.h"
#include "fsl_debug_console.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "freertos_spi.h"
#include "fsl_port.h"
#include "fsl_dspi.h"

//  Inicio
const uint8_t cinves_Bitmap[] = {
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xfc, 0xfc, 0x3e, 0x1e, 0x9e, 0x9f, 0x8f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x9f, 0x8f, 0x9f, 0x9e, 0x9e, 0xfe, 0x7c, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf8, 0xfc, 0xfe, 0x7e, 0x1e, 0x0e, 0xcc, 0xf8, 0xf8, 0x78, 0xfc, 0x9e, 0x0f, 0x0f, 0x3f, 0x77, 0x63, 0x73, 0xfe, 0xf0, 0x30, 0x30, 0xfe, 0xf7, 0x73, 0x33, 0x1f, 0x0f, 0x07, 0xcf, 0xde, 0x3c, 0x7c, 0xfc, 0xf6, 0xc7, 0x07, 0x1f, 0x3f, 0xff, 0xfc, 0xf8, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0x07, 0x01, 0x80, 0xc0, 0xc0, 0xc3, 0x43, 0xc5, 0xfc, 0xfe, 0x9f, 0x97, 0x18, 0x0e, 0x06, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x03, 0x06, 0x0e, 0x89, 0xcf, 0x5f, 0xfe, 0xfa, 0xe3, 0x21, 0x60, 0xe0, 0xe0, 0xc0, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0f, 0x1f, 0x1f, 0x1f, 0x18, 0x08, 0x0f, 0x7f, 0xff, 0xfc, 0xcc, 0x87, 0xc7, 0xc3, 0xe0, 0xcf, 0x9f, 0xf0, 0x60, 0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x30, 0xfe, 0xcf, 0xe1, 0xe1, 0x43, 0x43, 0xc6, 0xf6, 0xff, 0xff, 0x0f, 0x04, 0x06, 0x07, 0x07, 0x07, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0xfc, 0xfe, 0xf6, 0xe3, 0xc3, 0x8f, 0x0f, 0x1e, 0x0c, 0x05, 0x03, 0x07, 0xc7, 0xfe, 0xce, 0xdf, 0x9d, 0xf9, 0x83, 0x83, 0x81, 0xdd, 0xfd, 0xcf, 0xce, 0xff, 0xe7, 0x03, 0x01, 0x02, 0x06, 0x0f, 0x87, 0xc7, 0xe1, 0xf1, 0xff, 0xff, 0x7e, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x1f, 0x3e, 0x3e, 0x7c, 0x78, 0x78, 0xf8, 0xf1, 0xf1, 0xfb, 0x7f, 0x03, 0x03, 0x03, 0x03, 0x03, 0x17, 0x7f, 0x79, 0xf9, 0x78, 0x7c, 0x7c, 0x3e, 0x3e, 0x1f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void delay (uint32_t sec)
{
	 volatile uint32_t i = 0;
	 for (i = 0; (i < (12000 * sec)); ++i)
	 {
			 __asm("NOP"); /* delay */
	 }
}

void print_task (void * args)
{
 for (;;)
 {
	 nokiaLCD_initialise();

	 nokiaLCD_clearDisplay(0);

	 vTaskDelay(portMAX_DELAY);
 }
}

void taskLCDChar (void * args)
{
 char counter = 'A';

 vTaskDelay(pdMS_TO_TICKS(5000));

 for (;;)
 {
	 if (counter > 'Z')
	 {
		 counter = 'A';
	 }

	 nokiaLCD_setChar(counter, 0, 0, 1);

	 nokiaLCD_updateDisplay();

	 counter++;

	 vTaskDelay(pdMS_TO_TICKS(2000));
 }
}

void taskLCDImg (void * args)
{
 for (;;)
 {
	 vTaskDelay(pdMS_TO_TICKS(1000));

	 nokiaLCD_setBitmap(&cinves_Bitmap);

	 nokiaLCD_updateDisplay();

	 vTaskDelay(portMAX_DELAY);
 }
}

// Aqui
typedef struct
{
	uint8_t task;
	uint8_t index;
	uint32_t value;
}alarm_msg_t;

typedef enum{segundos_type, minutos_type, horas_type}time_types_t;
typedef struct
{
	time_types_t time_type;
	uint8_t value;
}time_msg_t;

typedef struct
{
  uint8_t is_init;
  dspi_master_handle_t fsl_spi_handle;
  SemaphoreHandle_t mutex_rx;
  SemaphoreHandle_t mutex_tx;
  SemaphoreHandle_t rx_sem;
  SemaphoreHandle_t tx_sem;
} freertos_spi_handle_t;

typedef struct
{
	uint8_t task;
	uint32_t value;
}spi_print_t;

typedef struct
{
	uint8_t task;
	uint32_t value;
}spi_alarm_t;

typedef struct
{
	QueueHandle_t secsend;
	QueueHandle_t minsend;
}time_handler_t;

static QueueHandle_t SPImailbox;
SemaphoreHandle_t xSemaphore_minutes = NULL;
SemaphoreHandle_t xSemaphore_hours = NULL;
SemaphoreHandle_t xSemaphore_time = NULL;

SemaphoreHandle_t xMutex;

void vTask_0 (void* pvParameters);
void seconds_task (void* pvParameters);
void minutes_task (void* pvParameters);
void hours_task (void* pvParameters);
void alarm_task (void* pvParameters);
void print_task (void* pvParameters);

int main(void) {
    /* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
    /* Init FSL debug console. */
    BOARD_InitDebugConsole();
#endif

    nokiaLCD_initialise();

    PRINTF("Hello World\n");
		nokiaLCD_updateDisplay();
		delay(2000);
		nokiaLCD_clearDisplay(0);
		delay(2000);


    SPImailbox = xQueueCreate(10, sizeof(spi_print_t*));
		SPImailbox = xQueueCreate(10, sizeof(spi_alarm_t*));
    xMutex = xSemaphoreCreateMutex();

    vQueueAddToRegistry(SPImailbox, "SPI Queue");

	 xTaskCreate(vTask_0, "Initial", (configMINIMAL_STACK_SIZE*2), NULL, (configMAX_PRIORITIES-2), NULL);

	 xTaskCreate(taskLCDChar, "Send Char", 400, NULL, 2, NULL);

	 xTaskCreate(taskLCDImg, "Send Img", 400, NULL, 2, NULL);

    vTaskStartScheduler();

    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
   		 nokiaLCD_backlight(1);
   		 delay(500);
   		 nokiaLCD_backlight(0);
   		 delay(500);
   	 }
   	 return 0 ;
}

void vTask_0 (void* pvParameters)
{
	time_handler_t xSemaphore_time = {xSemaphore_minutes, SPImailbox};
	for(;;)
	{
		xTaskCreate(seconds_task, "Seconds", (configMINIMAL_STACK_SIZE*3), NULL, 3, NULL);
		xTaskCreate(minutes_task, "minutos", (configMINIMAL_STACK_SIZE*3), (void*)&xSemaphore_minutes, 3, NULL);
		xTaskCreate(hours_task, "horas", (configMINIMAL_STACK_SIZE*3), (void*)&xSemaphore_time, 3, NULL);
		xTaskCreate(alarm_task, "alarma", (configMINIMAL_STACK_SIZE*3), (void*)&SPImailbox, 3, NULL);
		xTaskCreate(print_task, "Init LCD", 400, NULL, 3, NULL);

		vTaskDelay(portMAX_DELAY);
	}
}


void seconds_task (void* pvParameters)
{
	QueueHandle_t SPImailbox = *((QueueHandle_t*)pvParameters);
	TickType_t xLastWakeTime;
	BaseType_t xWasDelayed;
	uint8_t* pmsg;
	uint8_t seconds;

	for(;;)
	{
		xLastWakeTime = xTaskGetTickCount();
		if (seconds < 60)
		{
			seconds++;
		}
		else
		{
			seconds = 0;
			xSemaphoreGiveFromISR(xSemaphore_minutes, NULL);
		}

		xSemaphoreTake(xMutex, portMAX_DELAY);
		// value = ADC_getValues();
		xSemaphoreGive(xMutex);
		*pmsg = seconds;
		xQueueSend(SPImailbox, &pmsg, portMAX_DELAY);
		xWasDelayed = xTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
	}
}

void minutes_task (void* pvParameters)
{
	QueueHandle_t SPImailbox = *((QueueHandle_t*)pvParameters);
	uint8_t* pmsg;
	uint8_t minutes;

			if(xSemaphoreTake(xSemaphore_minutes,portMAX_DELAY) == pdTRUE)
			{
				if (minutes < 60)
				{
					minutes++;
				}
				else
				{
					minutes = 0;
					xSemaphoreGiveFromISR(xSemaphore_hours, NULL);
				}
			}

		xSemaphoreTake(xMutex, portMAX_DELAY);
		// value = ADC_getValues();
		xSemaphoreGive(xMutex);
		*pmsg = minutes;
		xQueueSend(SPImailbox, &pmsg, portMAX_DELAY);
}

void hours_task (void* pvParameters)
{
	QueueHandle_t SPImailbox = *((QueueHandle_t*)pvParameters);
	uint8_t* pmsg;
	uint8_t hours;

			if(xSemaphoreTake(xSemaphore_hours,portMAX_DELAY) == pdTRUE)
			{
				if (hours < 23)
				{
					hours++;
				}
				else
				{
					hours = 0;
				}
			}

		xSemaphoreTake(xMutex, portMAX_DELAY);
		// value = ADC_getValues();
		xSemaphoreGive(xMutex);
		*pmsg = hours;
		xQueueSend(SPImailbox, &pmsg, portMAX_DELAY);
}

void alarm_task (void* pvParameters)
{

}