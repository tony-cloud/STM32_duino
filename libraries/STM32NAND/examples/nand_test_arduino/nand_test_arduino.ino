/*  nand_test.ino arduino style nandflash.
      This boards tested:
       ARMFLY_F407ZG       HY27UF082G2A
       HASEE_III_F103ZE    K9F1G08U0A
       REDBULL_V2_F103ZE   K9F1208U0C
*/

#include "bsp.h"
#include <stm32Nand.h>
STM32NAND& myNAND = STM32NAND::getInstance();

#define led1 LED_BUILTIN
void setup() {
  NAND_IDTypeDef  nand_id;
  pinMode(led1, OUTPUT);
  Serial.begin(115200);
  delay(200);
  Serial.println("NAND FLASH ID:");
  delay(200);

  uint8_t status;
  myNAND.Init();
  status = myNAND.readID(&nand_id);

  if (status != HAL_OK) Serial.println("id read err");
  else Serial.println("id read OK");

  Serial.print(nand_id.Maker_Id, HEX);
  Serial.print(" ");
  Serial.print(nand_id.Device_Id, HEX);
  Serial.print(" ");
  Serial.print(nand_id.Third_Id, HEX);
  Serial.print(" ");
  Serial.println(nand_id.Fourth_Id, HEX);

  if ( ( nand_id.Maker_Id == 0xAD ) && (nand_id.Device_Id == 0xF1) &&
       ( nand_id.Third_Id == 0x80 ) && ( nand_id.Fourth_Id == 0x1D))
  {
    Serial.println("Type = HY27UF081G2A");
  }
  else if ( ( nand_id.Maker_Id == 0xAD) && (nand_id.Device_Id == 0xDA))
  {
    Serial.println("Type = HY27UF082G2A");
  }
  else if ( ( nand_id.Maker_Id == 0xEC ) && ( nand_id.Device_Id == 0xF1 ) &&
            ( nand_id.Third_Id == 0x80 ) && ( nand_id.Fourth_Id == 0x15) )
  {
    Serial.println("Type = K9F1G08U0A");
  }
  else if ( ( nand_id.Maker_Id == 0xEC ) && ( nand_id.Device_Id == 0xF1 ) &&
            ( nand_id.Third_Id == 0x00 ) && ( nand_id.Fourth_Id == 0x95 ) )
  {
    Serial.println("Type = K9F1G08U0B");
  }
  else if ( ( nand_id.Maker_Id == 0xEC ) && ( nand_id.Device_Id == 0x76 ) &&
            ( nand_id.Third_Id == 0x5A ) && ( nand_id.Fourth_Id == 0x3F ) )
  {
    Serial.println("Type = K9F1208U0C");
  }
  else
  {
    Serial.println("Type = Unknow");
  }
  Serial.println("\nok!\n");
}

void loop() {
  digitalToggle(led1);
  delay(1000);
}

