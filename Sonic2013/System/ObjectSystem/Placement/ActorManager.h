#pragma once
#include <memory>

namespace app::Gops
{
	class CGopsWorld;
	struct SActorPackTag
	{
		size_t m_Tag;
		CActorPack* m_pPack;
	};

	class CActorListener
	{
	public:
		virtual ~CActorListener() = default;
		virtual void ActorAddedCallback(CActor* pActor) {}
		virtual void ActorRemovedCallback(CActor* pActor) {}
	};
	
	class CActorManager
	{
	private:
		bool m_IsOptimized;

	protected:
		float m_RangeIn;
		void* m_Unk1;
		app::TArray<SActorPackTag, std::dummy::allocator<SActorPackTag>> m_PackTags;
		size_t m_PackCount;
		csl::ut::ObjectMoveArray<csl::ut::LinkList<CActorPack>> m_Packs{ csl::fnd::Singleton<app::GameObjectSystem>::GetInstance()->GetPooledAllocator() };
		std::unique_ptr<CGopsWorld> m_pWorld; // boost::scoped_ptr<CGopsWorld>
		app::TArray<CActorListener*, std::dummy::allocator<CActorListener*>> m_Listeners;

	public:
		SActorPackTag* FindTag(size_t tag) const
		{
			for (auto& packTag : m_PackTags)
			{
				if (packTag.m_Tag == tag)
				{
					return &packTag;
				}
			}
			
			return m_PackTags.end();
		}
		
		CActorPack* FindPack(size_t tag)
		{
			auto* pTag = FindTag(tag);
			if (pTag == m_PackTags.end())
				return nullptr;

			return pTag->m_pPack;
		}
	};
}