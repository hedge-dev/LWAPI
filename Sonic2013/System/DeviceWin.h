#pragma once

namespace app::hid
{
	class DeviceWin : public DeviceBase, csl::fnd::SingletonPointer<DeviceWin>
	{
	protected:
		csl::ut::InplaceMoveArray<DevicePlatformBase*, 8> devices{ nullptr };
		uint maxPort{};

	public:
		[[nodiscard]] uint GetPortMax() const override
		{
			return maxPort;
		}

		[[nodiscard]] const csl::ut::MoveArray<DevicePlatformBase*>* GetDevices() const
		{
			return &devices;
		}

		
		//void AddDevice(DevicePlatformBase* device)
		//{
		//	devices.change_allocator(GetAllocator());

		//	device->AddRef();
		//	devices.push_back(device);
		//}

		//void RemoveDevice(const DevicePlatformBase* device)
		//{
		//	uint index = -1;

		//	for (int i = 0; i < devices.size(); i++)
		//	{
		//		if (devices[i] == device)
		//		{
		//			index = i;
		//			break;
		//		}
		//	}
		//	
		//	if (index == (uint)-1)
		//		return;

		//	devices.remove(index);
		//}
	};
}

inline DEFINE_SINGLETONPTR(app::hid::DeviceWin, ASLR(0x00FD3CC0));