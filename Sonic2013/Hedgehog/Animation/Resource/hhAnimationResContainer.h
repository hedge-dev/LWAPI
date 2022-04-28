#pragma once

namespace hh::gfx::res
{
	class ResSkeleton;
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
			struct ResData
			{
				FileHeader* m_pFile{};
				csl::ut::ObjectMoveArray<ResCharAnim> m_SimpleAnimations;
				csl::ut::ObjectMoveArray<ResCharAnim> m_ComplexAnimations;
				csl::ut::ObjectMoveArray<ut::RefPtr<ResCharMirrorAnim>> m_MirrorAnims;

				ResData(csl::fnd::IAllocator& in_allocator) : m_SimpleAnimations(&in_allocator),
					m_ComplexAnimations(&in_allocator), m_MirrorAnims(&in_allocator)
				{
					
				}
			};

			struct LoadInfo
			{
				ResCharAnimScript m_Script{};
				hh::gfx::res::ResSkeleton m_Skeleton{};
				csl::ut::MoveArray<MirrorBindData>* m_pMirrorData{};
			};
			
			csl::fnd::IAllocator* m_pAllocator{};
			ResData m_Data;
			ut::RefPtr<AnimationXMLLoader> m_rpLoader;

		private:
			inline static FUNCTION_PTR(void, __thiscall, ms_fpLoadFromBuffer, ASLR(0x00412CA0), AnimationResContainer*, LoadInfo&, hh::ut::PackFile);
		public:
			AnimationResContainer(csl::fnd::IAllocator& in_allocator) : m_pAllocator(&in_allocator), m_Data(in_allocator)
			{
				
			}
			
			void LoadFromBuffer(LoadInfo& in_info, hh::ut::PackFile in_pac)
			{
				ms_fpLoadFromBuffer(this, in_info, in_pac);
			}
		};
	}
}