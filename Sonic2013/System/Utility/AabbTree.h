#pragma once

namespace app::ut
{
	class AabbTreeHandle;

	struct AabbTree : public fnd::ReferencedObject
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpBuild, ASLR(0x00924800), AabbTree*);

	public:
		class InternalNode
		{
			INSERT_PADDING(48);
		};

		csl::ut::Bitset<uint8> Unk1{};
		int Unk2{};
		int Unk3{};
		csl::ut::MoveArray<AabbTreeHandle*> Handles{ GetAllocator() };
		csl::ut::MoveArray<csl::math::Aabb> Aabbs{ GetAllocator() };
		csl::ut::MoveArray<csl::math::Vector3> Positions{ GetAllocator() };
		csl::ut::MoveArray<InternalNode> Nodes{ GetAllocator() };
		csl::ut::MoveArray<ushort> Unk4{ GetAllocator() };

		AabbTree(size_t in_blockCount, size_t in_blockSize)
		{
			Unk3 = 1;
			Nodes.resize(1 << (in_blockSize + 1));
			
			Build();
		}

		void Build()
		{
			ms_fpBuild(this);
		}

		void Verify()
		{
			if (Unk1.test(0))
				Build();
		}

		static AabbTree* Create(csl::fnd::IAllocator* in_pAllocator, size_t in_blockCount, size_t in_blockSize)
		{
			auto* pTree = new(in_pAllocator) AabbTree(in_blockCount, in_blockSize);
			if (!pTree)
				return { nullptr };
		
			return pTree;
		}
	};
}