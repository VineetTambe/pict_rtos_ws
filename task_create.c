/* Hello World Example
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this

   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

//#define 1kb 1000
#define byte char

void vTaskAllocate(void*);
void vTaskdeallocate(void*);

bool flag = false;
char *mem=NULL;
void app_main(void)
{
    printf("\nprogram start\n\n");
    printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());
    
    xTaskCreate(vTaskAllocate,"Allocate",10000,NULL,1,NULL);
    xTaskCreate(vTaskdeallocate,"Deallocate",10000,NULL,1,NULL);

   
/*
    printf("Hello world!\n");

    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    printf("This is %s chip with %d CPU core(s), WiFi%s%s, ",
            CONFIG_IDF_TARGET,
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    printf("silicon revision %d, ", chip_info.revision);

    printf("%dMB %s flash\n", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");
    printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());

    for (int i = 10; i >= 0; i--) {
        printf("Restarting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    printf("Restarting now.\n");
    fflush(stdout);
    esp_restart();*/
}

void vTaskAllocate(void* param){
    while(1){
	if(!flag){
	 
	  printf("Allocating 1024 bytes == 1KB of memory on heap\n");

    	  mem = (char*)malloc(1024);
	  printf("Minimum free heap size: %d bytes\n", esp_get_minimum_free_heap_size());
        vTaskDelay(500 / portTICK_PERIOD_MS);
	 flag = true;
	}
    }
    vTaskDelete(NULL);
}

void vTaskdeallocate(void* param){
    while(1){
      if(flag){
	    
	    printf("Deallocating 1024 = 1KB of memory on heap\n");
	    free(mem);
	    mem = NULL;
	    printf("Minimum free heap size: %d bytes\n\n\n\n", esp_get_minimum_free_heap_size());
	    vTaskDelay(499 / portTICK_PERIOD_MS);
	    flag = false;
        }
   }
    vTaskDelete(NULL);
}
