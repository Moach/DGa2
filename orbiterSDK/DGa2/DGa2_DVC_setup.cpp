#include "DGa2.h"
#include "DGa2_DVC.h"

//


bool DGa2::clbkLoadVC (int id)
{	
	OUT "Delta-Starliner G42 :: Start DVC setup!" ENT;

	//
	SetCameraOffset (V3_VC_EYEPOINT);
	SetCameraDefaultDirection (_V(0,0,1));
	SetCameraRotationRange (RAD*120, RAD*120, RAD*70, RAD*70);
	SetCameraShiftRange (_V(0,0,0.1), _V(-0.2,0,0), _V(0.2,0,0));
	
	
	static VCHUDSPEC huds = {1, MGP_ID_HUD, _V(-0.0, 1.529, 24.9465), 0.2};
	oapiVCRegisterHUD (&huds); // HUD parameters
	
	
	static VCMFDSPEC mfds_left = {1,MGP_ID_MFD_L};
	static VCMFDSPEC mfds_rite = {1,MGP_ID_MFD_R};
	static VCMFDSPEC mfds_cent = {1,MGP_ID_MFD_C};
	oapiVCRegisterMFD (MFD_LEFT,  &mfds_left);
	oapiVCRegisterMFD (MFD_RIGHT, &mfds_rite);
	oapiVCRegisterMFD (MFD_USER1, &mfds_cent);
	
	oapiOpenMFD(MFD_MAP,     MFD_LEFT);
	oapiOpenMFD(MFD_SURFACE, MFD_RIGHT);
	oapiOpenMFD(MFD_ORBIT,   MFD_USER1);
	
	
	//
	SURFHANDLE mfdb_ll_sh = oapiGetTextureHandle (mdl_dvc, 1);
	//

	// left mfd buttons
	{


		//
		oapiVCRegisterArea (DVC_AREA_MFDL_BTNL1, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDL_BTNL1, V3_DVC_BTN_MFDL001, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDL_BTNL2, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDL_BTNL2, V3_DVC_BTN_MFDL002, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDL_BTNL3, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDL_BTNL3, V3_DVC_BTN_MFDL003, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDL_BTNL4, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDL_BTNL4, V3_DVC_BTN_MFDL004, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDL_BTNL5, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDL_BTNL5, V3_DVC_BTN_MFDL005, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDL_BTNL6, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDL_BTNL6, V3_DVC_BTN_MFDL006, .01);
		//
		//
		oapiVCRegisterArea (DVC_AREA_MFDL_BTNR1, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDL_BTNR1, V3_DVC_BTN_MFDL007, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDL_BTNR2, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDL_BTNR2, V3_DVC_BTN_MFDL008, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDL_BTNR3, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDL_BTNR3, V3_DVC_BTN_MFDL009, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDL_BTNR4, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDL_BTNR4, V3_DVC_BTN_MFDL010, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDL_BTNR5, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDL_BTNR5, V3_DVC_BTN_MFDL011, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDL_BTNR6, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDL_BTNR6, V3_DVC_BTN_MFDL012, .01);
	} 
	// center mfd buttons
	{

		// center mfd buttons
		//
		oapiVCRegisterArea (DVC_AREA_MFDC_BTNL1, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDC_BTNL1, V3_DVC_BTN_MFDC001, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDC_BTNL2, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDC_BTNL2, V3_DVC_BTN_MFDC002, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDC_BTNL3, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDC_BTNL3, V3_DVC_BTN_MFDC003, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDC_BTNL4, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDC_BTNL4, V3_DVC_BTN_MFDC004, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDC_BTNL5, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDC_BTNL5, V3_DVC_BTN_MFDC005, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDC_BTNL6, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDC_BTNL6, V3_DVC_BTN_MFDC006, .01);
		//
		//
		oapiVCRegisterArea (DVC_AREA_MFDC_BTNR1, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDC_BTNR1, V3_DVC_BTN_MFDC007, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDC_BTNR2, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDC_BTNR2, V3_DVC_BTN_MFDC008, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDC_BTNR3, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDC_BTNR3, V3_DVC_BTN_MFDC009, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDC_BTNR4, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDC_BTNR4, V3_DVC_BTN_MFDC010, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDC_BTNR5, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDC_BTNR5, V3_DVC_BTN_MFDC011, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDC_BTNR6, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDC_BTNR6, V3_DVC_BTN_MFDC012, .01);
	}	
	// right mfd buttons
	{

		
		//
		oapiVCRegisterArea (DVC_AREA_MFDR_BTNL1, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDR_BTNL1, V3_DVC_BTN_MFDR001, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDR_BTNL2, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDR_BTNL2, V3_DVC_BTN_MFDR002, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDR_BTNL3, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDR_BTNL3, V3_DVC_BTN_MFDR003, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDR_BTNL4, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDR_BTNL4, V3_DVC_BTN_MFDR004, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDR_BTNL5, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDR_BTNL5, V3_DVC_BTN_MFDR005, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDR_BTNL6, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDR_BTNL6, V3_DVC_BTN_MFDR006, .01);
		//
		//
		oapiVCRegisterArea (DVC_AREA_MFDR_BTNR1, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDR_BTNR1, V3_DVC_BTN_MFDR007, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDR_BTNR2, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDR_BTNR2, V3_DVC_BTN_MFDR008, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDR_BTNR3, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDR_BTNR3, V3_DVC_BTN_MFDR009, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDR_BTNR4, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDR_BTNR4, V3_DVC_BTN_MFDR010, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDR_BTNR5, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDR_BTNR5, V3_DVC_BTN_MFDR011, .01);
		//
		oapiVCRegisterArea (DVC_AREA_MFDR_BTNR6, _R(0,0,27,85), PANEL_REDRAW_USER, PANEL_MOUSE_LBDOWN, PANEL_MAP_BACKGROUND, mfdb_ll_sh);
		oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDR_BTNR6, V3_DVC_BTN_MFDR012, .01);

	}



	oapiVCRegisterArea (DVC_AREA_MFDL_SEL, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN|PANEL_MOUSE_ONREPLAY);
	oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDL_SEL, V3_DVC_BTN_MFDL_SEL, .02);
	//
	oapiVCRegisterArea (DVC_AREA_MFDL_INFO, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN|PANEL_MOUSE_ONREPLAY);
	oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDL_INFO, V3_DVC_BTN_MFDL_INFO, .01);

	oapiVCRegisterArea (DVC_AREA_MFDC_SEL, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN|PANEL_MOUSE_ONREPLAY);
	oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDC_SEL, V3_DVC_BTN_MFDC_SEL, .02);
	//
	oapiVCRegisterArea (DVC_AREA_MFDC_INFO, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN|PANEL_MOUSE_ONREPLAY);
	oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDC_INFO, V3_DVC_BTN_MFDC_INFO, .01);

	oapiVCRegisterArea (DVC_AREA_MFDR_SEL, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN|PANEL_MOUSE_ONREPLAY);
	oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDR_SEL, V3_DVC_BTN_MFDR_SEL, .02);
	//
	oapiVCRegisterArea (DVC_AREA_MFDR_INFO, PANEL_REDRAW_NEVER, PANEL_MOUSE_LBDOWN|PANEL_MOUSE_ONREPLAY);
	oapiVCSetAreaClickmode_Spherical(DVC_AREA_MFDR_INFO, V3_DVC_BTN_MFDR_INFO, .01);


	// 
	//
	
	
	SURFHANDLE sysmfd_t1;
	//
	sysmfd_t1 = oapiGetTextureHandle(mdl_dvc, 5);
	oapiVCRegisterArea(DVC_SYSMFD_1, _R(0,0,256,256), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, sysmfd_t1);
	
	SURFHANDLE sysmfd_t2;
	//
	sysmfd_t2 = oapiGetTextureHandle(mdl_dvc, 6);
	oapiVCRegisterArea(DVC_SYSMFD_2, _R(0,0,256,256), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, sysmfd_t2);
	
	SURFHANDLE sysmfd_t3;
	//
	sysmfd_t3 = oapiGetTextureHandle(mdl_dvc, 7);
	oapiVCRegisterArea(DVC_SYSMFD_3, _R(0,0,256,256), PANEL_REDRAW_ALWAYS, PANEL_MOUSE_IGNORE, PANEL_MAP_NONE, sysmfd_t3);
	


	//
	OUT "Delta-Starliner G42 :: Done DVC setup!" ENT;
	return true;
}


VCGDI sysmfd_GDI; // here's where we put our GDI crap :)

void DGa2::SetupVCGDI()
{

	OUT " -- GDI Start" ENT;

	HDC hDC = GetDC (NULL);
	
	sysmfd_GDI.bkgdBrush = CreateSolidBrush (RGB(0,0,0));
	sysmfd_GDI.nullPen = CreatePen (PS_NULL, 0, RGB(0,0,0));
	
	sysmfd_GDI.greenBrush = CreateSolidBrush (RGB(0,255,0));
	sysmfd_GDI.greenPen   = CreatePen (PS_SOLID, 1, RGB(0,255,0));
	
	sysmfd_GDI.redBrush = CreateSolidBrush (RGB(255,0,0));
	sysmfd_GDI.redPen   = CreatePen (PS_SOLID, 1, RGB(255,0,0));
	
	sysmfd_GDI.yellowBrush = CreateSolidBrush (RGB(255,210,0));
	sysmfd_GDI.yellowPen   = CreatePen (PS_SOLID, 1, RGB(255,210,0));
	
	sysmfd_GDI.whiteBrush = CreateSolidBrush (RGB(255,255,255));
	sysmfd_GDI.whitePen   = CreatePen (PS_SOLID, 1, RGB(255,255,255));
	
	
	//
	long fontH10 = MulDiv(10, GetDeviceCaps (hDC, LOGPIXELSY), 72);
	//
	sysmfd_GDI.fontSmall = CreateFont(fontH10, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Courier New"));
	
	ReleaseDC (NULL, hDC);
	
	OUT " -- GDI ready" ENT;
}
