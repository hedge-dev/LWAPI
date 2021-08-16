#pragma once

namespace app
{
	class GameMode : public fnd::ReferencedObject
	{
	protected:
		CGame* m_pGame{};
		void* m_Unk1{};
		const char* m_pName{};
		GameDocument* m_pDocument{};
		void* m_Unk2{};
	
	public:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpOnEnter, ASLR(0x004AC800), GameMode*, CGame&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpOnLeave, ASLR(0x004AC820), GameMode*, CGame&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDefaultGameLoop, ASLR(0x004AC9B0), GameMode*, const fnd::SUpdateInfo&);
		
		virtual void OnEnter(CGame& game)
		{
			ms_fpOnEnter(this, game);
		}

		virtual void OnLeave(CGame& game)
		{
			ms_fpOnLeave(this, game);
		}

		virtual void Update(CGame& game, const fnd::SUpdateInfo& updateInfo)
		{
			ms_fpDefaultGameLoop(this, updateInfo);
		}

		virtual bool ProcessMessage(CGame& game, fnd::Message& msg)
		{
			return false;
		}

		virtual bool PreProcessMessage(CGame& game, fnd::Message& msg)
		{
			return false;
		}

		GameDocument* GetGameDocument() const
		{
			return m_pDocument;
		}
		
		const char* GetName() const
		{
			return m_pName;
		}
		
		CGame* GetGame() const
		{
			return m_pGame;
		}

		void* operator new (size_t size)
		{
			return ReferencedObject::operator new(size, game::GlobalAllocator::GetAllocator(2));
		}
	};
}