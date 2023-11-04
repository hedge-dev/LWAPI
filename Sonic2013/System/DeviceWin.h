#pragma once

namespace app::hid
{
	class DeviceWin : public DeviceBase, csl::fnd::SingletonPointer<DeviceWin>
	{
	protected:
		csl::ut::InplaceMoveArray<DevicePlatformBase*, 8> m_Devices{ nullptr };
		uint m_MaxPort{};

	public:
		[[nodiscard]] uint GetPortMax() const override
		{
			return m_MaxPort;
		}

		[[nodiscard]] const csl::ut::MoveArray<DevicePlatformBase*>* GetDevices() const
		{
			return &m_Devices;
		}
		
		//void AddDevice(DevicePlatformBase* device)
		//{
		//	m_Devices.change_allocator(GetAllocator());

		//	device->AddRef();
		//	m_Devices.push_back(device);
		//}

		//void RemoveDevice(const DevicePlatformBase* device)
		//{
		//	uint index = -1;

		//	for (int i = 0; i < m_Devices.size(); i++)
		//	{
		//		if (m_Devices[i] == device)
		//		{
		//			index = i;
		//			break;
		//		}
		//	}
		//	
		//	if (index == (uint)-1)
		//		return;

		//	m_Devices.remove(index);
		//}
	};
}

inline DEFINE_SINGLETONPTR(app::hid::DeviceWin, ASLR(0x00FD3CC0));