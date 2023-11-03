#pragma once

namespace app::hid
{	
	class DeviceBase : public fnd::ReferencedObject
	{
	public:
		virtual void Poll(float time)
		{
			
		}

		[[nodiscard]] virtual uint GetPortMax() const
		{
			return 0;
		}

		virtual bool GetDeviceData(ResDeviceData* data, uint port)
		{
			return false;
		}

		virtual bool SendDeviceData(uint a1, uint a2, const ResSendDeviceData* data)
		{
			return false;
		}
	};
}