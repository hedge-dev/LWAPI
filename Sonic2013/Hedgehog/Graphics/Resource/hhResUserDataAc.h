#pragma once

namespace hh::gfx::res
{
	struct ResUserDataItemData
	{
		void* Unknown1{};
		void* Unknown2{};
		void* Unknown3{};
		void* Unknown4{};
		ResNameData Name{};
	};

	class ResUserDataItem : public hh::ut::ResCommon<ResUserDataItemData>
	{
		ResName GetName()
		{
			return { &m_pRes->Name };
		}
	};

	struct ResUserDataData
	{
		uint ItemCount{};
		ResUserDataItemData* pItems{};
	};

	class ResUserData : public hh::ut::ResCommon<ResUserDataData>
	{
		uint GetNumResUserDataItems() const
		{
			return m_pRes->ItemCount;
		}

		ResUserDataItem GetResUserDataItem(uint in_index) const
		{
			if (m_pRes->ItemCount <= in_index)
				return { nullptr };

			return { &m_pRes->pItems[in_index] };
		}
	};
}