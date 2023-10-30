#pragma once

namespace Extra::fx
{
	class CFxPipelineExecutor
	{
	public:
		class CFxPipelineExecutorInternal
		{
		public:
			inline static FUNCTION_PTR(void, __cdecl, ms_fpRebuildTextureSurface, ASLR(0x00C50C40), hh::rsdx::RsdxSurface9* in_surface, Extra::fx::STextureSurfacePair& out_pair, bool a3);

			static void RebuildTextureSurface(hh::rsdx::RsdxSurface9* in_surface, Extra::fx::STextureSurfacePair& out_pair, bool a3)
			{
				ms_fpRebuildTextureSurface(in_surface, out_pair, a3);
			}
		};

		static void RebuildTextureSurface(hh::rsdx::RsdxSurface9* in_surface, Extra::fx::STextureSurfacePair& out_pair, bool a3)
		{
			CFxPipelineExecutorInternal::RebuildTextureSurface(in_surface, out_pair, a3);
		}
	};
}