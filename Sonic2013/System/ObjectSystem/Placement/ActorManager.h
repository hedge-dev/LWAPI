#pragma once
#include <memory>

namespace app::Gops
{
	class CGopsWorld;
	
	struct SActorPackTag
	{
		size_t Tag;
		CActorPack* pPack;
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

	public:
		float RangeIn;
		void* Unk1;
		app::TArray<SActorPackTag, std::dummy::allocator<SActorPackTag>> PackTags;
		size_t PackCount;
		csl::ut::ObjectMoveArray<csl::ut::LinkList<CActorPack>> Packs{ csl::fnd::Singleton<app::GameObjectSystem>::GetInstance()->GetPooledAllocator() };
		std::unique_ptr<CGopsWorld> pWorld; // boost::scoped_ptr<CGopsWorld>
		app::TArray<CActorListener*, std::dummy::allocator<CActorListener*>> Listeners;

		SActorPackTag* FindTag(size_t in_tag) const
		{
			for (auto& packTag : PackTags)
			{
				if (packTag.Tag == in_tag)
				{
					return &packTag;
				}
			}
			
			return PackTags.end();
		}
		
		CActorPack* FindPack(size_t in_tag)
		{
			auto* pTag = FindTag(in_tag);
			if (pTag == PackTags.end())
				return nullptr;

			return pTag->pPack;
		}
	};
}