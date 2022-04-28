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
			ut::RefPtr<AnimationXMLLoader> m_rpXmlLoader;

		private:
			inline static FUNCTION_PTR(void, __thiscall, ms_fpLoadFromBuffer, ASLR(0x00412CA0), AnimationResContainer*, LoadInfo&, hh::ut::PackFile);

			void PrepareMerge()
			{
				if (m_rpXmlLoader)
					return;

				m_rpXmlLoader = new(m_pAllocator) AnimationXMLLoader();
			}

			void* CreateBuffer(size_t in_size)
			{
				return m_rpXmlLoader->CreateBuffer(in_size);
			}

			template<typename T>
			T* CreateBuffer()
			{
				return new(CreateBuffer(sizeof(T))) T();
			}

			template<typename T>
			T* CreateBuffer(size_t in_count)
			{
				T* pBuffer = static_cast<T*>(CreateBuffer(sizeof(T) * in_count));
				for (size_t i = 0; i < in_count; i++)
					new(&pBuffer[i]) T();

				return pBuffer;
			}

		public:
			AnimationResContainer(csl::fnd::IAllocator& in_allocator) : m_pAllocator(&in_allocator), m_Data(in_allocator)
			{
				
			}

			void LoadFromBuffer(LoadInfo& in_info, hh::ut::PackFile in_pac)
			{
				ms_fpLoadFromBuffer(this, in_info, in_pac);
			}

			bool MergeTransitions(const AnimationResContainer& in_other)
			{
				if (!in_other.m_Data.m_pFile)
					return false;

				return MergeTransitions(in_other.m_Data.m_pFile->m_pTransitions);
			}

			bool MergeTransitions(const TransitionArray* in_other)
			{
				if (!m_Data.m_pFile || !in_other)
					return false;

				PrepareMerge();
				auto& file = *m_Data.m_pFile;
				auto* oldTransitions = file.m_pTransitions;
				if (!oldTransitions)
				{
					file.m_pTransitions = CreateBuffer<TransitionArray>();
					*file.m_pTransitions = *in_other;

					return true;
				}

				file.m_pTransitions = CreateBuffer<TransitionArray>();
				file.m_pTransitions->m_Count = in_other->m_Count + oldTransitions->m_Count;
				file.m_pTransitions->m_pTransitions = CreateBuffer<TransitionInfo>(file.m_pTransitions->m_Count);
				size_t base{};
				for (base = 0; base < oldTransitions->m_Count; ++base)
					file.m_pTransitions->m_pTransitions[base] = oldTransitions->m_pTransitions[base];

				for (size_t i = 0; i < in_other->m_Count; ++i)
					file.m_pTransitions->m_pTransitions[base + i] = in_other->m_pTransitions[i];

				return true;
			}
		};
	}
}