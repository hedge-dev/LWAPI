#pragma once

namespace app::fnd
{
	class GOCVisualTransformed : public GOCVisual, HFrameListener
	{
	protected:
		void* m_Unk1;
		HFrame* m_pFrame;
		void* m_Unk2;
		csl::math::CalculatedTransform m_Transform;
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
		void SetLocalScale(const csl::math::Vector3& scale)
		{
			m_Transform.m_Scale = scale;
			m_Transform.SetFlag(1);
			MarkUpdate();
		}
	};
}