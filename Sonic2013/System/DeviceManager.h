#pragma once

namespace app::hid
{
	class DeviceManager : public fnd::ReferencedObject, csl::fnd::SingletonPointer<DeviceManager>
	{
	public:
		inline static FUNCTION_PTR(ResDeviceData*, __thiscall, ms_fpGetDeviceData, ASLR(0x004F66E0), void* pThis, uint port, uint type);
		
		void* m_pImpl;

		ResDeviceData* GetDeviceData(uint port, uint type)
		{
			return ms_fpGetDeviceData(this, port, type);
		}
	};
}

DEFINE_SINGLETONPTR(app::hid::DeviceManager, ASLR(0x0FD3F90));