#pragma once

namespace app::Render
{
	struct CameraParam
	{
	private:
		inline static FUNCTION_PTR(bool, __thiscall, ms_fpProjectScreen, ASLR(0x008FF3D0), const CameraParam*, const csl::math::Vector3&, csl::math::Vector3&, float*);

	public:
		csl::math::Matrix34 ViewMtx{}; // 0
		csl::math::Vector2 ViewportPosition{}; // 64
		csl::math::Vector2 ViewportSize{ 1280, 720 }; // 72
		csl::math::Matrix34 Perspective{}; // 80
		csl::math::Vector3 Unk3{}; // ???
		csl::math::Vector3 Unk4{}; // ???

		bool TransformNDC(csl::math::Vector3& out_rNdc, const csl::math::Vector3& in_rPoint) const
		{
			csl::math::Vector3 mtxPoint = { ViewMtx * csl::math::Vector4(in_rPoint, 1.0f) };
			if (mtxPoint.z() >= 0.0f)
				return false;

			csl::math::Vector3 ndc{ Perspective.col(0).x() * mtxPoint.x(), Perspective.col(1).y() * mtxPoint.y(), Perspective.col(2).z() * mtxPoint.z() + Perspective.col(2).w() };
			out_rNdc = { ndc * (1.0f / mtxPoint.z()) };
			return true;
		}

		bool ProjectScreen(const csl::math::Vector3& in_rPoint, csl::math::Vector3& out_rScreenPoint, float* out_pDepth) const
		{
			using namespace csl::math;

			csl::math::Vector3 clip{ Perspective * Vector3(ViewMtx * Vector4(in_rPoint, 1.0f)) };
			Eigen::Vector4f clipPos{ *reinterpret_cast<Eigen::Vector4f*>(&clip) };
			if (clipPos[3] < FLT_EPSILON)
				return false;

			Vector3 ndcPos{ Vector3{clipPos[0], clipPos[1], clipPos[2]} / clipPos[3] };

			if (out_pDepth)
				*out_pDepth = clipPos[3];

			out_rScreenPoint[0] = (0.5f + ndcPos[0] / 2.0f) * ViewportSize.x();
			out_rScreenPoint[1] = (0.5f - ndcPos[1] / 2.0f) * ViewportSize.y();

			return true;
		}

		bool ProjectScreen(const csl::math::Vector3& in_rPoint, csl::math::Vector3& out_rScreenPoint) const
		{
			return ProjectScreen(in_rPoint, out_rScreenPoint, nullptr);
		}

		// Transform 0-1 range screen co-ordinates to world space
		csl::math::Vector3 ProjectWorld(const csl::math::Vector3& in_rPoint) const
		{
			using namespace csl::math;
			using namespace Eigen;
			
			Vector2 ndc = reinterpret_cast<const csl::math::Vector2&>(in_rPoint);
			ndc[0] = (ndc[0] - 0.5f) * 2.0f;
			ndc[1] = (ndc[1] - 0.5f) * -2.0f;

			Vector4f transformed = Perspective.inverse() * Vector4f { ndc[0], ndc[1], in_rPoint[2], 1 };
			transformed = ViewMtx.inverse() * transformed;
			transformed /= transformed[3];

			return Vector3{ transformed[0], transformed[1], transformed[2] };
		}

		// Transform 0-1 range screen co-ordinates to world space
		csl::math::Vector3 ProjectWorld(const csl::math::Vector2& in_rPoint, float in_depth = 0) const
		{
			return ProjectWorld(csl::math::Vector3{ in_rPoint[0], in_rPoint[1], std::clamp(in_depth, 0.0f, 1.0f) });
		}
		
		csl::math::Matrix34 GetInvViewMatrix() const
		{
			csl::math::Matrix34 mtx{};
			csl::math::Matrix34Inverse(ViewMtx, &mtx);
			
			return mtx;
		}
	};
}