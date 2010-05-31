#include "DGa2.h"
#include "detours.h"


HINSTANCE thisDLL;








DLLCLBK void InitModule(HINSTANCE mod)
{
	thisDLL = mod;
	//
	//
	
	
	//
	
}

DLLCLBK void ExitModule(HINSTANCE mod)
{
	//
}









DLLCLBK VESSEL* ovcInit(OBJHANDLE vsl_hndl, int fltModel)
{

	return new DGa2(vsl_hndl, fltModel);
} 

DLLCLBK void ovcExit(VESSEL* vsl)
{
	if (vsl) 
		delete (DGa2*) vsl;
}







void hookOpenInputBox(char *title, bool (*Clbk)(void*,char*,void*), char *buf = 0, int vislen = 20, void *usrdata = 0)
{
	OUT "INPUT :: " << title ENT;
	
	
	char inputEntry[128];
	cin.getline(inputEntry, 128);
	
	OUT " <enter> " ENT
	//
	//
	if (!(*Clbk)(title, inputEntry, usrdata))
	{
		OUT "does not compute...\n" ENT
	}
}



void (__stdcall* inputBoxFn)(char *title, bool (*Clbk)(void*,char*,void*), char *buf, int vislen, void *usrdata);
void (__stdcall* inputCelBodyFn)(char *title, bool (*Clbk)(void*,char*,void*), char *buf, int vislen, void *usrdata);
void (__stdcall* inputTargetFn)(char *title, bool (*Clbk)(void*,char*,void*), char *buf, int vislen, void *usrdata);
//

void DGa2::setInputHook ()
{
	//
	//
	OUT "hooking MFD inputs... (or trying to)" ENT
	
	//
	OUT "address for inputBox function should be: " << &oapiOpenInputBox ENT
	inputBoxFn = (void (__stdcall*)(char *title, bool (*Clbk)(void*,char*,void*), char *buf, int vislen, void *usrdata))DetourFunction((PBYTE)&oapiOpenInputBox, (PBYTE)hookOpenInputBox);
	inputCelBodyFn = (void (__stdcall*)(char *title, bool (*Clbk)(void*,char*,void*), char *buf, int vislen, void *usrdata))DetourFunction((PBYTE)0x00431050, (PBYTE)hookOpenInputBox);
	inputTargetFn  = (void (__stdcall*)(char *title, bool (*Clbk)(void*,char*,void*), char *buf, int vislen, void *usrdata))DetourFunction((PBYTE)0x00431190, (PBYTE)hookOpenInputBox);
	
	//
	OUT "hook should be set now...\n\n" ENT
	
}