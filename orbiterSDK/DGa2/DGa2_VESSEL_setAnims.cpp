#include "DGa2.h"

//
// disused... delete if you want to...
inline void setVectorAxis(VECTOR3& v, VECTOR3& v1, VECTOR3& v2)
{
	//
	VECTOR3 dV = _V(v2.x - v1.x, v1.y - v2.y, v1.z - v2.z);
	double len = sqrt((dV.x * dV.x) + (dV.y * dV.y) + (dV.y * dV.y));

	//
	v.x = dV.x / len;
	v.y = dV.y / len;
	v.z = dV.z / len;

}


#define V3_HINGE_BAYDR_L _V(1.94938, 1.10794, 13.2922)
#define V3_HINGE_BAYDR_R _V(-1.99617, 1.16704, 5.84599)

#define V3_HINGE_INTDR_R _V(-2.5128, 0.617366, 7.73694)
#define V3_HINGE_INTDR_L _V(3.5271, 0.617556, 7.73671)

#define V3_TDIR_HINGE_BAYDR_L _V(-0.00198513, 0.00928237, -0.999955)
#define V3_TDIR_HINGE_BAYDR_R _V(0.00118532, -0.00408568, 0.999991)

#define V3_TDIR_HINGE_INTDR_R _V(0.999981, 0.000698005, -0.00606585)
#define V3_TDIR_HINGE_INTDR_L _V(0.999926, -0.000967029, 0.0121319)


#define VHINGE_ELEVONS_HINGE_L _V(-25.1, -1.49455, -11.6078),  _V(0.889818, 0.019304, -0.455907)
#define VHINGE_ELEVONS_HINGE_R _V(24.9753, -1.46115, -11.6365), _V(-0.889258, 0.0168734, -0.457094)



#define V3_LGSTRUT_L _V(-7.80382, -0.834367, -3.87187)
#define V3_LGSTRUT_R _V(7.71409, -0.834, -3.87187)
#define V3_LGSTRUT_C _V(0.0, -0.956942, 18.3684)

#define VHINGE_GDOOR_LR_HINGE _V(-3.31465, -2.2309, -0.951003), _V(0.0165015, -0.0136534, -0.999771)
#define VHINGE_GDOOR_RL_HINGE _V(3.2277, -2.2963, -5.74022), _V(0.0165013, 0.0136533, 0.999771)
#define VHINGE_GDOOR_LL_HINGE _V(-8.95951, -1.24726, -2.09405), _V(0.0398763, -0.0294983, -0.998769)
#define VHINGE_GDOOR_RR_HINGE _V(8.80699, -1.35424, -5.71635), _V(0.039876, 0.0294983, 0.998769)
#define VHINGE_GDOOR_CAR_HINGE _V(0.716957, -1.46209, 14.3683), _V(0.0120776, 0.0214787, 0.999696)
#define VHINGE_GDOOR_CFL_HINGE _V(-0.82999, -1.25658, 24.1011), _V(0.00912139, -0.0206244, -0.999746)
#define VHINGE_GDOOR_CFR_HINGE _V(0.783676, -1.34344, 19.8908), _V(0.00912116, 0.0206243, 0.999746)
#define VHINGE_GDOOR_CAL_HINGE _V(-0.791577, -1.34344, 19.8908), _V(0.0120198, -0.0214423, -0.999698)


#define V3_TDIR_RAMDOOR_L_HINGE _V(-0.999466, 0.030516, 0.011649)
#define V3_TDIR_RAMDOOR_R_HINGE _V(-0.999822, -0.0188617, -0.000580661)



#define V3_visor_cover _V(-0.00394821, 0.353031, 27.6734)
#define V3_visor_glass_frame _V(-0.00395155, -0.0603296, 24.0578)
#define VHINGE_VISOR_PANEL_R_AXIS _V(0.505705, 0.268476, 27.6456), _V(0.0418723, 0.313013, -0.948825)
#define VHINGE_VISOR_PANEL_L_AXIS _V(-0.513597, 0.268445, 27.6456), _V(-0.0418802, 0.313023, -0.948822)



void DGa2::defineAnimations()
{
	//
	anim_InletDoors = CreateAnimation(0.0);


	{ ///////////////////////////////////////////////// left inlet door
		static UINT groups[1] = {MGP_ID_inlet_door_L};
		//	
		static MGROUP_ROTATE InletDoor_L (0, groups, 1, V3_HINGE_INTDR_L, V3_TDIR_HINGE_INTDR_L, (float)(10 * RAD));
		//
		AddAnimationComponent (anim_InletDoors, 0, 1, &InletDoor_L);
	}

	{///////////////////////////////////////////////// right inlet door
		static UINT groups[1] = {MGP_ID_inlet_door_R};
		//	
		static MGROUP_ROTATE InletDoor_R (0, groups, 1, V3_HINGE_INTDR_R, V3_TDIR_HINGE_INTDR_R, (float)(10 * RAD));
		//
		AddAnimationComponent (anim_InletDoors, 0, 1, &InletDoor_R);
	}
	


	UINT anim_bayDoors = CreateAnimation (0.0);
	//
	// note on the bizarre... for some ungodly reason, the bay doors will hinge around the axis on the other side
	// for that reason we must switch the vectors for L and R  --  WTF??
	//
	{///////////////////////////////////////////////// left bay door
		static UINT groups[1] = {MGP_ID_BayDoor_L};
	
		//	
		static MGROUP_ROTATE BayDoor_L (0, groups, 1, V3_HINGE_BAYDR_R, V3_TDIR_HINGE_BAYDR_R, (float)(130 * RAD));
		//
		AddAnimationComponent (anim_bayDoors, 0, 0.5, &BayDoor_L);
	}
	{///////////////////////////////////////////////// right bay door
		static UINT groups[1] = {MGP_ID_BayDoor_R};
		//	
		static MGROUP_ROTATE BayDoor_R (0, groups, 1, V3_HINGE_BAYDR_L, V3_TDIR_HINGE_BAYDR_L, (float)(130 * RAD));
		//
		AddAnimationComponent (anim_bayDoors, 0.51, 1, &BayDoor_R);
	}
	
	bayDoors = new DGa2_MovingPart(anim_bayDoors, 0.05,  MP_LOW_DETENT, 0.0);
	
	
	
	
	
	UINT anim_visor = CreateAnimation (0.0);
	
	{///////////////////////////////////////////////// nose visor
		
		static UINT cover[1] = {MGP_ID_visor_cover};
		//	
		static MGROUP_ROTATE visor_cover (0, cover, 1, V3_visor_cover, _V(1,0,0), (float)(6.3 * RAD));
		
		
		static UINT adaptor[2] = {MGP_ID_visor_glass_frame, MGP_ID_visor_glass001};
		//	
		static MGROUP_ROTATE visor_adaptor (0, adaptor, 2, V3_visor_glass_frame, _V(1,0,0), (float)(-40 * RAD));
		
		
		static UINT panelR[1] = {MGP_ID_visor_panel_R};
		static UINT panelL[1] = {MGP_ID_visor_panel_L};
		//	
		static MGROUP_ROTATE visor_panelR (0, panelR, 1, VHINGE_VISOR_PANEL_R_AXIS, (float)( 34 * RAD));
		static MGROUP_ROTATE visor_panelL (0, panelL, 1, VHINGE_VISOR_PANEL_L_AXIS, (float)(-34 * RAD));
		
		
		AddAnimationComponent (anim_visor, 0.0, 0.8, &visor_cover);
		AddAnimationComponent (anim_visor, 0.5, 1,   &visor_adaptor);
		AddAnimationComponent (anim_visor, 0.0, 0.8, &visor_panelR);
		AddAnimationComponent (anim_visor, 0.0, 0.8, &visor_panelL);
	}

	noseCone = new DGa2_MovingPart(anim_visor, 0.1,  MP_LOW_DETENT, 0.0);
	
	
	
	
	// landing gears
	//
	UINT anim_lg = CreateAnimation (0.0);
	
	{///////////////////////////////////////////////// gears
		static UINT gpC[1] = {MGP_ID_LGSTRUT_C};
		static UINT gpL[1] = {MGP_ID_LGSTRUT_L};
		static UINT gpR[1] = {MGP_ID_LGSTRUT_R};
		//
		//	
		static MGROUP_ROTATE lg_C (0, gpC, 1, V3_LGSTRUT_C, _V(-1.0,0.0, 0.0), (float)(-95.0 * RAD));
		static MGROUP_ROTATE lg_L (0, gpL, 1, V3_LGSTRUT_L, _V( 0.0,0.0, 1.0), (float)(-90.0 * RAD));
		static MGROUP_ROTATE lg_R (0, gpR, 1, V3_LGSTRUT_R, _V( 0.0,0.0,-1.0), (float)(-90.0 * RAD));
		//
		AddAnimationComponent (anim_lg, 0.1, .9, &lg_C);
		AddAnimationComponent (anim_lg, 0.2, .9, &lg_L);
		AddAnimationComponent (anim_lg, 0.2, .9, &lg_R);
		
		
		//////////////////////////////////////////// doors
		static UINT gpDrC_L[1] = {MGP_ID_GEARDOOR_C_AFTL};
		static UINT gpDrC_R[1] = {MGP_ID_GEARDOOR_C_AFTR};
		static UINT gpDrL[1]   = {MGP_ID_GEARDOOR_L_OTBD};
		static UINT gpDrR[1]   = {MGP_ID_GEARDOOR_R_OTBD};
		
		static MGROUP_ROTATE lg_DrCL (0, gpDrC_L, 1, VHINGE_GDOOR_CAL_HINGE, (float)(120.0 * RAD));
		static MGROUP_ROTATE lg_DrCR (0, gpDrC_R, 1, VHINGE_GDOOR_CAR_HINGE, (float)(120.0 * RAD));
		//
		static MGROUP_ROTATE lg_DrL(0,  gpDrL, 1, VHINGE_GDOOR_LL_HINGE,  (float)(165.0 * RAD));
		static MGROUP_ROTATE lg_DrR (0, gpDrR, 1, VHINGE_GDOOR_RR_HINGE,  (float)(165.0 * RAD));
		
		AddAnimationComponent (anim_lg, 0.0, .2, &lg_DrCL);
		AddAnimationComponent (anim_lg, 0.0, .2, &lg_DrCR);
		AddAnimationComponent (anim_lg,  0.0, 1, &lg_DrL);
		AddAnimationComponent (anim_lg,  0.0, 1, &lg_DrR);
	}

	landingGears = new DGa2_MovingPart(anim_lg, 0.1,  MP_HI_DETENT, 1.0, this);
	
	
	
	
	
	///////////////////////////// front gear doors...
	//
	UINT anim_lgDoors_fore = CreateAnimation (0.0);
	{
		static UINT gp_doorL[1] = {MGP_ID_GEARDOOR_C_FORL};
		static UINT gp_doorR[1] = {MGP_ID_GEARDOOR_C_FORR};
		//
		static MGROUP_ROTATE gp_doorL_rotate (0, gp_doorL, 1, VHINGE_GDOOR_CFL_HINGE, (float)(100.0 * RAD));
		static MGROUP_ROTATE gp_doorR_rotate (0, gp_doorR, 1, VHINGE_GDOOR_CFR_HINGE, (float)(100.0 * RAD));
		
		AddAnimationComponent (anim_lgDoors_fore, 0.0, 1, &gp_doorL_rotate);
		AddAnimationComponent (anim_lgDoors_fore, 0.0, 1, &gp_doorR_rotate);
			
	}
	//
	landingGearDoorsFore = new DGa2_MovingPart(anim_lgDoors_fore, 0.5, MP_LOW_DETENT, 0.0, this);
	
	/////// control surfaces...
	
	
	UINT anim_lgDoors_aft = CreateAnimation (0.0);
	{
		static UINT gp_doorL[1] = {MGP_ID_GEARDOOR_L_INBD};
		static UINT gp_doorR[1] = {MGP_ID_GEARDOOR_R_INBD};
		//
		static MGROUP_ROTATE gp_doorL_rotate (0, gp_doorL, 1, VHINGE_GDOOR_LR_HINGE, (float)(-150.0 * RAD));
		static MGROUP_ROTATE gp_doorR_rotate (0, gp_doorR, 1, VHINGE_GDOOR_RL_HINGE, (float)(-150.0 * RAD));

		AddAnimationComponent (anim_lgDoors_aft, 0.0, 1, &gp_doorL_rotate);
		AddAnimationComponent (anim_lgDoors_aft, 0.0, 1, &gp_doorR_rotate);

	}
	//
	landingGearDoorsAft = new DGa2_MovingPart(anim_lgDoors_aft, 0.5, MP_LOW_DETENT, 0.0, this);
	
}



//
void DGa2::defineAnimationsVC ()
{
	//
	// this one's gonna be a bitch...






	//
	//


}