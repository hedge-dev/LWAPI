#pragma once

namespace app::game
{
	class GOCMotor;
	
	namespace motor_util
	{
		inline float GetGlobalTime(const GOCMotor& in_pMotor);
	}

	class GOCMotor : public fnd::GOComponent
	{
	public:
		typedef math::Transform UpdateOutput;
		typedef uint Status;
		typedef uint TimeType;
		
		math::Transform Transform{};
		fnd::GOCTransform* pTransform{};
		char Flags{};
		TimeType Type{ 1 };
		float Unk4{};
		float Time{};
		Status MotorStatus{ static_cast<uint>(-1) };

		const char* GetFamilyID() const override
		{
			return "GOCMotor";
		}

		void Update(fnd::UpdatingPhase phase, const fnd::SUpdateInfo& updateInfo) override
		{
			if (!phase)
			{
				UpdateStatus(updateInfo.deltaTime);
				if (IsActuate())
				{
					AdvanceTime(updateInfo.deltaTime);
					
					math::Transform transform{};
					Actuate(Time, &transform);
					SetTransform(transform);
				}
			}
		}

		void OnGOCEvent(int event, GameObject& object, void* data) override
		{
			if (event >= 4)
			{
				switch (event)
				{
				case 4:
				{
					if ((Flags & 8) != false)
						DrawDebugDraw();
					
					break;
				}
				case 6:
				{
					RegisterTransform(object);
					ResetTransformForDebug();
					break;
				}
				case 7:
				{
					ResetTransformForDebug();
					break;
				}
				}
			}
			else if (event)
			{
				if (event == 1)
					m_Flags.set(0, true);
			}
			else
			{
				RegisterTransform(object);
			}
		}

		virtual void Actuate(float in_time, UpdateOutput* out_pOutput) = 0;
		
		virtual void DrawDebugDraw()
		{
			
		}
		
		void SetStatus(Status in_status)
		{
			MotorStatus = in_status;
		}

		void UpdateStatus(float in_delta)
		{
			if (MotorStatus != 2)
				return;

			float globalTime = motor_util::GetGlobalTime(*this);
			float remainingTime = fmodf(globalTime - Time, Unk4);
			if (remainingTime < 0.0f)
				remainingTime += Unk4;
		
			if (remainingTime - in_delta < 0.0f && remainingTime >= 0.0f)
				SetStatus(0);
		}

		bool IsActuate()
		{
			return MotorStatus == 0;
		}
		
		void AdvanceTime(float in_delta)
		{
			if (Type)
			{
				if (Type == 1)
					Time += in_delta;
			}
			else
			{
				Time = motor_util::GetGlobalTime(*this);
			}
		}
		
		void InitTransform()
		{
			math::Transform transform{};
			Actuate(Time, &transform);
			SetTransform(transform);
			SetStatus(0);
		}

		void SetTransform(const UpdateOutput& in_rOutput)
		{
			if ((Flags & 1) != false)
				pTransform->SetLocalTranslation(in_rOutput.m_Position);
			
			if ((Flags & 2) != false)
				pTransform->SetLocalRotation(in_rOutput.m_Rotation);
		}

		void RegisterTransform(GameObject& in_rObject)
		{
			pTransform = in_rObject.GetComponent<fnd::GOCTransform>();
			Transform = pTransform->m_Transform;
		}

		void ResetTransformForDebug()
		{
			if ((Flags & 4) != false)
			{
				Time = 0.0f;
				
				math::Transform transform{};
				Actuate(Time, &transform);
				SetTransform(transform);
			}
		}

		void RequestEnable(bool in_enable)
		{
			if (MotorStatus)
			{
				if (MotorStatus == 1)
					SetStatus(!in_enable);
			}
			else if (in_enable)
			{
				if (MotorStatus)
					SetStatus(2);
			}
			else
			{
				SetStatus(1);
			}
		}

		void SetTimeParameter(TimeType in_type, float in_time)
		{
			Type = in_type;
			Unk4 = in_time;
			if (in_type)
			{
				if (in_type == 1)
					Time = 0.0f;
			}
			else
			{
				Time = motor_util::GetGlobalTime(*this);
			}
		}
	};

	namespace motor_util
	{
		inline float GetGlobalTime(const GOCMotor& in_pMotor)
		{
			return in_pMotor.GetGameObject()->GetDocument()->m_GlobalTime;
		}
	}
}