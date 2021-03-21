#pragma once

namespace app
{
	class ResPhysicsMesh
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00F62224));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResUnusedPhysicsMesh
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00F62234));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResGismoConfig
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00F938E8));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResScoreTable
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FB9A0C));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResSvCol
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FB772C));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResSample
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00F6A48C));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResSurfRideProject
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00F731D0));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResFxColFile
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FB6D68));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResVoxelContainer
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FB6FE8));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResCustomData
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00F69960));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResLuaData
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00F6FC2C));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResTerrainMap
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FB76F0));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResSM4ShaderContainer
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FB6FAC));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};
	
	namespace game
	{
		class ResNameExtra
		{
		private:
			inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00F6AD14));

		public:
			static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
		};

		class ResSplinePath2
		{
		private:
			inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00F6F958));

		public:
			static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
		};
	}
	
	namespace text
	{
		class ResTTFData
		{
		private:
			inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00F69E38));

		public:
			static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
		};

		class ResBFTTFData
		{
		private:
			inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00F69E48));

		public:
			static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
		};
	}

	namespace dev
	{
		class ResEventTb
		{
		private:
			inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00F64FD0));

		public:
			static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
		};

		class ResEventTag
		{
		private:
			inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00F64F98));

		public:
			static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
		};

		class ResEventEvs
		{
		private:
			inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00F64F60));

		public:
			static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
		};
	}

	namespace res
	{
		class ResShadowModel
		{
		private:
			inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FB6F0C));

		public:
			static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
		};
	}
}

namespace hh::ut
{
	class ResPacDepend
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCEAEC));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	namespace internal
	{
		class ResPacGeneral
		{
		private:
			inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCEAFC));

		public:
			static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
		};
	}
}

namespace hh::gfx::res
{
	class ResAnimCameraContainer
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE990));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResAnimLightContainer
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE948));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResAnimMaterial
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE900));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResAnimMorphTarget
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE8C0));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResAnimSkeleton
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE87C));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResAnimTexPat
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE83C));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResAnimTexSrt
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE7FC));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResAnimVis
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE7BC));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResFragmentShader
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE600));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResMaterial
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE780));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResModel
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE6B4));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResModelInstanceInfo
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE744));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResShader
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE610));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResSkeleton
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE700));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResTerrainModel
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE6C4));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResTexture
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE64C));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResVertexShader
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE5F0));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResMirageLight
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE550));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResMirageLightField
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE510));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResMiragePixelShaderCode
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE4CC));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResMiragePixelShaderParameter
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE484));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResMirageTerrainInstanceInfo
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE434));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResMirageVertexShaderCode
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE3E8));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};

	class ResMirageVertexShaderParameter
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCE39C));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};
}

namespace hh::eff::res
{
	class ResEffect
	{
	private:
		inline static hh::ut::ResourceTypeInfo* ms_pTypeInfo = reinterpret_cast<hh::ut::ResourceTypeInfo*>(ASLR(0x00FCDDC8));

	public:
		static const hh::ut::ResourceTypeInfo& staticTypeInfo() { return *ms_pTypeInfo; }
	};
}