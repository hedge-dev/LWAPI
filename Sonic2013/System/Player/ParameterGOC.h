#pragma once

namespace app::Player
{
	class CPlayer;

	struct Param
	{
		typedef uint Index;

		struct Type
		{
			typedef uint EType__;
		};
	};

	struct ParameterNode
	{
		int Unk1[141]{};
		int Unk2{};
		int Unk3{};
	};

	class CParameterGOC : public CGOComponent
	{
	private:
		inline static FUNCTION_PTR(float, __thiscall, ms_fpGet, ASLR(0x008665C0), CParameterGOC*, Param::Index);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpChangeParam, ASLR(0x008664A0), CParameterGOC*, Param::Type::EType__);

		inline static const char* ms_pStaticId = (char*)ASLR(0x00DF82C8);

	public:
		int Unk1{};
		bool Unk2{};
		CPlayer* pPlayer{};
		ParameterNode Nodes[6]{};
		csl::ut::LinkList<ParameterNode> ParameterList{};

		static const char* staticID()
		{
			return ms_pStaticId;
		}

		CParameterGOC(CPlayer* in_pPlayer)
		{
			pPlayer = in_pPlayer;
		}

		float Get(Param::Index in_index)
		{
			return ms_fpGet(this, in_index);
		}

		void ChangeParam(Param::Type::EType__ in_type)
		{
			ms_fpChangeParam(this, in_type);
		}

		void ResetParam(Param::Type::EType__ in_type)
		{

		}
	};
}