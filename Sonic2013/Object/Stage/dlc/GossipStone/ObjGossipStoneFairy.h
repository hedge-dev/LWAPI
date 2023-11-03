#pragma once

namespace app
{
	class ObjGossipStoneFairy : public GameObject3D
	{
	public:
		class CInfo
		{
		public:
			float Unknown1{};
			csl::math::Matrix34 TransformMtx{};
		};

	private:
		inline static const char* ms_pAnimationName = "IDLE";
		inline static size_t ms_AnimationCount = 1;

	public:
		float Unknown1{};
		csl::math::Matrix34 TransformMtx{};
		float ElapsedTime{};

	public:
		ObjGossipStoneFairy(const CInfo& in_rCreateInfo) : GameObject3D(), Unknown1(in_rCreateInfo.Unknown1), TransformMtx(in_rCreateInfo.TransformMtx)
		{
			
		}

	protected:
		void AddCallback(GameDocument* in_pDocument) override
		{
			fnd::GOComponent::Create<fnd::GOCVisualModel>(*this);
			fnd::GOComponent::Create<game::GOCAnimationSimple>(*this);

			fnd::GOComponent::BeginSetup(*this);

			auto* pInfo = ObjUtil::GetObjectInfo<ObjGossipStoneInfo>(in_pDocument);

			if (auto* pVisualGoc = GetComponent<fnd::GOCVisualModel>())
			{
				fnd::GOCVisualModel::Description description{};
				description.Model = pInfo->FairyModel;
				description.Skeleton = pInfo->FairySkeleton;

				pVisualGoc->Setup(description);

				if (auto* pAnimationGoc = GetComponent<game::GOCAnimationSimple>())
				{
					pAnimationGoc->Setup({ ms_AnimationCount });
					pAnimationGoc->Add(ms_pAnimationName, pInfo->FairyAnimation, game::PlayPolicy::Loop);

					pVisualGoc->AttachAnimation(pAnimationGoc);

					pAnimationGoc->SetAnimation(ms_pAnimationName);
				}
			}

			fnd::GOComponent::EndSetup(*this);
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			ElapsedTime += in_rUpdateInfo.deltaTime;

			int timeThird = (int)(ElapsedTime / 3.0f);
			if (timeThird >= 3)
			{
				Kill();
				return;
			}

			float mask = SonicUSA::System::RadianMaskU(ElapsedTime * (MATHF_PI * 2.0f / 3.0f));

			float scalar1 = 10.0f;
			float scalar2 = sinf((fmodf(ElapsedTime, 1.6f) / 1.6f) * MATHF_PI * 2.0f) * 5.0f;
			float scalar3{};

			if (timeThird)
			{
				if (timeThird == 2)
				{
					scalar1 *= (1.0f - (fmodf(ElapsedTime, 3.0f) / 3.0f));
					scalar2 *= (1.0f - (fmodf(ElapsedTime, 3.0f) / 3.0f));
					scalar3 = (1.0f - (fmodf(ElapsedTime, 3.0f) / 3.0f)) * 7.0f + 10.0f;
				}
				else
				{
					scalar3 = 7.0f + 10.0f;
				}
			}
			else
			{
				scalar2 *= (fmodf(ElapsedTime, 3.0f) / 3.0f);
				scalar3 = (fmodf(ElapsedTime, 3.0f) / 3.0f) * 7.0f + 10.0f;
			}

			csl::math::Vector3 frontVec { TransformMtx * math::Vector3RotateY(mask, { csl::math::Vector3::UnitZ() }) };
			csl::math::Vector3 leftVec { TransformMtx * math::Vector3RotateY(mask, { csl::math::Vector3::UnitX() }) };
			
			csl::math::Matrix34 updatedMtx{};
			updatedMtx.SetColumn(0, { -frontVec });
			updatedMtx.SetColumn(1, frontVec.cross(leftVec));
			updatedMtx.SetColumn(2, { leftVec });
			updatedMtx.SetColumn(3, { 0.0f, 0.0f, 0.0f });

			csl::math::Vector3 translation{ TransformMtx.GetTransVector() + csl::math::Vector3(frontVec * scalar1) + csl::math::Vector3(frontVec.cross(leftVec) * (scalar2 + scalar3)) };
			csl::math::Quaternion rotation{ updatedMtx };

			GetComponent<fnd::GOCTransform>()->SetLocalTranslationAndRotation(translation, rotation);

			float modelScale = csl::math::Clamp(sinf(csl::math::Clamp(ElapsedTime / 0.2f, 0.0f, 1.0f) * MATHF_PI / 2.0f), 0.01f, 1.0f) * 2.0f;
			GetComponent<fnd::GOCVisualModel>()->SetLocalScale({ modelScale, modelScale, modelScale });
		}

	public:
		inline static ObjGossipStoneFairy* Create(const CInfo& in_rInfo)
		{
			return new ObjGossipStoneFairy(in_rInfo);
		}
	};
}