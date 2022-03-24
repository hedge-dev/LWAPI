#pragma once

namespace csl::math
{
	struct Frustum;
}

namespace hh::gfx
{
	class SceneNode : public GfxObject
	{
	public:
		typedef void UpdateAnimationCallback_t(SceneNode* in_pObj, uint in_a2);
		typedef void UpdateFrameCallback_t(SceneNode* in_pObj, float in_delta);
		typedef void UpdateViewCallback_t(SceneNode* in_pObj, csl::math::Frustum* in_pFrustum);
		typedef void UpdateTransformCallback_t(SceneNode* in_pObj);

		INSERT_PADDING(8) {};
		UpdateAnimationCallback_t* m_pAnimUpdateCallback{};
		UpdateTransformCallback_t* m_pTransformUpdateCallback{};
		UpdateViewCallback_t* m_pViewUpdateCallback{};
		UpdateFrameCallback_t* m_pFrameUpdateCallback{};
		uint m_Unk1{};

		// csl::ut::Children<hh::gfx::SceneNode, hh::gfx::SceneNode, csl::ut::ChildrenDetacher<hh::gfx::SceneNode>, csl::ut::MoveArray<hh::gfx::SceneNode *>>
		struct
		{
			csl::ut::MoveArray<SceneNode*> m_Container{};
			INSERT_PADDING(8) {};
		} m_Children;
		uint m_Flags{ 0x81F61 };
		INSERT_PADDING(8) {};

		SceneNode(csl::fnd::IAllocator* in_pAllocator, bool a2) : GfxObject(in_pAllocator)
		{
			m_Children.m_Container = { in_pAllocator };
			if (a2)
				m_Flags |= 0x10000;

			m_pAnimUpdateCallback = UpdateAnimation;
			m_pTransformUpdateCallback = UpdateTransform;
			m_pViewUpdateCallback = UpdateView;
			m_pFrameUpdateCallback = UpdateFrame;
		}

		inline static void UpdateAnimation(SceneNode* in_pObj, uint in_a2)
		{
			
		}

		inline static void UpdateTransform(SceneNode* in_pObj)
		{

		}

		inline static void UpdateView(SceneNode* in_pObj, csl::math::Frustum* in_pFrustum)
		{

		}

		inline static void UpdateFrame(SceneNode* in_pObj, float in_delta)
		{

		}
	};
}