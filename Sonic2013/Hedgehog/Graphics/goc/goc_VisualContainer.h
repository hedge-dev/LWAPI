#pragma once

namespace app::fnd
{
	class GOCVisualContainer : public GOCVisual
	{
	private:
		inline static GOComponentClass* ms_pStaticClass = reinterpret_cast<GOComponentClass*>(ASLR(0x00FD4254));

	public:
		struct Description
		{
			size_t VisualCount;
		};
		
		csl::ut::InplaceMoveArray<GOCVisual*, 2> Visuals{ GetAllocator() };

		static GOComponentClass* staticClass()
		{
			return ms_pStaticClass;
		}
		
		void Setup(const Description& in_rDesc)
		{
			Visuals.reserve(in_rDesc.VisualCount);
		}
		
		void Add(GOCVisual* in_pVisual)
		{
			in_pVisual->AddRef();
			Visuals.push_back(in_pVisual);

			Unk1 |= in_pVisual->Unk1;
		}

		void Remove(GOCVisual* in_pVisual)
		{
			auto idx = Visuals.find(in_pVisual);
			if (idx != -1)
				Visuals.remove(idx);
			
			if (in_pVisual)
				in_pVisual->Release();
		}
	};
}