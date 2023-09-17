#pragma once

namespace app::Render
{
	struct CameraParam
	{
		csl::math::Matrix34 m_ViewMtx{}; // 0
		csl::math::Vector2 m_ViewportPosition{}; // 64
		csl::math::Vector2 m_ViewportSize{ 1280, 720 }; // 72
		csl::math::Matrix34 m_Perspective{}; // 80
		csl::math::Vector3 m_Unk3{}; // ???
		csl::math::Vector3 m_Unk4{}; // ???

		inline static FUNCTION_PTR(bool, __thiscall, ms_fpProjectScreen, ASLR(0x008FF3D0), const CameraParam*, const csl::math::Vector3&, csl::math::Vector3&, float*);

		bool TransformNDC(csl::math::Vector3& out_rNdc, const csl::math::Vector3& in_rPoint) const
		{
			csl::math::Vector3 mtxPoint = { m_ViewMtx * csl::math::Vector4(in_rPoint, 1.0f) };
			if (mtxPoint.z() >= 0.0f)
				return false;

			csl::math::Vector3 ndc{ m_Perspective.col(0).x() * mtxPoint.x(), m_Perspective.col(1).y() * mtxPoint.y(), m_Perspective.col(2).z() * mtxPoint.z() + m_Perspective.col(2).w() };
			out_rNdc = { ndc * (1.0f / mtxPoint.z()) };
			return true;
		}

		bool ProjectScreen(const csl::math::Vector3& in_point, csl::math::Vector3& out_screenPoint, float* out_pDepth) const
		{
			using namespace csl::math;

			csl::math::Vector3 clip{ m_Perspective * Vector3(m_ViewMtx * Vector4(in_point, 1.0f)) };
			Eigen::Vector4f clipPos{ *reinterpret_cast<Eigen::Vector4f*>(&clip) };
			if (clipPos[3] < FLT_EPSILON)
				return false;

			Vector3 ndcPos{ Vector3{clipPos[0], clipPos[1], clipPos[2]} / clipPos[3] };

			if (out_pDepth)
				*out_pDepth = clipPos[3];

			out_screenPoint[0] = (0.5f + ndcPos[0] / 2.0f) * m_ViewportSize.x();
			out_screenPoint[1] = (0.5f - ndcPos[1] / 2.0f) * m_ViewportSize.y();

			return true;
		}

		bool ProjectScreen(const csl::math::Vector3& in_point, csl::math::Vector3& out_screenPoint) const
		{
			return ProjectScreen(in_point, out_screenPoint, nullptr);
		}

		// Transform 0-1 range screen co-ordinates to world space
		csl::math::Vector3 ProjectWorld(const csl::math::Vector3& in_point) const
		{
			using namespace csl::math;
			using namespace Eigen;
			
			Vector2 ndc = reinterpret_cast<const csl::math::Vector2&>(in_point);
			ndc[0] = (ndc[0] - 0.5f) * 2.0f;
			ndc[1] = (ndc[1] - 0.5f) * -2.0f;

			Vector4f transformed = m_Perspective.inverse() * Vector4f { ndc[0], ndc[1], in_point[2], 1 };
			transformed = m_ViewMtx.inverse() * transformed;
			transformed /= transformed[3];

			return Vector3{ transformed[0], transformed[1], transformed[2] };
		}

		// Transform 0-1 range screen co-ordinates to world space
		csl::math::Vector3 ProjectWorld(const csl::math::Vector2& in_point, float in_depth = 0) const
		{
			return ProjectWorld(csl::math::Vector3{ in_point[0], in_point[1], std::clamp(in_depth, 0.0f, 1.0f) });
		}
		
		csl::math::Matrix34 GetInvViewMatrix() const
		{
			csl::math::Matrix34 mtx{};
			csl::math::Matrix34Inverse(m_ViewMtx, &mtx);
			
			return mtx;
		}
	};
}