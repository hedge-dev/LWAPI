#pragma once

namespace app::game
{
	struct ResPathObjectData
	{
		const char* pName{};
		char Unk1{};
		float Length{};
		INSERT_PADDING(28);
		float Min[3];
		float Max[3];
		INSERT_PADDING(8);
	};

	class ResPathObject : public app::fnd::ResCommon<ResPathObjectData>
	{
	public:
		csl::math::Aabb GetAabb() const
		{
			return csl::math::Aabb(csl::math::Vector3(m_pRes->Min[0], m_pRes->Min[1], m_pRes->Min[2]), csl::math::Vector3(m_pRes->Max[0], m_pRes->Max[1], m_pRes->Max[2]));
		}
	};
}