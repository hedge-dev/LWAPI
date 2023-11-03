#pragma once

namespace app::StageInfo
{
	struct StageNode
	{
		csl::ut::FixedString<64> Title{};
		csl::ut::FixedString<16> Name{};
	};
	
	class WorldNode : public fnd::ReferencedObject
	{
		csl::ut::FixedString<64> m_Title{};
		csl::ut::MoveArray<StageNode> m_Stages{ GetAllocator() };

	public:
		WorldNode()
		{

		}
		
		void SetTitle(const char* in_pTitle)
		{
			m_Title = in_pTitle;
		}

		const char* GetTitle() const
		{
			return m_Title.c_str();
		}
		
		void AddNode(const StageNode& in_rNode)
		{
			m_Stages.push_back(in_rNode);
		}

		csl::ut::MoveArray<StageNode>& GetStages()
		{
			return m_Stages;
		}

		const csl::ut::MoveArray<StageNode>& GetStages() const
		{
			return m_Stages;
		}
	};
}