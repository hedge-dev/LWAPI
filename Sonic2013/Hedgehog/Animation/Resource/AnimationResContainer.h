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
			const char* Unk1;
			const char* Unk2;
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
			AnimationXMLLoader() { }
			
			void* CreateBuffer(size_t in_size)
			{
				void* buffer = GetAllocator()->Alloc(in_size, 16);
				m_Buffers.push_back(buffer);
				return buffer;
			}

			const char* CreateCharBuffer(const char* in_pStr)
			{
				const size_t len = strlen(in_pStr) + 1;
				void* pBuffer = CreateBuffer(len);
				memcpy(pBuffer, in_pStr, len);
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
		private:
			inline static FUNCTION_PTR(void, __thiscall, ms_fpLoadFromBuffer, ASLR(0x00412CA0), AnimationResContainer*, LoadInfo&, hh::ut::PackFile);

		public:
			struct ResData
			{
				FileHeader* pFile{};
				csl::ut::ObjectMoveArray<ResCharAnim> SimpleAnimations;
				csl::ut::ObjectMoveArray<ResCharAnim> ComplexAnimations;
				csl::ut::ObjectMoveArray<ut::RefPtr<ResCharMirrorAnim>> MirrorAnims;

				ResData(csl::fnd::IAllocator& in_rAllocator) : SimpleAnimations(&in_rAllocator),
					ComplexAnimations(&in_rAllocator), MirrorAnims(&in_rAllocator)
				{
					
				}
			};

			struct LoadInfo
			{
				ResCharAnimScript Script{};
				hh::gfx::res::ResSkeleton Skeleton{};
				csl::ut::MoveArray<MirrorBindData>* pMirrorData{};
			};
			
			csl::fnd::IAllocator* pAllocator{};
			ResData Data;
			ut::RefPtr<AnimationXMLLoader> rpXmlLoader;

		private:
			void PrepareMerge()
			{
				if (rpXmlLoader)
					return;

				rpXmlLoader = new(m_pAllocator) AnimationXMLLoader();
			}

			void* CreateBuffer(size_t in_size)
			{
				return rpXmlLoader->CreateBuffer(in_size);
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
			AnimationResContainer(csl::fnd::IAllocator& in_rAllocator) : m_pAllocator(&in_rAllocator), m_Data(in_rAllocator)
			{
				
			}

			void LoadFromBuffer(LoadInfo& in_rInfo, hh::ut::PackFile in_pac)
			{
				ms_fpLoadFromBuffer(this, in_rInfo, in_pac);
			}

			bool MergeTransitions(const AnimationResContainer& in_rOther)
			{
				if (!in_rOther.Data.pFile)
					return false;

				return MergeTransitions(in_rOther.Data.pFile->pTransitions);
			}

			bool MergeTransitions(const TransitionArray* in_pOther)
			{
				if (!Data.pFile || !in_pOther)
					return false;

				PrepareMerge();
				auto& file = *Data.pFile;
				auto* pOldTransitions = file.pTransitions;
				if (!pOldTransitions)
				{
					file.pTransitions = CreateBuffer<TransitionArray>();
					*file.pTransitions = *in_pOther;

					return true;
				}

				file.pTransitions = CreateBuffer<TransitionArray>();
				file.pTransitions->Count = in_pOther->Count + pOldTransitions->Count;
				file.pTransitions->pTransitions = CreateBuffer<TransitionInfo>(file.pTransitions->Count);
				size_t base{};
				for (base = 0; base < pOldTransitions->Count; ++base)
					file.pTransitions->pTransitions[base] = pOldTransitions->pTransitions[base];

				for (size_t i = 0; i < in_pOther->Count; ++i)
					file.pTransitions->pTransitions[base + i] = in_pOther->pTransitions[i];

				return true;
			}
		};
	}
}