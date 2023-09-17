#pragma once

namespace app::Player
{
	struct SStateParameter
	{
	public:
		inline static const char* ms_pName = (const char*)ASLR(0x00DFCBE4);

		int m_Unk1{};

		virtual SStateParameter* Clone(csl::fnd::IAllocator& in_rAlloc) const
		{
			auto* pParam = static_cast<SStateParameter*>(in_rAlloc.Alloc(sizeof(SStateParameter), 32));
			*pParam = { *this };

			return pParam;
		}

		virtual const char* GetName() const
		{
			return ms_pName;
		}

		virtual ~SStateParameter() = default;
	};

	class CPlayerStateParameter
	{
	public:
		csl::fnd::IAllocator* pAllocator{};
		csl::ut::ObjectMoveArray<SStateParameter*> Parameters{};

		CPlayerStateParameter(csl::fnd::IAllocator* in_pAllocator) : pAllocator(in_pAllocator), Parameters(in_pAllocator)
		{
			//CreateParameter<RelayedFlagParameter>();
			//CreateParameter<JumpParameter>();
			//CreateParameter<StompingParameter>();
			//CreateParameter<SpinDashParameter>();
			//CreateParameter<HomingParameter>();
		}

		template <typename T>
		T* CreateParameter()
		{
			T* pParam = static_cast<T*>(pAllocator->Alloc(sizeof(T), 32));
			pParam = new(pParam) T();
			
			if (!pParam)
				return pParam;

			Parameters.push_back(pParam);

			return pParam;
		}

		SStateParameter* GetParam(const char* in_pName)
		{
			for (auto* pParam : Parameters)
			{
				if (pParam->GetName() == in_pName)
					return pParam;
			}

			return { nullptr };
		}
	};
}