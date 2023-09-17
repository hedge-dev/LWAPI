#pragma once

namespace app::fnd
{
	class GOCVisualTransformed : public GOCVisual, HFrameListener
	{
	public:
		void* m_Unk1;
		HFrame* m_pFrame;
		void* m_Unk2;
		math::CalculatedTransform m_Transform;
		bool m_Unk3;
		INSERT_PADDING(12);
		
		virtual void OnGOCVisualEvent(int, uint, void*) = 0;

		void SetFrame(HFrame* pFrame)
		{
			if (m_pFrame)
				m_pFrame->RemoveHFrameListener(this);

			m_pFrame = pFrame;
			if (pFrame)
				pFrame->AddHFrameListener(this);
		}

		void MarkUpdate()
		{
			m_pFrame->MarkUpdate();
			m_Unk3 = true;
		}

	public:
		void SetLocalTranslation(const csl::math::Vector3& translation)
		{
			m_Transform.SetTranslation(translation);
			MarkUpdate();
		}

		void SetLocalRotation(const csl::math::Quaternion& in_rRotation)
		{
			m_Transform.SetRotation(in_rRotation);
			MarkUpdate();
		}

		void SetLocalRotationXYZ(float in_roll, float in_pitch, float in_yaw)
		{
			m_Transform.SetRotationXYZ(in_roll, in_pitch, in_yaw);
			MarkUpdate();
		}

		void SetLocalScale(const csl::math::Vector3& scale)
		{
			m_Transform.m_Scale = scale;
			m_Transform.SetFlag(1);
			MarkUpdate();
		}
	};
}