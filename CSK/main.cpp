#include "main.h"
void sThread(void*)
{
	while (!SAMP::Init())
		Sleep(350);
	Sleep(500);
	InitialiseKey();
}

BOOL WINAPI DllMain(_In_ HINSTANCE , _In_ DWORD fdwReason, _In_ LPVOID)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		_beginthread(sThread, NULL, NULL);
		break;
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}
	return TRUE;
}

void InitialiseKey() {
	boost::property_tree::ptree inicfg;
	boost::property_tree::ini_parser::read_ini(".\\CSK.ini", inicfg);
	SAMP::SetFunctionKey(inicfg.get<unsigned char>("KeyActivation.DialogPressOk"), SAMP::SetDialogButton);
	SAMP::SetFunctionKey(27, SAMP::ESCDisableChat);
	SAMP::SetFunctionKey(inicfg.get<unsigned char>("KeyActivation.PageUp"), SAMP::FUNCTIONID::PageUp);
	SAMP::SetFunctionKey(inicfg.get<unsigned char>("KeyActivation.PageDown"), SAMP::FUNCTIONID::PageDown);
	SAMP::SetFunctionKey(inicfg.get<unsigned char>("KeyActivation.RecallUp"), SAMP::FUNCTIONID::RecallUp);
	SAMP::SetFunctionKey(inicfg.get<unsigned char>("KeyActivation.RecallDown"), SAMP::FUNCTIONID::RecallDown);
	SAMP::SetFunctionKey(inicfg.get<unsigned char>("KeyActivation.CmdRawPos"), SAMP::FUNCTIONID::CmdRawSavePos);
	SAMP::SetFunctionKey(inicfg.get<unsigned char>("KeyActivation.OpenChat"), SAMP::FUNCTIONID::ToggleChat);
	SAMP::SetFunctionKey(inicfg.get<unsigned char>("KeyActivation.CycleMode"), SAMP::FUNCTIONID::CycleMode);
	SAMP::SetFunctionKey(inicfg.get<unsigned char>("KeyActivation.TakeScreens"), SAMP::FUNCTIONID::TakeScreenshoot);
	SAMP::SetFunctionKey(inicfg.get<unsigned char>("KeyActivation.KillList"), SAMP::FUNCTIONID::ToggleDeathWindow);
	SAMP::SetCharKey(inicfg.get<unsigned char>("KeyActivation.TChatOpen"));
	SAMP::SetHandleFunctionKey(inicfg.get<unsigned char>("KeyActivation.HelpDialog"), SAMP::FUNC::HelpDialog);
	SAMP::SetHandleFunctionKey(inicfg.get<unsigned char>("KeyActivation.ReturnedToClass"), SAMP::FUNC::ReturningChangeClass);
	SAMP::SetHandleFunctionKey(inicfg.get<unsigned char>("KeyActivation.NetworStats"), SAMP::FUNC::NetworkStats);
	SAMP::SetHandleFunctionKey(inicfg.get<unsigned char>("KeyActivation.HideInterface"), SAMP::FUNC::HideInterface);
	SAMP::SetHandleFunctionKey(inicfg.get<unsigned char>("KeyActivation.ScoreBoard"), SAMP::FUNC::ToggleScoreBoard);
	SAMP::HookTable();
}