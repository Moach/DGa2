#include "DGa2.h"





void DGa2::clbkLoadStateEx (FILEHANDLE scn, void *status)
{
	char *line;
	while (oapiReadScenario_nextline (scn, line)) {

		if (!strnicmp (line, "MYPARAM", 7)) {
			sscanf (line+7, "%lf", &loadPar);

		} else {
			ParseScenarioLineEx (line, status);
		}
	}
}


void DGa2::clbkSaveState (FILEHANDLE scn)
{
	VESSEL2::clbkSaveState (scn);
	oapiWriteScenario_float (scn, "MYPARAM", loadPar);
}





inline bool DGa2_MovingPart::operate(double& dt, VESSEL& vsl)
{
	switch (mp_status)
	{
	case MP_MOVING:


		pos = pos + (rate * dt);

		if (pos >= 1.0)
		{
			pos = 1.0;
			mp_status = MP_HI_DETENT;
		}
		vsl.SetAnimation (anim_idx,  pos);

		return true;

	case MP_REVERSING:

		pos = pos - (rate * dt);

		if (pos <= 0.0)
		{
			pos = 0.0;
			mp_status = MP_LOW_DETENT;
		}
		vsl.SetAnimation (anim_idx, pos);

		return true;
	}
	
	//
	return false;
}




inline int DGa2_MovingPart::toggle()
{

	if(mp_status ==  MP_REVERSING || mp_status == MP_LOW_DETENT)
	{
		mp_status = MP_MOVING;
	}
	else if(mp_status == MP_MOVING || mp_status == MP_HI_DETENT)
	{
		mp_status = MP_REVERSING;
	}
	
	return mp_status;
}

inline int DGa2_MovingPart::toggle(bool b)
{

	if(b && (mp_status ==  MP_REVERSING || mp_status == MP_LOW_DETENT))
	{
		mp_status = MP_MOVING;
	}
	else if(!b && (mp_status == MP_MOVING || mp_status == MP_HI_DETENT))
	{
		mp_status = MP_REVERSING;
	}

	return mp_status;
}




void DGa2::clbkPostStep(double simt, double simdt, double mjd)
{
	//
	//SetAnimation(anim_InletDoors, GetThrusterLevel (main_eng_arr[0])); // just checking...
	
	bayDoors->operate (simdt, *this);
	noseCone->operate (simdt, *this);
	
	deltaT = simdt;
	
	
	// landing gear operations
	bool gearOp = landingGears->operate (simdt, *this);
	//
	if (gearOp && landingGearDoorsFore->mp_status == MP_LOW_DETENT) // when gears move, these should be open
	{
		landingGearDoorsFore->toggle(true);
		landingGearDoorsAft->toggle(true);
	} 
	else if (!gearOp && landingGearDoorsFore->mp_status == MP_HI_DETENT) // and close once gears stop
	{
		landingGearDoorsFore->toggle(false);
		landingGearDoorsAft->toggle(false);
	}
	//
	landingGearDoorsFore->operate (simdt, *this);
	landingGearDoorsAft->operate (simdt, *this);
}



// --------------------------------------------------------------
// Process direct key events
// --------------------------------------------------------------
int DGa2::clbkConsumeDirectKey (char *kstate)
{
	/*
	if (KEYMOD_ALT (kstate)) {
		if (KEYDOWN (kstate, OAPI_KEY_ADD)) { // increment scram thrust
			if (scramjet)
				for (int i = 0; i < 2; i++) {
					IncThrusterLevel (th_scram[i], oapiGetSimStep() * 0.3);
					scram_intensity[i] = GetThrusterLevel (th_scram[i]) * scram_max[i];
				}
				RESETKEY (kstate, OAPI_KEY_ADD);
		}
		if (KEYDOWN (kstate, OAPI_KEY_SUBTRACT)) { // decrement scram thrust
			if (scramjet)
				for (int i = 0; i < 2; i++) {
					IncThrusterLevel (th_scram[i], oapiGetSimStep() * -0.3);
					scram_intensity[i] = GetThrusterLevel (th_scram[i]) * scram_max[i];
				}
				RESETKEY (kstate, OAPI_KEY_SUBTRACT);
		}
	}*/
	return 0;
}

// --------------------------------------------------------------
// Process buffered key events
// --------------------------------------------------------------

//
int DGa2::clbkConsumeBufferedKey (DWORD key, bool down, char *kstate)
{
	if (down) return 0;
	
	switch (key)
	{
		case OAPI_KEY_B: // bay door operation...
			//
			
			if(GetAtmDensity ()) // let's keep them from being ripped off... they're really expensive
			{
				OUT "cannot operate bay doors in atmospheric flight" ENT;
				return 0;
			}
			bayDoors->toggle();
			
		break;
		
		case OAPI_KEY_N: // nose cone operation...
			noseCone->toggle();
			break;
			
		case OAPI_KEY_G: // nose cone operation...
			landingGears->toggle();
			break;
			
			
		case OAPI_KEY_EQUALS:
			OUT "ENGINES >> next stage" ENT;
		break;
		
		case OAPI_KEY_MINUS:
			OUT "ENGINES >> prev stage" ENT;
		break;
			
			
		default:
		break;
	}
	
	/*
	
	if (!down) return 0; // only process keydown events
	if (Playback()) return 0; // don't allow manual user input during a playback

	if (KEYMOD_SHIFT (kstate)) {
	} else if (KEYMOD_CONTROL (kstate)) {
		switch (key) {
		case OAPI_KEY_SPACE: // open control dialog
			oapiOpenDialogEx (g_Param.hDLL, IDD_CTRL, Ctrl_DlgProc, DLG_CAPTIONCLOSE, this);
			return 1;
		case OAPI_KEY_B:
			RevertAirbrake ();
			return 1;
		}
	} else {
		switch (key) {
		case OAPI_KEY_D:  // "operate radiator"
			RevertRadiator ();
			return 1;
		case OAPI_KEY_G:  // "operate landing gear"
			RevertLandingGear ();
			return 1;
		case OAPI_KEY_K:  // "operate docking port"
			RevertDockingPort ();
			return 1;
		case OAPI_KEY_O:  // "operate outer airlock"
			RevertOuterAirlock ();
			return 1;
		}
	}*/
	return 0;
}
