#pragma once
#include "../../lua/lauxlib.h"

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
		
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCtor, ASLR(0x004DECC0), LuaScript*, csl::fnd::IAllocator*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpDtor, ASLR(0x004DEBB0), LuaScript*);
		
		inline static FUNCTION_PTR(void, __thiscall, ms_fpLoad, ASLR(0x004DEBC0), LuaScript*, const char*, size_t);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpOpenNode, ASLR(0x004DED00), LuaScript*, const char*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpCloseNode, ASLR(0x004DEC20), LuaScript*);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetBool, ASLR(0x004DED60), LuaScript*, const char*, bool&);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetInt, ASLR(0x004DEE70), LuaScript*, const char*, int&);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetColor, ASLR(0x004DF470), LuaScript*, const char*, csl::ut::Color8&);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetFloat, ASLR(0x004DEDF0), LuaScript*, const char*, float&);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetFloatArray, ASLR(0x004DF070), LuaScript*, const char*, csl::ut::MoveArray<float>&);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetVector3, ASLR(0x004DF350), LuaScript*, const char*, csl::math::Vector3&);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetString, ASLR(0x004DEF00), LuaScript*, const char*, const char*&);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpGetStringArray, ASLR(0x004DF160), LuaScript*, const char*, csl::ut::MoveArray<const char*>&);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpForEach, ASLR(0x004DF260), LuaScript*, const char*, Iterator*, void*);

	public:
		LuaScript(csl::fnd::IAllocator* in_pAllocator)
		{
			ms_fpCtor(this, in_pAllocator);
		}

		~LuaScript()
		{
			if (m_pState)
			{
				lua_close(m_pState);
			}
		}
		
		void Load(const char* in_pBuf, size_t in_bufSize)
		{
			if (m_pState == nullptr || luaL_loadbuffer(m_pState, in_pBuf, in_bufSize, nullptr))
			{
				return;
			}

			lua_pcall(m_pState, 0, 0, 0);
			m_Top = lua_gettop(m_pState);
		}

		bool OpenNode(const char* in_pName)
		{
			return ms_fpOpenNode(this, in_pName);
		}
		
		void CloseNode()
		{
			ms_fpCloseNode(this);
		}
		
		void ForEach(const char* in_pNode, Iterator* in_pIter, void* in_pContext)
		{
			return ms_fpForEach(this, in_pNode, in_pIter, in_pContext);
		}

		bool GetStringArray(const char* in_pName, csl::ut::MoveArray<const char*>& out_rResult)
		{
			return ms_fpGetStringArray(this, in_pName, out_rResult);
		}

		bool GetString(const char* in_pName, const char*& out_rResult)
		{
			return ms_fpGetString(this, in_pName, out_rResult);
		}

		bool GetVector3(const char* in_pName, csl::math::Vector3& out_rResult)
		{
			return ms_fpGetVector3(this, in_pName, out_rResult);
		}

		bool GetColor(const char* in_pName, csl::ut::Color8& out_rResult)
		{
			return ms_fpGetColor(this, in_pName, out_rResult);
		}

		bool GetFloatArray(const char* in_pName, csl::ut::MoveArray<float>& out_rResult)
		{
			return ms_fpGetFloatArray(this, in_pName, out_rResult);
		}

		bool GetFloat(const char* in_pName, float& out_rResult)
		{
			return ms_fpGetFloat(this, in_pName, out_rResult);
		}

		bool GetInt(const char* in_pName, int& out_rResult)
		{
			return ms_fpGetInt(this, in_pName, out_rResult);
		}

		bool GetBool(const char* in_pName, bool& out_rResult)
		{
			return ms_fpGetBool(this, in_pName, out_rResult);
		}
	};
}