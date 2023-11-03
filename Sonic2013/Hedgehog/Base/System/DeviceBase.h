#pragma once

namespace app::hid
{	
	class DeviceBase : public fnd::ReferencedObject
	{
	public:
		virtual void Poll(float in_time)
		{
			
		}

		[[nodiscard]] virtual uint GetPortMax() const
		{
			return 0;
		}

		virtual bool GetDeviceData(ResDeviceData* in_pData, uint in_port)
		{
			return false;
		}

		virtual bool SendDeviceData(uint in_a1, uint in_a2, const ResSendDeviceData* in_pData)
		{
			return false;
		}
	};
}