#pragma once

#ifndef ORBITER_MODULE

#define STRICT



	#include "../include/Orbitersdk.h"

	#include "OrbiterSoundSDK35.h"
	#include <math.h>
	#include <string>
	#include <iostream>
	#include <sstream>
	#include <iomanip>


	#define OUT cout <<
	#define ENT << endl;
	

#define ORBITER_MODULE




#define MAXFUEL_MAIN 145000.0
#define MAXFUEL_RCS 1200.0

#define MAXTHRUST_MAIN 1300000.0
#define MAXTRHUST_RCS 3500.0

#define ISP_MAIN_OPEN_VAC 15000
#define ISP_MAIN_OPEN_AGL 12000

#define NML_AGL_PRS 101.4e3

#define RCS_FX_LSCALE 0.8
#define RCS_FX_WSCALE 0.038


// hotpoint vectors

#define V3_RCS_TAILUP_L_01 _V(8.75059, -1.3337, -18.7238)
#define V3_RCS_TAILUP_L_02 _V(8.39211, -1.3337, -18.7312)
#define V3_RCS_ACT_BANK_L _V(8.58744, -1.16195, -18.7238)
#define V3_RCS_TAILDOWN_L_02 _V(8.39662, -1.00531, -18.7144)
#define V3_RCS_TAILDOWN_L_01 _V(8.74223, -1.00531, -18.7144)
#define V3_RCS_TAILDOWN_R_02 _V(8.36646, -1.00531, -18.728)
#define V3_RCS_TAILUP_R_01 _V(-8.75165, -1.3337, -18.7238)
#define V3_RCS_TAILUP_R_02 _V(-8.39317, -1.3337, -18.7312)
#define V3_RCS_ACT_BANK_R _V(-8.58849, -1.16195, -18.7238)
#define V3_RCS_TAILDOWN_R_01 _V(-8.74328, -1.00531, -18.7144)
#define V3_RCS_TAILDOWN_R_01 _V(-8.74328, -1.00531, -18.7144)
#define V3_RCS_NOSEDOWN_01 _V(0.608067, -0.137917, 26.6754)
#define V3_RCS_NOSEDOWN_02 _V(0.685618, -0.0647135, 26.3937)
#define V3_RCS_NOSERIGHT_01 _V(0.810028, 0.0100853, 26.1961)
#define V3_RCS_NOSERIGHT_02 _V(0.846548, 0.0183651, 25.8832)
#define V3_RCS_NOSEUP_01 _V(0.815009, -0.240087, 26.4861)
#define V3_RCS_NOSEUP_02 _V(0.764681, -0.380358, 26.18)
#define V3_RCS_LINBACK_01 _V(2.63178, -0.2456, 21.92)
#define V3_RCS_LINBACK_02 _V(2.88047, -0.230677, 21.203)
#define V3_RCS_LINBACK_03 _V(3.12795, -0.225506, 20.3428)
#define V3_RCS_LINFWD_01 _V(5.00221, -0.970151, -15.9877)
#define V3_RCS_LINFWD_02 _V(4.62779, -0.983613, -15.9877)
#define V3_RCS_LINFWD_03 _V(4.24975, -0.967775, -15.9877)
#define V3_RCS_TAILRIGHT_01 _V(3.3811, -0.248591, -16.7706)
#define V3_RCS_TAILRIGHT_02 _V(3.3811, -0.248449, -17.0705)
#define V3_RCS_TAILRIGHT_03 _V(3.3811, -0.237208, -17.3376)
#define V3_THR_MAIN_L _V(1.59979, 0.0167372, -16.2821)
#define V3_THR_RAMC_L _V(1.98892, -1.79736, -7.79007)
#define V3_RCS_ACT_TAIL_V _V(0.0, -1.22882, -18.7238)
#define V3_RCS_ACT_TAIL_H _V(0.0, -0.261495, -17.1446)
#define V3_RCS_ACT_NOSE_V _V(0.0, -0.0993336, 26.4209)
#define V3_RCS_ACT_NOSE_H _V(0.0, -0.00612795, 26.0378)
#define V3_RCS_ACT_LIN_BACK _V(0.0, -0.0236707, 21.1243)
#define V3_RCS_ACT_LIN_FWD _V(0.0, -1.00555, -15.8855)
#define V3_RCS_NOSEDOWN_03 _V(-0.637305, -0.137917, 26.6754)
#define V3_RCS_NOSEDOWN_04 _V(-0.714857, -0.0647135, 26.3937)
#define V3_RCS_NOSELEFT_01 _V(-0.839267, 0.0100853, 26.1961)
#define V3_RCS_NOSELEFT_02 _V(-0.875787, 0.0183651, 25.8832)
#define V3_RCS_NOSEUP_03 _V(-0.844248, -0.240087, 26.4861)
#define V3_RCS_NOSEUP_04 _V(-0.793919, -0.380358, 26.18)
#define V3_RCS_LINBACK_04 _V(-2.66102, -0.2456, 21.92)
#define V3_RCS_LINBACK_05 _V(-2.90971, -0.230677, 21.203)
#define V3_RCS_LINBACK_06 _V(-3.15719, -0.225506, 20.3428)
#define V3_RCS_TAILDOWN_R_01 _V(-9.21025, -1.00531, -18.7144)
#define V3_RCS_TAILDOWN_R_02 _V(-8.83342, -1.00531, -18.728)
#define V3_RCS_TAILUP_R_01 _V(-9.21861, -1.3337, -18.7238)
#define V3_RCS_TAILUP_R_02 _V(-8.86014, -1.3337, -18.7312)
#define V3_RCS_LINFWD_04 _V(-5.03144, -0.970151, -15.9877)
#define V3_RCS_LINFWD_05 _V(-4.65703, -0.983613, -15.9877)
#define V3_RCS_LINFWD_06 _V(-4.27899, -0.967775, -15.9877)
#define V3_RCS_TAILLEFT_01 _V(-3.41034, -0.248591, -16.7706)
#define V3_RCS_TAILLEFT_02 _V(-3.41034, -0.248449, -17.0705)
#define V3_RCS_TAILLEFT_03 _V(-3.41034, -0.237208, -17.3376)
#define V3_THR_MAIN_R _V(-1.62902, 0.0167372, -16.2821)
#define V3_THR_RAMC_R _V(-2.01816, -1.79736, -7.79007)


#define V3_DOCKPORT_NOSE _V(-0.0113345, -0.189793, 26.9839)

#define V3_TOUCHDOWN_C _V(0.00566546, -5.00912, 18.0903)
#define V3_TOUCHDOWN_R _V(7.80444, -5.31145, -3.84937)
#define V3_TOUCHDOWN_L _V(-7.80444, -5.31145, -3.84937)


#define V3_VC_EYEPOINT _V(0, 1.53738, 24.4835)
#define V3_VC_HUDCENTER _V(0, 1.53738, 24.9373)





// mesh tags ===============================


//     external
#define MGP_ID_BayDoor_L 0
#define MGP_ID_BayDoor_R 1
#define MGP_ID_inlet_door_L 2
#define MGP_ID_scram_door_L 3
#define MGP_ID_radiator_door_L 4
#define MGP_ID_GEARDOOR_C_AFTL 5
#define MGP_ID_bleed_doors 6
#define MGP_ID_GEARDOOR_C_FORL 7
#define MGP_ID_cabin_hatch 8
#define MGP_ID_Object06 9
#define MGP_ID_GEARDOOR_R_INBD 10
#define MGP_ID_GEARDOOR_R_OTBD 11
#define MGP_ID_dgpilot1_1 12
#define MGP_ID_Box07 13
#define MGP_ID_Box08 14
#define MGP_ID_Cylinder03 15
#define MGP_ID_EX 16
#define MGP_ID_Box06 17
#define MGP_ID_dgint1_1 18
#define MGP_ID_Box04 19
#define MGP_ID_inlet_door_R 20
#define MGP_ID_Object09 21
#define MGP_ID_elevon_R 22
#define MGP_ID_rudderon_R 23
#define MGP_ID_rudderon_L_BOT 24
#define MGP_ID_Line04 25
#define MGP_ID_elevon_L 26
#define MGP_ID_LGSTRUT_C 27
#define MGP_ID_LGSTRUT_L 28
#define MGP_ID_LGSTRUT_R 29
#define MGP_ID_GEARDOOR_L_OTBD 30
#define MGP_ID_GEARDOOR_L_INBD 31
#define MGP_ID_GEARDOOR_C_FORR 32
#define MGP_ID_GEARDOOR_C_AFTR 33
#define MGP_ID_wheelwell_R 34
#define MGP_ID_wheelwell_L 35
#define MGP_ID_upper_inlets_int 36
#define MGP_ID_main_exh_int 37
#define MGP_ID_ramcaster_exhs_int 38
#define MGP_ID_bleed_vents_int 39
#define MGP_ID_rcs_exhs_ports 40
#define MGP_ID_scram_door_R 41
#define MGP_ID_rudderon_L_TOP 42
#define MGP_ID_RAMCASTER_int 43
#define MGP_ID_visor_cover 44
#define MGP_ID_visor_glass_frame 45
#define MGP_ID_visor_panel_R 46
#define MGP_ID_visor_panel_L 47
#define MGP_ID_cockpitglass 48
#define MGP_ID_visor_glass001 49
//
// check DVC header for dvc ids
//



//===============================================

//                     sound effects


#define SFX_BEEPSHORT   1
#define SFX_BEEPDOUBLE  2
#define SFX_BEEPDENY    3
#define SFX_GEAROPERATE 4


//
//
using namespace std;



enum MP_STATE 
{MP_MOVING = 1, MP_LOW_DETENT = 2, MP_HI_DETENT = 4, MP_REVERSING = 3, MP_INOP = 0};

//
//
struct DGa2_MovingPart  /// implemented in vessel ops
{
	UINT anim_idx;
	double pos;
	double rate;
	MP_STATE mp_status; //

	DGa2_MovingPart(UINT idx, double rt, MP_STATE st, double stPos = 0.0, VESSEL* vsl = NULL)
	{
		anim_idx = idx;
		pos = stPos;
		rate = rt;
		mp_status = st;
		
		if(vsl)
			vsl->SetAnimation(idx, stPos);
	}
	
	inline bool operate(double& dt, VESSEL& vsl);
	inline int toggle();
	inline int toggle(bool b);
	
};










struct DGa2 : VESSEL2
{

	
	////////////////////////////////////////////////////////////////////////

	MESHHANDLE mdl_dvc;
	MESHHANDLE mdl_ext;

	PROPELLANT_HANDLE main_fuel_res;
	PROPELLANT_HANDLE rcs_fuel_res;

	THGROUP_HANDLE main_eng_grp;
	//
	THRUSTER_HANDLE main_onbrdox_thrgp[2];
	THRUSTER_HANDLE main_extrnox_thrgp[2];
	THRUSTER_HANDLE ramcaster_lo_thrgp[2];
	THRUSTER_HANDLE ramcaster_hi_thrgp[2];
	//
	THRUSTER_HANDLE hoverjets_thrgp[2];
	

	double loadPar;

	UINT anim_InletDoors;
	
	// moving parts
	//
	DGa2_MovingPart *bayDoors;
	DGa2_MovingPart *noseCone;
	//
	DGa2_MovingPart *landingGears;
	DGa2_MovingPart *landingGearDoorsAft;
	DGa2_MovingPart *landingGearDoorsFore;
	
	int SFXID;
	
	double deltaT; // master sim delta-time
	
	
	///////////
	
	
	/////////////////////////////////////////////////////////////////////////
	//
	//       -- mind the file names on sections below
	
	
	//        vessel setup
	//
	DGa2(OBJHANDLE vsl_hndl, int fltModel);
	~DGa2();
	//
	void clbkSetClassCaps (FILEHANDLE cfg);
	//
	void clbkLoadStateEx (FILEHANDLE scn, void *status);
	void clbkSaveState (FILEHANDLE scn);
	void clbkPostCreation (void);
	
	
	//        DVC setup
	//
	bool clbkLoadVC (int id);
	void SetupVCGDI();
	
	
	//        vessel setAnims
	//
	void defineAnimations();
	void defineAnimationsVC();
	
	
	//         vessel ops
	//
	void clbkPostStep(double simt, double simdt, double mjd);
	int  clbkConsumeDirectKey (char *kstate);
	int  clbkConsumeBufferedKey (DWORD key, bool down, char *kstate);
	
	//   DVC displays
	//
	void clbkDrawHUD (int mode, const HUDPAINTSPEC *hps, HDC hDC);
	bool clbkVCRedrawEvent (int id, int event, SURFHANDLE surf);

	//   DVC controls
	//
	bool clbkVCMouseEvent (int id, int ev, VECTOR3&p);

	// oapi
	//
	void setInputHook();
};







#endif
