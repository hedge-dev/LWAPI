#pragma once

namespace app::hid
{
	enum TouchStates
	{
		TOUCH_PRIMARY = 1,
		TOUCH_ACTIVE = 0x800000
	};
	
    enum ButtonStates
    {
        BUTTON_A = 1,
        BUTTON_B = 2,
        BUTTON_X = 4,
        BUTTON_Y = 8,
        BUTTON_UP = 0x10,
        BUTTON_DOWN = 0x20,
        BUTTON_LEFT = 0x40,
        BUTTON_RIGHT = 0x80,
        BUTTON_L1 = 0x100,
        BUTTON_R1 = 0x200,
        BUTTON_L2 = 0x400,
        BUTTON_R2 = 0x800,
        BUTTON_L3 = 0x1000,
        BUTTON_R3 = 0x2000,
        BUTTON_START = 0x4000,
        BUTTON_SELECT = 0x8000,
        LAXIS_UP = 0x10000,
        LAXIS_DOWN = 0x20000,
        LAXIS_LEFT = 0x40000,
        LAXIS_RIGHT = 0x80000,
        RAXIS_UP = 0x100000,
        RAXIS_DOWN = 0x200000,
        RAXIS_LEFT = 0x400000,
        RAXIS_RIGHT = 0x800000,
    };

    struct ResPadDeviceData
    {
        ButtonStates HeldButtons;
        ButtonStates PressedButtons;
        ButtonStates ReleasedButtones;
        csl::math::Vector2 LeftStick;
        csl::math::Vector2 RightStick;
        float LeftTrigger;
        float RightTrigger;
        INSERT_PADDING(12);

    	bool IsButtonHeld(ButtonStates in_buttons) const
    	{
            return (HeldButtons & in_buttons) == in_buttons;
    	}

        bool IsButtonDown(ButtonStates in_buttons) const
        {
            return (PressedButtons & in_buttons) == in_buttons;
        }

        bool IsButtonUp(ButtonStates in_buttons) const
        {
            return (ReleasedButtones & in_buttons) == in_buttons;
        }

    	float ButtonToAxis(ButtonStates in_high, ButtonStates in_low) const
    	{
            if (IsButtonHeld(in_high))
                return 1;
            else if (IsButtonHeld(in_low))
                return -1;
            
            return 0;
    	}
    };

    struct ResGyroDeviceData
    {
        INSERT_PADDING(64);
    };

    struct ResAccDeviceData
    {
        INSERT_PADDING(32);
    };

    struct ResTouchDeviceData
    {
        TouchStates HeldStates{};
        TouchStates PressedStates{};
        TouchStates ReleasedStates{};
        csl::math::Vector2 Position{};
        bool IsBackground{};
    };

    struct ResMotorDeviceData
    {
        INSERT_PADDING(12);
    };
	
	struct ResDeviceData
	{
		struct Repeat
		{
            float Time;
            float Unk1;
            float Unk2;
		};
		
        ResPadDeviceData PadData;
		ResGyroDeviceData GyroData;
		ResAccDeviceData AccData;
		ResTouchDeviceData TouchData;
		ResMotorDeviceData MotorData;
		Repeat RepeatData;
	};
}