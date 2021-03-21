#pragma once

namespace app::hid
{
	typedef void ResSendDeviceData;

	class DevicePlatformBase : public fnd::ReferencedObject
	{
		DEFINE_RTTI;

	public:
		virtual DEFINE_RTTI_GETTER;

		virtual void Poll(float time)
		{
			
		}

		[[nodiscard]] virtual uint GetPortMax() const
		{
			return 0;
		}

		virtual bool GetDeviceData(ResSendDeviceData* data, uint port)
		{
			return false;
		}

		virtual bool SendDeviceData(uint a1, uint a2, const ResSendDeviceData* data, bool a4)
		{
			return false;
		}

		virtual bool ChangeDeviceData(const ResDeviceData* a1, const ResDeviceData* a2, uint a3)
		{
			return false;
		}

		virtual	bool IsActive(uint port) const
		{
			return false;
		}
	};
}