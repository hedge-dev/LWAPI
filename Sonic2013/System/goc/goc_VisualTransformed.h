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
		INSERT_PADDING(16);
		
		virtual void OnGOCVisualEvent(int, uint, void*) = 0;

		void SetFrame(HFrame* pFrame)
		{
			if (m_pFrame)
				m_pFrame->RemoveHFrameListener(this);

			m_pFrame = pFrame;
			if (pFrame)
				pFrame->AddHFrameListener(this);
		}
	};
}