#include "ProcMem.h"

#define FL_ONGROUND (1 << 0)

struct sOffsets {
	DWORD dwFlags = 0x100;
	DWORD dwLocalPlayer = 0x00AA5834;
	DWORD dwForceJump = 0x04F5EB58;
}Offsets;

ProcMem Mem;

int main() {
	Mem.Process("csgo.exe");
	DWORD dwClientDLL = Mem.Module("client.dll");


	while (true) {
		DWORD dwLocalBase = Mem.Read<DWORD>(Offsets.dwLocalPlayer + dwClientDLL);
		BYTE dwFlags = Mem.Read<DWORD>(dwLocalBase + Offsets.dwFlags);

		if (dwFlags & FL_ONGROUND && GetAsyncKeyState(VK_SPACE)) {
			Mem.Write<DWORD>(dwClientDLL + Offsets.dwForceJump, 6);
		}
	}


	return 0;
}