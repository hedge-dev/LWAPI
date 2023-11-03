#pragma once

namespace app::fnd
{
	class GOCVisualTransformed : public GOCVisual, public HFrameListener
	{
	public:
		void* Unk1;
		HFrame* pFrame;
		void* Unk2;
		math::CalculatedTransform Transform;
		bool Unk3;
		INSERT_PADDING(12);
		
		virtual void OnGOCVisualEvent(int, uint, void*) = 0;

		void SetFrame(HFrame* in_pFrame)
		{
			if (pFrame)
				pFrame->RemoveHFrameListener(this);

			pFrame = in_pFrame;
			if (in_pFrame)
				in_pFrame->AddHFrameListener(this);
		}

		void MarkUpdate()
		{
			pFrame->MarkUpdate();
			Unk3 = true;
		}

	public:
		void SetLocalTranslation(const csl::math::Vector3& in_rTranslation)
		{
			Transform.SetTranslation(in_rTranslation);
			MarkUpdate();
		}

		void SetLocalRotation(const csl::math::Quaternion& in_rRotation)
		{
			Transform.SetRotation(in_rRotation);
			MarkUpdate();
		}

		void SetLocalRotationXYZ(float in_roll, float in_pitch, float in_yaw)
		{
			Transform.SetRotationXYZ(in_roll, in_pitch, in_yaw);
			MarkUpdate();
		}

		void SetLocalScale(const csl::math::Vector3& in_rScale)
		{
			Transform.Scale = in_rScale;
			Transform.SetFlag(1);
			MarkUpdate();
		}
	};
}