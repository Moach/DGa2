

#include "DGa2.h"







DGa2::DGa2 (OBJHANDLE vsl_hndl, int fltModel) : VESSEL2(vsl_hndl, fltModel)
{
	//
	OUT "Delta-Starliner G42 :: vessel created!\n\n" ENT;
	
	defineAnimations();
	defineAnimationsVC();
}
DGa2::~DGa2()
{
	//
	OUT "Delta-Starliner G42 :: vessel dumped!\n\n" ENT;
	
	// get rid of the heaped moving parts
	delete landingGears;
	delete bayDoors;
	delete noseCone;
}


//             from stock DG - blame Martin
// ==============================================================
// Airfoil coefficient functions
// Return lift, moment and zero-lift drag coefficients as a
// function of angle of attack (alpha or beta)
// ==============================================================

// 1. vertical lift component (wings and body)

void VLiftCoeff (VESSEL *v, double aoa, double M, double Re, void *context, double *cl, double *cm, double *cd)
{
	int i;
	const int nabsc = 9;
	static const double AOA[nabsc] = {-180*RAD,-60*RAD,-30*RAD, -2*RAD, 15*RAD,20*RAD,25*RAD,60*RAD,180*RAD};
	static const double CL[nabsc]  = {       0,      0,   -0.4,      0,    0.7,     1,   0.8,     0,      0};
	static const double CM[nabsc]  = {       0,      0,  0.014, 0.0039, -0.006,-0.008,-0.010,     0,      0};
	for (i = 0; i < nabsc-1 && AOA[i+1] < aoa; i++);
	double f = (aoa-AOA[i]) / (AOA[i+1]-AOA[i]);
	*cl = CL[i] + (CL[i+1]-CL[i]) * f;  // aoa-dependent lift coefficient
	*cm = CM[i] + (CM[i+1]-CM[i]) * f;  // aoa-dependent moment coefficient
	double saoa = sin(aoa);
	double pd = 0.015 + 0.4*saoa*saoa;  // profile drag
	*cd = pd + oapiGetInducedDrag (*cl, 1.5, 0.7) + oapiGetWaveDrag (M, 0.75, 1.0, 1.1, 0.04);
	// profile drag + (lift-)induced drag + transonic/supersonic wave (compressibility) drag
}

// 2. horizontal lift component (vertical stabilisers and body)

void HLiftCoeff (VESSEL *v, double beta, double M, double Re, void *context, double *cl, double *cm, double *cd)
{
	int i;
	const int nabsc = 8;
	static const double BETA[nabsc] = {-180*RAD,-135*RAD,-90*RAD,-45*RAD,45*RAD,90*RAD,135*RAD,180*RAD};
	static const double CL[nabsc]   = {       0,    +0.3,      0,   -0.3,  +0.3,     0,   -0.3,      0};
	for (i = 0; i < nabsc-1 && BETA[i+1] < beta; i++);
	*cl = CL[i] + (CL[i+1]-CL[i]) * (beta-BETA[i]) / (BETA[i+1]-BETA[i]);
	*cm = 0.0;
	*cd = 0.015 + oapiGetInducedDrag (*cl, 1.5, 0.6) + oapiGetWaveDrag (M, 0.75, 1.0, 1.1, 0.04);
}






void DGa2::clbkSetClassCaps (FILEHANDLE cfg)
{
	
	OUT "Delta-Starliner G42 :: Start Class Caps" ENT;
	
	//setInputHook();
	SetupVCGDI();
	
	
	SetEmptyMass (95000.0);
	SetSize (10.0);
	
	//
	SetAlbedoRGB (_V(0.77,0.20,0.13));
	SetGravityGradientDamping (20.0);
	SetCW (0.09, 0.09, 2, 1.4);
	SetWingAspect (0.6);
	SetWingEffectiveness (1.2);	
	SetCrossSections (_V(53.0,186.9,25.9));
	SetSurfaceFrictionCoeff (0.07, 0.3);
	SetMaxWheelbrakeForce (3e5);
	SetPMI (_V(15.5,22.1,7.7)); 
	SetRotDrag (_V(0.10,0.13,0.04));


	//SetDockParams (V3_DOCKPORT_NOSE, _V(0,0,1), _V(0,1,0));
	
	
	SetTouchdownPoints (V3_TOUCHDOWN_C, V3_TOUCHDOWN_L, V3_TOUCHDOWN_R);
	
	
	EnableTransponder (true);
	
	
	
	mdl_ext = oapiLoadMeshGlobal ("DGa2\\DeltaStarliner");
	mdl_dvc = oapiLoadMeshGlobal ("DGa2\\DeltaStarliner_pit");
	SetMeshVisibilityMode (AddMesh(mdl_ext), MESHVIS_EXTERNAL);
	SetMeshVisibilityMode (AddMesh(mdl_dvc), MESHVIS_VC);
	
	OUT " -- Meshes Loaded" ENT;
	
	
	PARTICLESTREAMSPEC contrail = {
		0, 8.0, 3, 150, 0.3, 3.5, 4, 3.0, PARTICLESTREAMSPEC::DIFFUSE,
		PARTICLESTREAMSPEC::LVL_PSQRT, 0, 2,
		PARTICLESTREAMSPEC::ATM_PLOG, 1e-4, 1
	};
	PARTICLESTREAMSPEC exhaust_main = {
		0, 2.0, 10, 150, 0.1, 0.2, 16, 1.0, PARTICLESTREAMSPEC::EMISSIVE,
		PARTICLESTREAMSPEC::LVL_SQRT, 0, 1,
		PARTICLESTREAMSPEC::ATM_PLOG, 1e-5, 0.1
	};
	
	
	//
	main_fuel_res = CreatePropellantResource(MAXFUEL_MAIN);
	
	main_onbrdox_thrgp[0] = CreateThruster(V3_THR_MAIN_L, _V(0,0,1), MAXTHRUST_MAIN, main_fuel_res, ISP_MAIN_OPEN_VAC, ISP_MAIN_OPEN_AGL, NML_AGL_PRS);
	main_onbrdox_thrgp[1] = CreateThruster(V3_THR_MAIN_R, _V(0,0,1), MAXTHRUST_MAIN, main_fuel_res, ISP_MAIN_OPEN_VAC, ISP_MAIN_OPEN_AGL, NML_AGL_PRS);
	
	main_eng_grp = CreateThrusterGroup (main_onbrdox_thrgp, 2, THGROUP_MAIN);
	
	
	AddExhaust (main_onbrdox_thrgp[0], 12, 1);
	AddExhaust (main_onbrdox_thrgp[1], 12, 1);
	/*
	AddExhaustStream (main_eng_arr[0], V3_THR_MAIN_L, &contrail);
	AddExhaustStream (main_eng_arr[1], V3_THR_MAIN_R, &contrail);
	AddExhaustStream (main_eng_arr[0], V3_THR_MAIN_L, &exhaust_main);
	AddExhaustStream (main_eng_arr[1], V3_THR_MAIN_R, &exhaust_main);
	*/
	
	OUT " -- Main Engines Ready" ENT;
	
	rcs_fuel_res   = CreatePropellantResource (MAXFUEL_RCS); // RCS tank  (fuel + oxidant)
	const double ISP = 4e4;
	
	//
	
	
	THRUSTER_HANDLE th_rcs_pitchUp[2], th_rcs_pitchDn[2],  th_rcs_vertUp[2], th_rcs_vertDown[2];
	THRUSTER_HANDLE th_rcs_yawLeft[2], th_rcs_yawRight[2], th_rcs_horLeft[2], th_rcs_horRight[2];
	THRUSTER_HANDLE th_rcs_fwd[1], th_rcs_back[1];
	THRUSTER_HANDLE th_rcs_bankRight[2], th_rcs_bankLeft[2];
	
	
	//
	th_rcs_pitchUp[0] = th_rcs_vertUp[0]   = CreateThruster (V3_RCS_ACT_NOSE_V, _V(0, 1,0),  MAXTRHUST_RCS, rcs_fuel_res, ISP); // raise bow 
	th_rcs_pitchUp[1] = th_rcs_vertDown[1] = CreateThruster (V3_RCS_ACT_TAIL_V, _V(0, -1,0), MAXTRHUST_RCS, rcs_fuel_res, ISP); // drop stern
	//
	th_rcs_pitchDn[0] = th_rcs_vertDown[0] = CreateThruster (V3_RCS_ACT_NOSE_V, _V(0, -1,0), MAXTRHUST_RCS, rcs_fuel_res, ISP); // drop bow
	th_rcs_pitchDn[1] = th_rcs_vertUp[1]   = CreateThruster (V3_RCS_ACT_TAIL_V, _V(0,  1,0), MAXTRHUST_RCS, rcs_fuel_res, ISP); // raise stern
	
	//
	CreateThrusterGroup (th_rcs_pitchUp, 2, THGROUP_ATT_PITCHUP);
	CreateThrusterGroup (th_rcs_pitchDn, 2, THGROUP_ATT_PITCHDOWN);
	CreateThrusterGroup (th_rcs_vertUp,  2, THGROUP_ATT_UP);
	CreateThrusterGroup (th_rcs_vertDown,2, THGROUP_ATT_DOWN);
	
	AddExhaust (th_rcs_pitchUp[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_NOSEUP_01, _V(0,-1,0)); // raise bow
	AddExhaust (th_rcs_pitchUp[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_NOSEUP_02, _V(0,-1,0));
	AddExhaust (th_rcs_pitchUp[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_NOSEUP_03, _V(0,-1,0));
	AddExhaust (th_rcs_pitchUp[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_NOSEUP_04, _V(0,-1,0));
	
	AddExhaust (th_rcs_pitchUp[1], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILDOWN_R_01, _V(0,1,0)); // drop stern
	AddExhaust (th_rcs_pitchUp[1], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILDOWN_R_02, _V(0,1,0));
	AddExhaust (th_rcs_pitchUp[1], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILDOWN_L_01, _V(0,1,0));
	AddExhaust (th_rcs_pitchUp[1], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILDOWN_L_02, _V(0,1,0));
	
	AddExhaust (th_rcs_pitchDn[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_NOSEDOWN_01, _V(0,1,0)); // drop bow
	AddExhaust (th_rcs_pitchDn[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_NOSEDOWN_02, _V(0,1,0));
	AddExhaust (th_rcs_pitchDn[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_NOSEDOWN_03, _V(0,1,0));
	AddExhaust (th_rcs_pitchDn[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_NOSEDOWN_04, _V(0,1,0));
	 
	AddExhaust (th_rcs_pitchDn[1], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILUP_R_01, _V(0,-1,0)); // raise stern
	AddExhaust (th_rcs_pitchDn[1], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILUP_R_02, _V(0,-1,0));
	AddExhaust (th_rcs_pitchDn[1], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILUP_L_01, _V(0,-1,0));
	AddExhaust (th_rcs_pitchDn[1], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILUP_L_02, _V(0,-1,0));
	
	
	////////////////////////
	
	th_rcs_yawLeft[0]  = th_rcs_horLeft[0]  = CreateThruster (V3_RCS_ACT_NOSE_H, _V(-1, 0,0), MAXTRHUST_RCS * .5, rcs_fuel_res, ISP) ;  // bow left
	th_rcs_yawLeft[1]  = th_rcs_horRight[1] = CreateThruster (V3_RCS_ACT_TAIL_H, _V( 1, 0,0), MAXTRHUST_RCS * .75, rcs_fuel_res, ISP);  // stern right
	//
	th_rcs_yawRight[0] = th_rcs_horRight[0] = CreateThruster (V3_RCS_ACT_NOSE_H, _V( 1, 0,0), MAXTRHUST_RCS * .75, rcs_fuel_res, ISP); // bow right
	th_rcs_yawRight[1] = th_rcs_horLeft[1]  = CreateThruster (V3_RCS_ACT_TAIL_H, _V(-1, 0,0), MAXTRHUST_RCS * .5, rcs_fuel_res, ISP);   // stern left
	
	//
	CreateThrusterGroup (th_rcs_yawLeft,  2,  THGROUP_ATT_YAWLEFT);
	CreateThrusterGroup (th_rcs_yawRight, 2,  THGROUP_ATT_YAWRIGHT);
	CreateThrusterGroup (th_rcs_horLeft,  2,  THGROUP_ATT_LEFT);
	CreateThrusterGroup (th_rcs_horRight, 2,  THGROUP_ATT_RIGHT);
	
	AddExhaust (th_rcs_yawLeft[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_NOSERIGHT_01, _V(1,0,0)); // bow left
	AddExhaust (th_rcs_yawLeft[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_NOSERIGHT_02, _V(1,0,0));
	
	AddExhaust (th_rcs_yawRight[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_NOSELEFT_01, _V(-1,0,0)); // bow right
	AddExhaust (th_rcs_yawRight[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_NOSELEFT_02, _V(-1,0,0));
	
	AddExhaust (th_rcs_yawLeft[1], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILLEFT_01,_V(-1,0,0)); // stern left
	AddExhaust (th_rcs_yawLeft[1], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILLEFT_02,_V(-1,0,0));
	AddExhaust (th_rcs_yawLeft[1], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILLEFT_03,_V(-1,0,0));
	
	AddExhaust (th_rcs_yawRight[1], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILRIGHT_01, _V(1,0,0)); // stern right
	AddExhaust (th_rcs_yawRight[1], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILRIGHT_02, _V(1,0,0));
	AddExhaust (th_rcs_yawRight[1], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILRIGHT_03, _V(1,0,0));
	
	/////////////////////////////
	
	th_rcs_fwd[0]  = CreateThruster (V3_RCS_ACT_LIN_FWD,  _V(0,0, 1), MAXTRHUST_RCS * 1.5, rcs_fuel_res, ISP);
	th_rcs_back[0] = CreateThruster (V3_RCS_ACT_LIN_BACK, _V(0,0,-1), MAXTRHUST_RCS * 1.5, rcs_fuel_res, ISP);
	
	CreateThrusterGroup (th_rcs_fwd,  1, THGROUP_ATT_FORWARD);
	CreateThrusterGroup (th_rcs_back, 1, THGROUP_ATT_BACK);
	
	//
	AddExhaust (th_rcs_back[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_LINBACK_01, _V(0,0,-1));
	AddExhaust (th_rcs_back[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_LINBACK_02, _V(0,0,-1));
	AddExhaust (th_rcs_back[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_LINBACK_03, _V(0,0,-1));
	AddExhaust (th_rcs_back[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_LINBACK_04, _V(0,0,-1));
	AddExhaust (th_rcs_back[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_LINBACK_05, _V(0,0,-1));
	AddExhaust (th_rcs_back[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_LINBACK_06, _V(0,0,-1));
	
	AddExhaust (th_rcs_fwd[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_LINFWD_01, _V(0,0,-1));
	AddExhaust (th_rcs_fwd[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_LINFWD_02, _V(0,0,-1));
	AddExhaust (th_rcs_fwd[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_LINFWD_03, _V(0,0,-1));
	AddExhaust (th_rcs_fwd[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_LINFWD_04, _V(0,0,-1));
	AddExhaust (th_rcs_fwd[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_LINFWD_05, _V(0,0,-1));
	AddExhaust (th_rcs_fwd[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_LINFWD_06, _V(0,0,-1));
	
	
	///////////////////////////
	
	th_rcs_bankRight[0] = CreateThruster (V3_RCS_ACT_BANK_L, _V(0,  1, 0),  MAXTRHUST_RCS * .5, rcs_fuel_res, ISP);  // raise left
	th_rcs_bankRight[1] = CreateThruster (V3_RCS_ACT_BANK_R, _V(0, -1, 0), MAXTRHUST_RCS * .5, rcs_fuel_res, ISP);   // drop right
	
	th_rcs_bankLeft[0] = CreateThruster (V3_RCS_ACT_BANK_L, _V(0, -1, 0), MAXTRHUST_RCS * .5, rcs_fuel_res, ISP);   // drop left
	th_rcs_bankLeft[1] = CreateThruster (V3_RCS_ACT_BANK_R, _V(0,  1, 0),  MAXTRHUST_RCS * .5, rcs_fuel_res, ISP);  // raise right
	
	CreateThrusterGroup (th_rcs_bankRight, 2, THGROUP_ATT_BANKLEFT); // orbiter banking seems backwards... :P
	CreateThrusterGroup (th_rcs_bankLeft,  2, THGROUP_ATT_BANKRIGHT);// do note the switch
	
	AddExhaust (th_rcs_bankLeft[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILUP_R_01, _V(0,-1,0)); 
	AddExhaust (th_rcs_bankLeft[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILUP_R_02, _V(0,-1,0));
	AddExhaust (th_rcs_bankLeft[1], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILDOWN_L_01,  _V(0,1,0));
	AddExhaust (th_rcs_bankLeft[1], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILDOWN_L_02,  _V(0,1,0));
	
	AddExhaust (th_rcs_bankRight[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILUP_L_01,  _V(0,-1,0)); 
	AddExhaust (th_rcs_bankRight[0], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILUP_L_02,  _V(0,-1,0));
	AddExhaust (th_rcs_bankRight[1], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILDOWN_R_01, _V(0,1,0));
	AddExhaust (th_rcs_bankRight[1], RCS_FX_LSCALE, RCS_FX_WSCALE, V3_RCS_TAILDOWN_R_02, _V(0,1,0));
		
	
	OUT " -- RCS Systems set" ENT;
	

	CreateControlSurface (AIRCTRL_ELEVATOR,     5.0, 1.5, _V(   0,0,-18.0), AIRCTRL_AXIS_XPOS);
	CreateControlSurface (AIRCTRL_RUDDER,       2.0, 1.5, _V(   0,0,-18.0), AIRCTRL_AXIS_YPOS);
	CreateControlSurface2 (AIRCTRL_AILERON, 2.5, 1.5, _V( 7.5,0,-18), AIRCTRL_AXIS_XPOS);
	CreateControlSurface2 (AIRCTRL_AILERON, 2.5, 1.5, _V(-7.5,0,-18), AIRCTRL_AXIS_XNEG);
	//
	CreateControlSurface (AIRCTRL_ELEVATORTRIM, 10.3, 1.5, _V(   0,0,-7.2), AIRCTRL_AXIS_XPOS);
	
	
	
	CreateAirfoil3 (LIFT_VERTICAL, _V(0,0,-0.3), VLiftCoeff, 0, 45, 500, 1.5);
	// wing and body lift+drag components

	CreateAirfoil3 (LIFT_HORIZONTAL, _V(0,0,-1), HLiftCoeff, 0, 5, 25, 1.5);
	// vertical stabiliser and body lift and drag components
	
	
	OUT " -- Control Surfaces GO" ENT;
	
	
	InitNavRadios (4);
	
	OUT "Delta-Starliner G42 :: Done Class Caps\n" ENT;
	
}





//
//





void DGa2::clbkPostCreation (void)
{
	SFXID = ConnectToOrbiterSoundDLL3 (GetHandle ());
	//
	OUT "OrbiterSound connect >> " << SFXID ENT
	
	SoundOptionOnOff3 (SFXID, PLAYCOUNTDOWNWHENTAKEOFF, 0);
	
	ReplaceStockSound3 (SFXID, "Sound\\DGa2_sfx\\amb.wav", REPLACE_AIR_CONDITIONNING);
	
	RequestLoadVesselWave3 (SFXID, SFX_BEEPSHORT,  "Sound\\DGa2_sfx\\blip.wav",  INTERNAL_ONLY);
	RequestLoadVesselWave3 (SFXID, SFX_BEEPDOUBLE, "Sound\\DGa2_sfx\\ready.wav", INTERNAL_ONLY);
	RequestLoadVesselWave3 (SFXID, SFX_BEEPDENY,   "Sound\\DGa2_sfx\\beep.wav",  INTERNAL_ONLY);
}





