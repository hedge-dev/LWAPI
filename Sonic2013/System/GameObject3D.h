#pragma once

namespace app
{
	class alignas(16) GameObject3D : GameObject
	{
		fnd::GOCTransform transform;
		INSERT_PADDING(100); // WHAT AND WHY

	protected:
		fnd::GOCTransform* pTransform{&transform};

	public:
		GameObject3D() : GameObject()
		{
			transform = fnd::GOCTransform();
			AddComponent(pTransform);
		}

		bool ProcessMessage(fnd::Message& msg) override
		{
			if (PreProcessMessage(msg))
				return true;


			
			return GameObject::ProcessMessage(msg);
		}
	};
}
