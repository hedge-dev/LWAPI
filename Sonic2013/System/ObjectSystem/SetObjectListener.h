#pragma once
#include <Hedgehog/Base/System/ReferencedObject.h>
#include <System/ObjectSystem/SetObjectListener.h>
#include <System/GameObject.h>

#include <cslib/math.h>

namespace app
{
	class CSetObjectListener : public GameObject
	{
	public:
		virtual void OnInitializedSetObject()
		{
			
		}
		
		virtual void OnPutSetObject(CSetAdapter& adapter)
		{
			
		}
		
		virtual void OnSetEditorParamChanged(CSetAdapter& adapter)
		{
			
		}
		
		virtual unsigned int GetAdsorbGuidePathID()
		{
			return 0;
		}

		virtual double GetAdsorbPathPosition()
		{
			return -1.0;
		}

		virtual Vector3 GetAdsorbPathOffset()
		{
			return { 0, 0, 0 };
		}

		
		virtual void SetAppearance(float opacity) // not sure if this is opacity
		{
			
		}
	};
}
