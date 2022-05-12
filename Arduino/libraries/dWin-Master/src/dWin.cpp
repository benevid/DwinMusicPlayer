/* *******************************************************************************
 *  Copyright (C) 2014-2022 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: dWin HMI LCD Screen Library.
 *	Code Developer		: Mehmet Gunce Akkoyun (akkoyun@me.com)
 *	Code Developer		: Recep Senbas (recepsenbas@gmail.com)
 *
 *********************************************************************************/

#include <dWin.h>

// Global Functions
bool dwin::Set_HMI_Begin(void)
{

	// Serial Begin
	HMI_Serial.begin(HMI_Serial_Baud);

	return (true);
}

bool dwin::Set_HMI_Page(uint8_t _Page_ID)
{

	// Control for Limits
	if (_Page_ID < 0)
		return (false);

	// Declare Default Data Array
	char Data[4] = {0x5A, 0x01, 0x00, 0x00};

	// Set Data Low/High Byte
	Data[3] = _Page_ID;

	// Send Data Pack
	Write_VP(0x0084, POINTER, Data, sizeof(Data));

	// End Function
	return (true);
}
bool dwin::Set_HMI_Sleep(bool _Status)
{

	// Data[0] - ON State Brightnes
	// Data[1] - Sleep State Brightnes
	// Data[2] - Sleep Time
	// Data[3] - Sleep Time

	// Declare Default Data Array
	char Data[4] = {0x64, 0x64, 0x0B, 0xB8};

	// Sleep State ON
	if (_Status)
		Data[1] = 0x00;

	// Send Data Pack
	Write_VP(0x0082, POINTER, Data, sizeof(Data));

	// End Function
	return (true);
}
bool dwin::Set_Int_Value(uint16_t _VP, uint16_t _Value)
{
	// Declare Default Data Array
	char Data[2] = {0x00, 0x00};

	// Set Data Low/High Byte
	Data[1] = (_Value & (uint16_t)0x00FF);
	Data[0] = ((_Value & (uint16_t)0xFF00) >> 8);

	// Send Data Pack
	Write_VP(_VP, POINTER, Data, sizeof(Data));

	// End Function
	return (true);
}
bool dwin::Set_Big_Int_Value(uint16_t _VP, uint32_t _Value)
{

	// Declare Default Data Array
	char Data[4];

	// Set Data Low/High Byte
	// Data[1] = (_Value & (uint16_t)0x00FF);
	// Data[0] = ((_Value & (uint16_t)0xFF00) >> 8);
	Data[0] = (_Value >> 24) & 0xFF;
	Data[1] = (_Value >> 16) & 0xFF;
	Data[2] = (_Value >> 8) & 0xFF;
	Data[3] = _Value & 0xFF;

	// Send Data Pack
	Write_VP(_VP, POINTER, Data, sizeof(Data));

	// End Function
	return (true);
}
bool dwin::Set_Float_Value(uint16_t _VP, float _Value)
{

	// Declare Default Data Array
	char Data[] = {0x00, 0x00};

	// Convert Value
	uint16_t _Value_RAW = uint16_t(_Value * 100);

	// Set Data Low/High Byte
	Data[1] = (_Value_RAW & (uint16_t)0x00FF);
	Data[0] = ((_Value_RAW & (uint16_t)0xFF00) >> 8);

	// Send Data Pack
	Write_VP(_VP, POINTER, Data, sizeof(Data));

	// End Function
	return (true);
}
bool dwin::Set_HMI_Text_Message(uint16_t _VP, const String _Message, uint16_t limit)
{

	unsigned int _textLength = _Message.length() + 1;

	// Log.println("TextLenght:");
	// Log.print(_textLength);

	// Declare Data Variable
	char _Data[_textLength];
	// Convert Data to Array
	_Message.toCharArray(_Data, _textLength);

	// Send Data Pack
	Write_VP(_VP, TEXT, _Data, sizeof(_Data));

	// End Function
	return (true);
}
/*
 *  Clear text display
 *	5AA5 05 82 5020 2020 2020
 */
bool dwin::Set_HMI_Clear_Text(uint16_t _Address, uint8_t _Size)
{

	// Set Address Low Byte
	uint8_t _Address_Low = (_Address & (uint16_t)0x00FF);

	// Get Address High Byte
	uint8_t _Address_High = ((_Address & (uint16_t)0xFF00) >> 8);

	// Define Length variable
	uint8_t _Pack_Length = _Size;

	HMI_Serial.write(0x5A);
	delay(1);
	HMI_Serial.write(0xA5);
	delay(1);
	HMI_Serial.write(_Pack_Length);
	delay(1);
	HMI_Serial.write(0x82);
	delay(1);
	HMI_Serial.write(_Address_High);
	delay(1);
	HMI_Serial.write(_Address_Low);
	delay(1);

	for (uint8_t i = 0; i < _Size; i++)
	{
		HMI_Serial.write(0x20);
		delay(1);
	}
	HMI_Serial.write(0xFF);
	HMI_Serial.write(0xFF);

	// Command Delay
	delay(10);

	// End Function
	return (true);
}

// Private Functions
bool dwin::Write_VP(const uint16_t _Address, uint8_t _Data_Type, const char *_Data, uint8_t _Size)
{

	// Set Address Low Byte
	uint8_t _Address_Low = (_Address & (uint16_t)0x00FF);

	// Get Address High Byte
	uint8_t _Address_High = ((_Address & (uint16_t)0xFF00) >> 8);

	// Define Length variable
	uint8_t _Pack_Length = _Size + 3;

	//  if (_Data_Type == TEXT)
	//  {
	//  	_Pack_Length = _Size+6;
	//  }

	// Log.println("Lenght:");
	// Log.print(_Pack_Length);
	// Log.println("Data:");
	// //Log.print(_Data);
	// Set Pack Header
	HMI_Serial.write(0x5A);
	delay(1);
	HMI_Serial.write(0xA5);
	delay(1);
	HMI_Serial.write(_Pack_Length);
	delay(1);
	HMI_Serial.write(0x82);
	delay(1);
	HMI_Serial.write(_Address_High);
	delay(1);
	HMI_Serial.write(_Address_Low);
	delay(1);

	// Send Pack

	for (uint8_t i = 0; i < _Size; i++)
	{
		HMI_Serial.write(_Data[i]);
		// Log.print(_Data[i]);
		delay(1);
	}

	// Control for Data Type
	if (_Data_Type == TEXT)
	{
		HMI_Serial.write(0xFF);
		HMI_Serial.write(0xFF);
	}

	// Command Delay
	delay(10);

	// End Function
	return (true);
}

// Define Library Class
dwin LCD;

// 1903