#pragma once

namespace app::hid
{
	class DeviceManager : public fnd::ReferencedObject, csl::fnd::SingletonPointer<DeviceManager>
	{
	public:
		inline static FUNCTION_PTR(ResDeviceData*, __thiscall, ms_fpGetDeviceData, ASLR(0x004F66E0), void*, uint, uint);
		
		void* pImpl;

		ResDeviceData* GetDeviceData(uint in_port, uint in_type)
		{
			return ms_fpGetDeviceData(this, in_port, in_type);
		}
	};
}

DEFINE_SINGLETONPTR(app::hid::DeviceManager, ASLR(0x0FD3F90));