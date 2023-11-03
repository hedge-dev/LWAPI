#pragma once

namespace app
{
	struct SYoshiCoinParam
	{
		enum SetPlaceType : uint8
		{
			PLACETYPE_NORMAL,
			PLACETYPE_MOVEABLE
		};

		enum EventType : uint8
		{
			EVENT_NONE,
			EVENT_VISIBLE,
			EVENT_INVISIBLE
		};

	public:
		float ResetTime;
		bool IsReset;
		SetPlaceType SetPlaceType;
		EventType EventType;
	};

	static void paramMap_ObjYoshiCoin(SetEd::CResClass in_rClass)
	{		
		FUNCTION_PTR(void, __thiscall, fpparamMap_ObjYoshiCoin, ASLR(0x00616D70), SetEd::CResClass);
		
		fpparamMap_ObjYoshiCoin(in_rClass);
	}
}