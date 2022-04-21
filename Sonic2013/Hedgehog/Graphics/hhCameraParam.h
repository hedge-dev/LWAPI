#pragma once

namespace app::Render
{
	struct CameraParam
	{
		csl::math::Matrix34 m_ViewMtx{}; // 0
		float m_Unk1{}; // 64
		float m_Unk2{}; // 68
		float m_Width{ 1280 }; // 72
		float m_Height{ 720 }; // 76
		csl::math::Matrix34 m_Perspective{}; // 80
		csl::math::Vector3 m_Unk3{}; // ???
		csl::math::Vector3 m_Unk4{}; // ???

		inline static FUNCTION_PTR(bool, __thiscall, ms_fpProjectScreen, ASLR(0x008FF3D0), const CameraParam*, const csl::math::Vector3&, csl::math::Vector3&, float*);
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpTransformNDC, ASLR(0x008FF660), const CameraParam*, csl::math::Vector3&, const csl::math::Vector3&);

		bool TransformNDC(csl::math::Vector3& out_ndc, const csl::math::Vector3& in_point) const
		{
			using namespace csl::math;

			Eigen::Vector4f clipPos{ m_Perspective * (m_ViewMtx * Vector4(in_point, 1)) };
			if (clipPos[3] < FLT_EPSILON)
				return false;

			out_ndc = { Vector3{clipPos[0], clipPos[1], clipPos[2]} / clipPos[3] };
			return true;
		}

		bool ProjectScreen(const csl::math::Vector3& in_point, csl::math::Vector3& out_screenPoint, float* out_pDepth) const
		{
			using namespace csl::math;

			Eigen::Vector4f clipPos{ m_Perspective * (m_ViewMtx * Vector4(in_point, 1)) };
			if (clipPos[3] < FLT_EPSILON)
				return false;

			Vector3 ndcPos{ Vector3{clipPos[0], clipPos[1], clipPos[2]} / clipPos[3] };

			if (out_pDepth)
				*out_pDepth = clipPos[3];

			out_screenPoint[0] = (0.5f + ndcPos[0] / 2.0f) * m_Width;
			out_screenPoint[1] = (0.5f - ndcPos[1] / 2.0f) * m_Height;

			return true;
		}

		bool ProjectScreen(const csl::math::Vector3& in_point, csl::math::Vector3& out_screenPoint) const
		{
			return ProjectScreen(in_point, out_screenPoint, nullptr);
		}
	};
}