#include "DGa2.h"
#include "DGa2_DVC.h"

#include "MFDlib.h"



inline void txtFltData(HDC& hDC, int x, int y, string st, double& val, char prcsn=2, char dgts=3)
{
	
	ostringstream strm;
	
	//
	if (abs(val) < 1000)
		strm << st << fixed << setprecision(prcsn) << val;	
	else if (abs(val) < 1000000)
		strm << st << fixed << setprecision(prcsn) << (val/1000) << TEXT("K");
	else
		strm << st << fixed << setprecision(prcsn) << (val/1000000) << TEXT("M");
	
	st = strm.str();
	TextOut(hDC, x,y, st.c_str(), st.length());
	
}


// here's we drawaringz the HUD....
//
void DGa2::clbkDrawHUD (int mode, const HUDPAINTSPEC *hps, HDC hDC)
{
	// draw the default HUD
	VESSEL2::clbkDrawHUD (mode, hps, hDC);
	
	
	//
	VESSEL *vsl = oapiGetFocusInterface();
	ELEMENTS   elms;

	double mjdref = oapiGetSimMJD();
	vsl->GetElements(elms,  mjdref);
	
	double surfRds = oapiGetSize(vsl->GetSurfaceRef());
	
	

	// show gear deployment status
	if (landingGears->mp_status != MP_LOW_DETENT) {
		int d = hps->Markersize/2;
		int cx = hps->CX, cy = hps->CY;
		
		if (landingGears->mp_status != MP_HI_DETENT)
		{
			
			TextOut (hDC,cx-15, cy-40, TEXT("GEAR"),4);
			TextOut (hDC,cx-20, cy-25, TEXT("UNSAFE"),6);
			
		} else
		{
			Rectangle (hDC, cx-d/2, cy-d*5, cx+d/2, cy-d*4);
			Rectangle (hDC, cx-d*3, cy-d*2, cx-d*2, cy-d);
			Rectangle (hDC, cx+d*2, cy-d*2, cx+d*3, cy-d);
		}		
	}
	
	double fltData;
	
	
	if (oapiCockpitMode() == COCKPIT_VIRTUAL) {
	
		
		switch(mode)
		{
		case HUD_SURFACE:
		
			fltData = vsl->GetMachNumber();  txtFltData (hDC, 5,50, TEXT("MACH "), fltData);
			fltData = vsl->GetDynPressure(); txtFltData (hDC, 5,60, TEXT("DynP "), fltData);
			fltData = vsl->GetAtmPressure(); txtFltData (hDC, hps->W - 68,50, TEXT("StaP "), fltData);
			
			fltData = vsl->GetSlipAngle() * DEG;  txtFltData (hDC, hps->W - 100, hps->H - 30, TEXT("SLIP  "), fltData);
			fltData = vsl->GetAOA() * DEG;        txtFltData (hDC, hps->W - 100, hps->H - 40, TEXT("AoA  "),  fltData);
			
			TextOut (hDC,0,hps->H - 25, TEXT("MAIN | INT"),10);
			break;
			
		case HUD_DOCKING:
			TextOut (hDC,hps->W-60,10, TEXT("::CLSD::"),8);
			
			
			
			break;	
			
		case HUD_ORBIT:
			vsl->GetApDist(fltData); fltData-=surfRds;    txtFltData (hDC,5,20, TEXT("ApA "),fltData);			
			vsl->GetPeDist(fltData); fltData-=surfRds;    txtFltData (hDC,5,30, TEXT("PeA "),fltData);

			txtFltData (hDC, 5,40, TEXT("Ecc "), elms.e);			
			txtFltData (hDC, 5,50, TEXT("SmA "), elms.a);
			
			txtFltData (hDC,(hps->W)- 80, 30, TEXT("Inc "), elms.i);
			txtFltData (hDC,(hps->W)- 80, 40, TEXT("LAN "), elms.theta);
			
			break;
			
		}
	
		
		
		if(vsl->GetNavmodeState (NAVMODE_KILLROT))
			TextOut(hDC, hps->W-150, hps->H-13, TEXT("|   KILLROT   |"), 15);

		if(vsl->GetNavmodeState (NAVMODE_PROGRADE))
			TextOut(hDC, hps->W-150, hps->H-13, TEXT("|   PROGRDE   |"), 15);

		if(vsl->GetNavmodeState (NAVMODE_RETROGRADE))
			TextOut(hDC, hps->W-150, hps->H-13, TEXT("|   RETROGD   |"), 15);

		if(vsl->GetNavmodeState (NAVMODE_NORMAL))
			TextOut(hDC, hps->W-150, hps->H-13, TEXT("|   NORMAL+   |"), 15);

		if(vsl->GetNavmodeState (NAVMODE_ANTINORMAL))
			TextOut(hDC, hps->W-150, hps->H-13, TEXT("|   NORMAL-   |"), 15);

		if(vsl->GetNavmodeState (NAVMODE_HLEVEL))
			TextOut(hDC, hps->W-150, hps->H-13, TEXT("|   WINGLVL   |"), 15);

		if(vsl->GetNavmodeState (NAVMODE_HOLDALT))
			TextOut(hDC, hps->W-150, hps->H-13, TEXT("|   HOLDALT   |"), 15);
		
		
		
		// show RCS mode
		switch (GetAttitudeMode()) {
		case RCS_ROT:
			TextOut (hDC, 0, hps->H-13, TEXT("RCS ROT"), 7);
			break;
		case RCS_LIN:
			TextOut (hDC, 0, hps->H-13, TEXT("RCS LIN"), 7);
			break;
		}
	}
}


extern VCGDI sysmfd_GDI;
//

bool DGa2::clbkVCRedrawEvent (int id, int ev, SURFHANDLE surf)
{
	
	
	HDC hDC = oapiGetDC(surf);
	HFONT restoreFont;
	
	
	if (id & DVC_SYSMFD)
	{
		SelectObject (hDC, sysmfd_GDI.nullPen);
		SelectObject (hDC, sysmfd_GDI.bkgdBrush);

		Rectangle (hDC, 0,0, 256,256);



		SetTextColor (hDC, RGB(255,220,0)); 
		SetBkColor (hDC, RGB(0,0,0));

		restoreFont = (HFONT)SelectObject (hDC, sysmfd_GDI.fontSmall);
	}
	
	
	
		
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	if(id == DVC_SYSMFD_1)
	{
		
		SYSMFD_TXTCLR(RGB(0,0,0), RGB(255,210,0));
		//
		TextOut(hDC, 150,85,  TEXT(" MAIN | INT "), 12);
		
		SYSMFD_TXTCLR(RGB(255,210,0), RGB(0,0,0));
		//
		TextOut(hDC, 150,100, TEXT("RD OPEN"), 7);
		TextOut(hDC, 150,110, TEXT("FS OPEN"), 7);
		
		
		SetTextColor (hDC, RGB(0,255,0));
		
		TextOut(hDC, 150,10, TEXT("Ram Temp: 0000°C"), 16);
		TextOut(hDC, 150,20, TEXT("Ram Pres:   000%"), 16);
		TextOut(hDC, 150,30, TEXT("R1 Temp : 0000°C"), 16);
		TextOut(hDC, 150,40, TEXT("R2 Temp : 0000°C"), 16);
		TextOut(hDC, 150,50, TEXT(" Ram Eff :  000%"), 16);
		
		//
		
		
		TextOut(hDC, 10,10,  TEXT("Exh Temp: 0000°C"), 16);
		TextOut(hDC, 10,20,  TEXT("Exh Pres:   000%"), 16);
		TextOut(hDC, 10,30,  TEXT("Cmpr RPM:   000%"), 16);
		TextOut(hDC, 10,40,  TEXT("Inlt Flw:   000%"), 16);
		TextOut(hDC, 10,50,  TEXT("Inlt Tmp: 0000°C"), 16);
		TextOut(hDC, 10,60,  TEXT("Eff Rtng:   100%"), 16);
		
		TextOut(hDC, 15, 80,  TEXT("APU  [OffLine]"), 14);
		TextOut(hDC, 15, 90,  TEXT("APU Fuel: 100%"), 14);
		TextOut(hDC, 15, 100, TEXT("APU RPM : 000%"), 14);
		TextOut(hDC, 15, 110, TEXT("APU Vltg: 000V"), 14);
		
		
		double mainfuel = GetFuelMass ();
		txtFltData (hDC, 20, 150, TEXT("Fuel Main:  "), mainfuel);
		//
		double fuelPct = (mainfuel / GetMaxFuelMass()) * 100;
		txtFltData (hDC, 20, 160, TEXT("Fuel Pct:   "), fuelPct);
		//
		
		double fuelFlow = GetPropellantFlowrate (main_fuel_res);
		txtFltData (hDC, 20, 170, TEXT("Fuel Flw:   "), fuelFlow);
		
		
		
		
		double fuelRcs = GetPropellantMass (rcs_fuel_res);
		txtFltData (hDC, 150,150, TEXT("RCS qty: "), fuelRcs);
		
		double fuelRcsFlow = GetPropellantFlowrate (rcs_fuel_res);
		txtFltData (hDC, 150,160, TEXT("RCS ffl: "), fuelRcsFlow);
		
		
		switch (GetAttitudeMode()) {
			case RCS_ROT:
				SYSMFD_TXTCLR(RGB(0,0,0), RGB(0,255,0));
				TextOut (hDC, 150, 175, TEXT(" RCS ROT "), 9);
				break;
			case RCS_LIN:
				SYSMFD_TXTCLR(RGB(0,0,0), RGB(0,255,0));
				TextOut (hDC, 150, 175, TEXT(" RCS LIN "), 9);
				break;
			default:
				SYSMFD_TXTCLR(RGB(0,0,0), RGB(255,0,0));
				TextOut (hDC, 150, 175, TEXT(" RCS OFF "), 9);
		}
		
		//
		//
		SelectObject (hDC, sysmfd_GDI.whitePen);
		MoveToEx (hDC, 10, 140, NULL);
		LineTo (hDC, 246, 140);
		
		MoveToEx (hDC, 10, 75, NULL);
		LineTo (hDC, 120,  75);
		
		
		
		
		//
		//
		
		
		SYSMFD_TXTCLR(RGB(0,0,0), RGB(0,255,0));
		//
		TextOut(hDC, 5, 190,   TEXT("| OVR |"), 7);
		
		SYSMFD_TXTCLR(RGB(255,255,255), RGB(0,0,0));
		
		TextOut(hDC, 55, 190,  TEXT("| ENG |"), 7);
		TextOut(hDC, 105, 190, TEXT("| RMC |"), 7);
		TextOut(hDC, 155, 190, TEXT("| APU |"), 7);
		TextOut(hDC, 205, 190, TEXT("| FLS |"), 7);
		
		
		SelectObject(hDC, restoreFont);
		//
		oapiReleaseDC (surf, hDC);
		return true;
	
	
	}
	
	
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	
	
	if(id == DVC_SYSMFD_2)
	{
	
	
		SYSMFD_TXTCLR(RGB(0,0,0), RGB(255,210,0));
		TextOut(hDC, 110, 10,  TEXT(" VISOR DOWN "), 12);
		//
		switch (landingGears->mp_status)
		{
			case MP_LOW_DETENT:
				TextOut(hDC, 185, 10,  TEXT("  GEAR UP  "), 11);
				break;
				
			case MP_HI_DETENT:
				TextOut(hDC, 185, 10,  TEXT(" GEAR DOWN "), 11);
				break;
				
				
			case MP_MOVING:
			case MP_REVERSING:
				SYSMFD_TXTCLR(RGB(255,255,255), RGB(255,0,0));
				TextOut(hDC, 185, 10,  TEXT(" GEAR UNSF "), 11);
				break;
		}
		
		
		
		
		int trimY = 20 + (GetTrimScale() * 100.0);

		SelectObject(hDC, sysmfd_GDI.greenPen);
		for (int tickY = 20; tickY <= 120; tickY += 10)
		{
			MoveToEx (hDC, 5, tickY, NULL);
			LineTo (hDC, 10, tickY);
		}
		//
		SelectObject(hDC, sysmfd_GDI.whitePen);
		MoveToEx(hDC, 12, trimY, NULL);
		LineTo (hDC, 20, trimY);
		
		
		
		// G's
		//
		SYSMFD_TXTCLR(RGB(0,255,0), RGB(0,0,0));
		TextOut(hDC, 10, 130,   TEXT("Gs:"), 3);
		//
		static double Gfwd, Gver, Glat, m;
		VECTOR3 vF, vW;
		//
		GetForceVector(vF);
		GetWeightVector(vW);
		m = oapiGetMass(GetHandle());
		//
		//Catch missing data bug
		if(m > 0)
		{
			VECTOR3 vA;
			vA = (vF-vW)/m;
			
			Gver = vA.y / 9.81;
			Gfwd = vA.z / 9.81;
			Glat = vA.x / 9.81;
			
			txtFltData (hDC, 15, 140, TEXT("VER: "), Gver);
			txtFltData (hDC, 15, 150, TEXT("FWD: "), Gfwd);
			txtFltData (hDC, 15, 160, TEXT("LAT: "), Glat);
		}
		
		
		
		
		SYSMFD_TXTCLR(RGB(0,0,0), RGB(0,255,0));
		//
		TextOut(hDC, 5, 190,   TEXT("| FLT |"), 7);

		SYSMFD_TXTCLR(RGB(255,255,255), RGB(0,0,0));

		TextOut(hDC, 55,  190, TEXT("| NAV |"), 7);
		TextOut(hDC, 105, 190, TEXT("| INS |"), 7);
		TextOut(hDC, 155, 190, TEXT("| VEC |"), 7);
		TextOut(hDC, 205, 190, TEXT("| STA |"), 7);
		
		//
		//
		//
		
		
		SYSMFD_TXTCLR(RGB(0,0,0), RGB(0,255,0));
		//
		TextOut(hDC, 15, 205,   TEXT(" [  MAN  ] "), 11);
		
		SYSMFD_TXTCLR(RGB(255,0,0), RGB(0,0,0));
		TextOut(hDC, 15, 225,   TEXT("  SAS OFF  "), 11);
		
		
		SYSMFD_TXTCLR(RGB(255,0,0), RGB(0,0,0));
		TextOut(hDC, 15, 235,   TEXT("  ATR OFF  "), 11);
		
	
	
		SelectObject(hDC, restoreFont);
		//
		oapiReleaseDC (surf, hDC);
		return true;
	
	
	}
	
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	
	
	
	if(id == DVC_SYSMFD_3)
	{
	
	
		SYSMFD_TXTCLR(RGB(0,0,0), RGB(255,210,0));
		TextOut(hDC, 100, 100,  TEXT(" OFFLINE "),9);
		
	
		SelectObject(hDC, restoreFont);
		//
		oapiReleaseDC (surf, hDC);
		return true;
	
	}

	
	
	//
	return false;	
} 