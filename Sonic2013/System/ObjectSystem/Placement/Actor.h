#pragma once

namespace app
{
	class CSetAdapter;
	namespace Gops
	{
		class CActorPack;
		class CActor : CWorldHandle
		{
		public:
			csl::ut::LinkListNode m_ListNode{};

		protected:
			CActorPack* m_pPack;
			SetEd::CResObject m_Object{ nullptr };
			size_t m_UnitNum{};
			CSetAdapter* m_pAdapter{};
			const game::ActorGroupInfo* m_pGroupInfo{};
			csl::math::Vector3 m_Position{};

		public:
			void* m_Unk1{};
			
			CActorPack* GetPack() const
			{
				return m_pPack;
			}
			
			const csl::math::Vector3& GetPosition() const
			{
				return m_Position;
			}

			const game::ActorGroupInfo* GetGroupInfo() const
			{
				return m_pGroupInfo;
			}

			SetEd::CResObject GetResObject() const
			{
				return m_Object;
			}

			CSetAdapter* GetAdapter() const
			{
				return m_pAdapter;
			}
			
			size_t GetUnitNum() const
			{
				return m_UnitNum;
			}
		};
	}
}