#pragma once

namespace app::StageInfo
{
	struct StageNode
	{
		csl::ut::FixedString<64> m_Title{};
		csl::ut::FixedString<16> m_Name{};
	};
	
	class WorldNode : public fnd::ReferencedObject
	{
		csl::ut::FixedString<64> m_Title{};
		csl::ut::MoveArray<StageNode> m_Stages{ GetAllocator() };

	public:
		WorldNode()
		{

		}
		
		void SetTitle(const char* pTitle)
		{
			m_Title = pTitle;
		}

		const char* GetTitle() const
		{
			return m_Title.c_str();
		}
		
		void AddNode(const StageNode& node)
		{
			m_Stages.push_back(node);
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