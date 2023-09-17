#pragma once

namespace app::game
{
	class PathEvaluator
	{
	private:
		inline static FUNCTION_PTR(void, __thiscall, ms_fpGetPNT, ASLR(0x004D8E50), const PathEvaluator*, float, csl::math::Vector3*, csl::math::Vector3*, csl::math::Vector3*);
		inline static FUNCTION_PTR(float, __thiscall, ms_fpLength, ASLR(0x004D8E30), const PathEvaluator*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpAdvance, ASLR(0x004D8EA0), PathEvaluator*, float);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpReset, ASLR(0x004D8E20), PathEvaluator*);
		inline static FUNCTION_PTR(void, __thiscall, ms_fpGetClosestPositionAlongSpline, ASLR(0x004D8EE0), const PathEvaluator*, const csl::math::Vector3&, float, float, float*);

	public:
		fnd::Handle<PathComponent> Component{ nullptr };
		float Distance{};
		int Unk1{};

		PathEvaluator()
		{
			
		}

		PathEvaluator(PathComponent* pObj)
		{
			Component = pObj;
		}

		PathComponent* GetPathObject() const
		{
			return Component.Get();
		}

		void SetPathObject(PathComponent* in_pComponent)
		{
			Component = in_pComponent;
		}

		ResPathObject GetResPath()
		{
			return GetPathObject()->GetResPathObject();
		}

		void GetPNT(float in_distance, csl::math::Vector3* out_pPoint, csl::math::Vector3* out_pNormal, csl::math::Vector3* out_pTangent) const
		{
			ms_fpGetPNT(this, in_distance, out_pPoint, out_pNormal, out_pTangent);
		}

		csl::math::Vector3 GetWorldPosition(float in_distance) const
		{
			csl::math::Vector3 pos;
			GetPNT(in_distance, &pos, nullptr, nullptr);
			return pos;
		}

		csl::math::Vector3 GetNormal(float in_distance) const
		{
			csl::math::Vector3 normal;
			GetPNT(in_distance, nullptr, &normal, nullptr);
			return normal;
		}

		csl::math::Vector3 GetTangent(float in_distance) const
		{
			csl::math::Vector3 tangent;
			GetPNT(in_distance, nullptr, nullptr, &tangent);
			return tangent;
		}

		float GetLength() const
		{
			return ms_fpLength(this);
		}

		void Advance(float in_speed)
		{
			ms_fpAdvance(this, in_speed);
		}

		void Reset()
		{
			ms_fpReset(this);
		}

		void GetClosestPositionAlongSpline(const csl::math::Vector3& in_position, float in_unk1, float in_unk2, float* in_length)
		{
			ms_fpGetClosestPositionAlongSpline(this, in_position, in_unk1, in_unk2, in_length);
		}

		void SetDistance(float in_distance)
		{
			Distance = in_distance;
		}
	};
}