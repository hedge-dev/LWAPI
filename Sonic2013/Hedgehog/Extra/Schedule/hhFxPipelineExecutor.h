#pragma once

namespace Extra::fx
{
	class CFxPipelineExecutor
	{
	public:
		class CFxPipelineExecutorInternal
		{
		public:
			inline static FUNCTION_PTR(void, __cdecl, ms_fpRebuildTextureSurface, ASLR(0x00C50C40), hh::rsdx::RsdxSurface9*, Extra::fx::STextureSurfacePair&, bool);

			static void RebuildTextureSurface(hh::rsdx::RsdxSurface9* in_pSurface, Extra::fx::STextureSurfacePair& out_rPair, bool in_a3)
			{
				ms_fpRebuildTextureSurface(in_pSurface, out_rPair, in_a3);
			}
		};

		static void RebuildTextureSurface(hh::rsdx::RsdxSurface9* in_pSurface, Extra::fx::STextureSurfacePair& out_rPair, bool in_a3)
		{
			CFxPipelineExecutorInternal::RebuildTextureSurface(in_pSurface, out_rPair, in_a3);
		}
	};
}