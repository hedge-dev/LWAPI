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
        ButtonStates m_HeldButtons;
        ButtonStates m_PressedButtons;
        ButtonStates m_ReleasedButtones;
        csl::math::Vector2 m_LeftStick;
        csl::math::Vector2 m_RightStick;
        float m_LeftTrigger;
        float m_RightTrigger;
        INSERT_PADDING(12);

    	bool IsButtonHeld(ButtonStates buttons) const
    	{
            return (m_HeldButtons & buttons) == buttons;
    	}

        bool IsButtonDown(ButtonStates buttons) const
        {
            return (m_PressedButtons & buttons) == buttons;
        }

        bool IsButtonUp(ButtonStates buttons) const
        {
            return (m_ReleasedButtones & buttons) == buttons;
        }

    	float ButtonToAxis(ButtonStates high, ButtonStates low) const
    	{
            if (IsButtonHeld(high))
                return 1;
            else if (IsButtonHeld(low))
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
        TouchStates m_HeldStates{};
        TouchStates m_PressedStates{};
        TouchStates m_ReleasedStates{};
        csl::math::Vector2 m_Position{};
        bool m_IsBackground{};
    };

    struct ResMotorDeviceData
    {
        INSERT_PADDING(12);
    };
	
	struct ResDeviceData
	{
		struct Repeat
		{
            float m_Time;
            float m_Unk1;
            float m_Unk2;
		};
		
        ResPadDeviceData m_PadData;
		ResGyroDeviceData m_GyroData;
		ResAccDeviceData m_AccData;
		ResTouchDeviceData m_TouchData;
		ResMotorDeviceData m_MotorData;
		Repeat m_RepeatData;
	};
}