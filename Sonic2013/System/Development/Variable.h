#pragma once

namespace gindows
{
	class TreeNode;
	struct DrawItemEventArgs;
};

namespace app::dev
{
	// S13Variable : gindows::TreeNode
	class S13Variable : public gindows::Object
	{
	public:
		struct InputInput;
		struct InputOutput;
		
	public:
		const void* m_pTreeNodeVftable;
		bool m_Unk1;
		std::dummy::string m_Name;
		INSERT_PADDING(12){};
		bool m_Unk2;
		
		S13Variable()
		{
			
		}
		
		/*virtual size_t GetChildCount_TN() const = 0;
		virtual gindows::TreeNode* GetChild_TN() = 0;
		virtual gindows::TreeNode* GetSibling_TN() = 0;*/
		virtual void Release() = 0;
		virtual void Increment(float value) = 0;
		virtual void Decrement(float value) = 0;
		virtual void Execute() = 0;
		virtual void DrawType(gindows::DrawItemEventArgs& args) = 0;
		virtual void DrawName(gindows::DrawItemEventArgs& args) = 0;
		virtual void DrawVariable(gindows::DrawItemEventArgs& args) = 0;
		virtual void DrawVariableEditing(gindows::DrawItemEventArgs& args) = 0;
		virtual void OnKeyDown(gindows::KeyEventArgs& args) = 0;
		virtual void ProcessInput(InputInput& input, InputOutput& output) = 0;
		virtual void ReadValue() = 0;
		virtual void WriteValue() = 0;
		virtual void StoreValue() = 0;
		virtual void RestoreValue() = 0;
	};
}