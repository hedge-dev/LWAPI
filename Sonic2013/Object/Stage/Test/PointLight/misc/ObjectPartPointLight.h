#pragma once

namespace app
{
	class ObjectPartPointLight : public GameObject3D
	{
	public:
		class CInfo
		{
		public:
			csl::math::Vector3 Position{};
			float Unk1{ 1.0f };
			float A{ 1.0f };
			float R{ 1.0f };
			float G{ 1.0f };
			float B{ 1.0f };
			float LifeTime{ 1.0f };
			fnd::GOCTransform* pParentTransform{};
			bool Unk8{};
		};

		const CInfo* pCreateInfo{};
		float LifeTime{};
		ushort LocalLightNo{};
		csl::ut::Bitset<char> Flags{};

		ObjectPartPointLight(const CInfo& in_rCreateInfo) : GameObject3D(), pCreateInfo(&in_rCreateInfo)
		{
			SetObjectCategory(9);
		}

		void AddCallback(GameDocument* in_pDocument) override
		{
			fnd::GOComponent::BeginSetup(*this);

			auto* pTransform = GetComponent<fnd::GOCTransform>();
			pTransform->SetLocalTranslation(pCreateInfo->Position);

			auto lightPosition = pCreateInfo->Position;
			if (pCreateInfo->pParentTransform)
			{
				pTransform->SetParent(pCreateInfo->pParentTransform);
				lightPosition = pCreateInfo->pParentTransform->Frame.Unk3.Mtx * csl::math::Vector4(lightPosition, 1.0f);
			}

			LifeTime = pCreateInfo->LifeTime;
			LocalLightNo = csl::fnd::Singleton<gfx::RenderManager>::GetInstance()->AddLocalLight(lightPosition, { pCreateInfo->R, pCreateInfo->G, pCreateInfo->B, pCreateInfo->A }, 0.0f, 0.0f, 0.0f, pCreateInfo->Unk1);

			if (!pCreateInfo->Unk8 && !pCreateInfo->pParentTransform)
				Flags.set(0, false);
			else
				Flags.set(0, true);

			pCreateInfo = nullptr;

			fnd::GOComponent::EndSetup(*this);
		}

		void RemoveCallback(GameDocument* in_rClass) override
		{
			csl::fnd::Singleton<gfx::RenderManager>::GetInstance()->RemoveLocalLight(LocalLightNo);
		}

		void Update(const fnd::SUpdateInfo& in_rUpdateInfo) override
		{
			if (LifeTime >= 0.0f)
			{
				LifeTime -= in_rUpdateInfo.deltaTime;
				if (LifeTime <= 0.0f)
				{
					Kill();
					return;
				}
			}

			if (!Flags.test(0))
				return;
		
			auto* pTransform = GetComponent<fnd::GOCTransform>();
			csl::fnd::Singleton<gfx::RenderManager>::GetInstance()->SetLocalLightPosition(LocalLightNo, pTransform->Frame.Unk3.GetTranslation());
		}

		void ChangeColor(csl::ut::ColorF in_color)
		{
			csl::fnd::Singleton<gfx::RenderManager>::GetInstance()->SetLocalLightColor(LocalLightNo, { in_color.R, in_color.G, in_color.B, in_color.A });
		}

		void ChangeLifeTime(float in_lifeTime)
		{
			LifeTime = in_lifeTime;
		}

		void ChangeRadius(float in_radius)
		{
			csl::fnd::Singleton<gfx::RenderManager>::GetInstance()->SetLocalLightRadius(LocalLightNo, 0.0f, 0.0f, 0.0f, in_radius);
		}

		static ObjectPartPointLight* Create(GameDocument& in_rDocument, const ObjectPartPointLight::CInfo& in_rCreateInfo)
		{
			auto* pObject = new ObjectPartPointLight(in_rCreateInfo);
			if (!pObject)
				return { nullptr };

			in_rDocument.AddGameObject(pObject);
			return pObject;
		}
	};
}