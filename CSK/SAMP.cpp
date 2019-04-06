#include "main.h"

namespace SAMP {
	unsigned long Addr = NULL;
	unsigned char itfss[223];
	unsigned long AddrFunc[5] = { 0x713E0, 0x797E, 0x71369, 0x713A9 , 0x5DC7F };
	bool Init()
	{
		Addr = (unsigned long)GetModuleHandle(L"samp.dll");
		if (Addr == 0)
			return false;
		for (int i = 0; i <= 223; i++) //заполняем таблицу 0x0B ибо он ведет на case default
		{
			itfss[i] = 0x0B;			
		}
		return true;
	}
	
	void SetFunctionKey(_In_ unsigned char Key,_In_ unsigned char val)
	{
		itfss[Key] = val;
	}
	


	template<typename T>
	void SetMemory(_In_ void* addr, _In_ unsigned long val)
	{
		unsigned long oldprot;
		VirtualProtect(addr, sizeof(T), PAGE_EXECUTE_READWRITE, &oldprot);
		//*(T *)addr = (T)val;
		*reinterpret_cast<T *>(addr) = (T)val;
		VirtualProtect(addr, sizeof(T), oldprot, NULL);
	}

	void SetCharKey(_In_ unsigned char toggle)
	{
		if (!toggle) {
			SetChar(0x5DB04, NULL);
			SetChar(0x5DAFA, NULL);
		}
	}

	inline void SetChar(_In_ unsigned long addr, _In_ unsigned char characte)
	{
		SetMemory<unsigned char>((void*)(Addr + addr), characte);
	}

	void HookTable()
	{
		SetMemory<unsigned long>((void*)(Addr + 0x5D863), (unsigned long)&itfss); //меняем таблицу на свою
		SetMemory<unsigned char>((void*)(Addr + 0x5D859), 0xDF);			 //номер максимального элемента таблицы
		SetMemory<unsigned char>((void*)(Addr + 0x5D856), 0x00);			 //номер минимального элемента таблицы
	}

	void SetHandleFunctionKey(_In_ unsigned char key, _In_ unsigned char id) 
	{
		SetMemory<unsigned char>((void*)(Addr + AddrFunc[id]), key);
	}
}