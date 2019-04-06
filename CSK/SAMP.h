#pragma once
namespace SAMP {
	bool Init();
	void SetFunctionKey(unsigned char, unsigned char);
	void HookTable();
	void SetCharKey(unsigned char);
	void SetChar(unsigned long, unsigned char);
	void SetHandleFunctionKey(unsigned char, unsigned char);
	enum FUNCTIONID {
		SetDialogButton = 0x00,
		ESCDisableChat = 0x01,
		PageUp = 0x02,
		PageDown = 0x03,
		RecallUp = 0x04,
		RecallDown = 0x05,
		CmdRawSavePos = 0x06,
		ToggleChat = 0x07,
		CycleMode = 0x08,
		TakeScreenshoot = 0x09,
		ToggleDeathWindow = 0x0A
	};

	enum FUNC {
		HelpDialog = 0x00,
		ReturningChangeClass = 0x01,
		NetworkStats = 0x02,
		HideInterface = 0x03,
		ToggleScoreBoard = 0x04
	};
}