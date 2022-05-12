/* *******************************************************************************
 *  Copyright (C) 2014-2022 Mehmet Gunce Akkoyun Can not be copied and/or
 *	distributed without the express permission of Mehmet Gunce Akkoyun.
 *
 *	Library				: dWin HMI LCD Screen Library.
 *	Code Developer		: Mehmet Gunce Akkoyun (akkoyun@me.com)
 *	Code Developer		: Recep Senbas (recepsenbas@gmail.com)
 *
 *********************************************************************************/

#ifndef __dWin__
#define __dWin__

// Define Arduino Library
#ifndef __Arduino__
#include <Arduino.h>
#endif

#define HMI_Serial Serial1
#define Log Serial
#define	HMI_Serial_Baud 115200

class dwin {

	public:

		enum Data_Type {
			POINTER						= 0,				// 0
			TEXT						= 1,				// 1
			PRESSURE					= 2					// 2
		};

		bool Set_HMI_Begin(void);

		// Tool Functions
		bool Set_HMI_Page(uint8_t _Page_ID);
		bool Set_HMI_Sleep(bool _Status);

		// Information Functions
		bool Set_HMI_Time_Stamp(uint8_t _Day, uint8_t _Month, uint8_t _Year, uint8_t _Hour, uint8_t _Minute, uint8_t _Second);
		bool Set_Int_Value(uint16_t _VP, uint16_t _Value);
		bool Set_Big_Int_Value(uint16_t _VP, uint32_t _Value);
		bool Set_Float_Value(uint16_t _VP, float _Value);
		bool Set_HMI_Text_Message(uint16_t _VP, const String _Message, uint16_t limit);
		bool Set_HMI_Clear_Text(uint16_t _Address, uint8_t _Size);

		

	private:

		// Color Constants
		const char Color_Black[2] = {0x00, 0x00};
		const char Color_White[2] = {0xFF, 0xFF};
		const char Color_Red[2] = {0xF8, 0x00};
		const char Color_Green[2] = {0x07, 0x40};
		const char Color_Gray[2] = {0xAD, 0x55};

		bool Write_VP(const uint16_t _Address, uint8_t _Data_Type, const char *_Data, uint8_t _Size);

};

extern dwin LCD;

#endif /* defined(__dWin_Arduino__) */