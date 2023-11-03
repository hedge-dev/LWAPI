#pragma once

namespace app::hid
{
	typedef void ResSendDeviceData;

	class DevicePlatformBase : public fnd::ReferencedObject
	{
		DEFINE_RTTI;

	public:
		virtual DEFINE_RTTI_GETTER;

		virtual void Poll(float in_time)
		{
			
		}

		[[nodiscard]] virtual uint GetPortMax() const
		{
			return 0;
		}

		virtual bool GetDeviceData(ResSendDeviceData* in_pData, uint in_port)
		{
			return false;
		}

		virtual bool SendDeviceData(uint in_a1, uint in_a2, const ResSendDeviceData* in_pData, bool in_a4)
		{
			return false;
		}

		virtual bool ChangeDeviceData(const ResDeviceData* in_pA1, const ResDeviceData* in_pA2, uint in_a3)
		{
			return false;
		}

		virtual	bool IsActive(uint in_port) const
		{
			return false;
		}
	};
}