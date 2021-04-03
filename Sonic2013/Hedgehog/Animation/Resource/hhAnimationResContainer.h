#pragma once

namespace hh::gfx::res
{
	class ResSkeleton;
	using ResSkeletonData = ResSkeleton;
}

namespace app
{
	class ResCharAnimScript;

	namespace animation
	{
		struct MirrorBindData
		{
			void* m_Unk1;
			void* m_Unk2;
		};
		
		class ResCharMirrorAnim : public fnd::ReferencedObject
		{
			INSERT_PADDING(12) {};
		};

		class AnimationXMLLoader : public fnd::ReferencedObject
		{
		protected:
			void* m_pUnk1{};
			csl::ut::MoveArray<void*> m_Buffers{ GetAllocator() };

		public:
			void* CreateBuffer(size_t size)
			{
				void* buffer = GetAllocator()->Alloc(size, 16);
				m_Buffers.push_back(buffer);
				return buffer;
			}

			const char* CreateCharBuffer(const char* pStr)
			{
				const size_t len = strlen(pStr) + 1;
				void* pBuffer = CreateBuffer(len);
				memcpy(pBuffer, pStr, len);
				return static_cast<const char*>(pBuffer);
			}

			~AnimationXMLLoader()
			{
				for (auto& buffer : m_Buffers)
					GetAllocator()->Free(buffer);
			}
		};

		class AnimationResContainer
		{
		public:
			struct LoadInfo
			{
				ResCharAnimScript* m_pScript{};
				hh::gfx::res::ResSkeletonData* m_pSkeleton{};
				csl::ut::MoveArray<MirrorBindData>* m_pMirrorData{};
			};

		protected:
			csl::fnd::IAllocator* m_pAllocator{};
			void* m_Unk1{};
			csl::ut::ObjectMoveArray<ResCharAnim> m_Anims{ m_pAllocator }; // Simple and complex animations?
			csl::ut::ObjectMoveArray<ResCharAnim> m_Anims2{ m_pAllocator };
			csl::ut::ObjectMoveArray<ut::RefPtr<ResCharMirrorAnim>> m_MirrorAnims{ m_pAllocator };
			ut::RefPtr<AnimationXMLLoader> m_rpLoader;

			inline static FUNCTION_PTR(void, __thiscall, ms_fpLoadFromBuffer, ASLR(0x00412CA0), AnimationResContainer*, LoadInfo&, hh::ut::PackFile);
		public:
			AnimationResContainer(csl::fnd::IAllocator& rAllocator) : m_pAllocator(&rAllocator)
			{
				
			}
			
			void LoadFromBuffer(LoadInfo& rInfo, hh::ut::PackFile pac)
			{
				ms_fpLoadFromBuffer(this, rInfo, pac);
			}
		};
	}
}