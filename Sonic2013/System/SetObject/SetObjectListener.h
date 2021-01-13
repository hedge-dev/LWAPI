#pragma once

namespace app
{
	class CSetAdapter;
	
	class CSetObjectListener : public GameObject3D
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

		virtual csl::math::Vector3 GetAdsorbPathOffset()
		{
			return { 0, 0, 0 };
		}

		
		virtual void SetAppearance(float opacity) // not sure if this is opacity
		{
			
		}
	};
}