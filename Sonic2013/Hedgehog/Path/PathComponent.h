#pragma once

namespace app::game
{
	class PathComponent : public fnd::GOComponent
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpResetResPathObject, ASLR(0x004D8C10), PathComponent*, ResPathObject);

		ResPathObject m_PathObject{};
	
	public:
		PathManager* pManager{};
	
	private:
		void* m_pInternalData{};
		size_t m_UID{};
		int m_CollisionFilterInfo{};

	public:
		PathComponent() : GOComponent()
		{
			
		}

		const char* GetFamilyID() const override
		{
			return "PathComponent";
		}

		void Cleanup();

		int GetCollisionFilterInfo() const
		{
			return m_CollisionFilterInfo;
		}

		void SetCollisionFilterInfo(int filterInfo)
		{
			m_CollisionFilterInfo = filterInfo;
		}

		void* GetInternalData() const
		{
			return m_pInternalData;
		}

		void SetInternalData(void* pData)
		{
			m_pInternalData = pData;
		}

		PathManager* GetManager() const
		{
			return pManager;
		}

		const char* GetName() const
		{
			return m_PathObject->pName;
		}

		game::ResPathObject GetResPathObject()
		{
			return m_PathObject;
		}

		game::ResPathObject GetResPathObject() const
		{
			return m_PathObject;
		}

		void ResetResPathObject(game::ResPathObject in_pathObject)
		{
			ms_fpResetResPathObject(this, in_pathObject);
		}
		
		size_t GetUID() const
		{
			return m_UID;
		}
	};
}