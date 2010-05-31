#include "DGa2.h"
#include "DGa2_DVC.h"



//
bool DGa2::clbkVCMouseEvent (int id, int ev, VECTOR3&p)
{
	//
	OUT "click! area: "<< id ENT
	
	switch (id & 0xFFFF00)
	{
		case DVC_AREA_MFDL_BUTTONS:
		
			PlayVesselWave3 (SFXID, SFX_BEEPSHORT);
			oapiProcessMFDButton (MFD_LEFT, id & 0x0000FF, ev);
		return true;
		
		case DVC_AREA_MFDC_BUTTONS:

			PlayVesselWave3 (SFXID, SFX_BEEPSHORT);
			oapiProcessMFDButton (MFD_USER1, id & 0x0000FF, ev);
		return true;
		
		case DVC_AREA_MFDR_BUTTONS:

			PlayVesselWave3 (SFXID, SFX_BEEPSHORT);
			oapiProcessMFDButton (MFD_RIGHT, id & 0x0000FF, ev);
		return true;
		
		
		case DVC_AREA_MFDCONTROLS:
			
			//
			PlayVesselWave3 (SFXID, SFX_BEEPDOUBLE);
			switch(id)
			{
				case DVC_AREA_MFDL_SEL:
					
					oapiSendMFDKey (MFD_LEFT, OAPI_KEY_F1);
					return true;
				
				case DVC_AREA_MFDC_SEL:

					oapiSendMFDKey (MFD_USER1, OAPI_KEY_F1);
					return true;
					
				case DVC_AREA_MFDR_SEL:

					oapiSendMFDKey (MFD_RIGHT, OAPI_KEY_F1);;
					return true;
					
				case DVC_AREA_MFDL_INFO:

					oapiSendMFDKey (MFD_LEFT, OAPI_KEY_GRAVE);
					return true;

				case DVC_AREA_MFDC_INFO:

					oapiSendMFDKey (MFD_USER1, OAPI_KEY_GRAVE);
					return true;

				case DVC_AREA_MFDR_INFO:

					oapiSendMFDKey (MFD_RIGHT, OAPI_KEY_GRAVE);;
					return true;
			
			}
	}
	
	return false;
}