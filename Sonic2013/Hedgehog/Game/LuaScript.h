#pragma once

typedef void lua_State;

namespace app::game
{
	class LuaScript
	{
		lua_State* m_pState;
		bool m_IsGCRunning;
		int m_Unk1;
		int m_Top;
		csl::fnd::IAllocator* m_pAllocator{};

	public:
		typedef void __cdecl Iterator(const char* pNode, LuaScript& script, void* pContext);
		
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x004DECC0), LuaScript* This, csl::fnd::IAllocator* pAllocator);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDtor, ASLR(0x004DEBB0), LuaScript* This);
		
		inline static FUNCTION_PTR(void, __thiscall, ms_fpLoad, ASLR(0x004DEBC0), LuaScript* This, const char* pBuf, size_t bufSize);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpOpenNode, ASLR(0x004DED00), LuaScript* This, const char* pName);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCloseNode, ASLR(0x004DEC20), LuaScript* This);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetBool, ASLR(0x004DED60), LuaScript* This, const char* pName, bool& result);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetInt, ASLR(0x004DEE70), LuaScript* This, const char* pName, int& result);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetColor, ASLR(0x004DF470), LuaScript* This, const char* pName, csl::ut::Color8& result);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetFloat, ASLR(0x004DEDF0), LuaScript* This, const char* pName, float& result);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetVector3, ASLR(0x004DF350), LuaScript* This, const char* pName, csl::math::Vector3& result);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetString, ASLR(0x004DEF00), LuaScript* This, const char* pName, const char*& result);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetStringArray, ASLR(0x004DF160), LuaScript* This, const char* pName, csl::ut::MoveArray<const char*>& result);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpForEach, ASLR(0x004DF260), LuaScript* This, const char* pNode, Iterator* pIter, void* pContext);

		LuaScript(csl::fnd::IAllocator* pAllocator)
		{
			ms_fpCtor(this, pAllocator);
		}

		~LuaScript()
		{
			ms_fpDtor(this);
		}
		
		void Load(const char* pBuf, size_t bufSize)
		{
			return ms_fpLoad(this, pBuf, bufSize);
		}

		bool OpenNode(const char* pName)
		{
			return ms_fpOpenNode(this, pName);
		}
		
		void CloseNode()
		{
			ms_fpCloseNode(this);
		}
		
		void ForEach(const char* pNode, Iterator* pIter, void* pContext)
		{
			return ms_fpForEach(this, pNode, pIter, pContext);
		}

		bool GetStringArray(const char* pName, csl::ut::MoveArray<const char*>& result)
		{
			return ms_fpGetStringArray(this, pName, result);
		}

		bool GetString(const char* pName, const char*& result)
		{
			return ms_fpGetString(this, pName, result);
		}

		bool GetVector3(const char* pName, csl::math::Vector3& result)
		{
			return ms_fpGetVector3(this, pName, result);
		}

		bool GetColor(const char* pName, csl::ut::Color8& result)
		{
			return ms_fpGetColor(this, pName, result);
		}

		bool GetFloat(const char* pName, float& result)
		{
			return ms_fpGetFloat(this, pName, result);
		}

		bool GetInt(const char* pName, int& result)
		{
			return ms_fpGetInt(this, pName, result);
		}

		bool GetBool(const char* pName, bool& result)
		{
			return ms_fpGetBool(this, pName, result);
		}
	};
}