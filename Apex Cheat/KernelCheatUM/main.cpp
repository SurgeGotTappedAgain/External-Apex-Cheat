#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <memory>
#include <string_view>
#include <cstdint>
#include <vector>
#include <string>
using namespace std;
HWND hWnd;

typedef struct _NULL_MEMORY
{
	void* buffer_address;
	UINT_PTR address;
	ULONGLONG size;
	ULONG pid;
	BOOLEAN write;
	BOOLEAN read;
	BOOLEAN req_base;
	void* output;
	const char* module_name;
	ULONG64 base_address;
}NULL_MEMORY;

uintptr_t base_address = 0;
std::uint32_t process_id = 0;

template<typename ... Arg>
uint64_t call_hook(const Arg ... args)
{
	void* hooked_func = GetProcAddress(LoadLibrary("win32u.dll"), "NtSetCompositionSurfaceIndependentFlipInfo"); // func hook = no bsod < 3

	auto func = static_cast<uint64_t(_stdcall*)(Arg...)>(hooked_func);

	return func(args ...);
}

struct HandleDisposer
{
	using pointer = HANDLE;
	void operator()(HANDLE handle) const
	{
		if (handle != NULL || handle != INVALID_HANDLE_VALUE)
		{
			CloseHandle(handle);
		}
	}
};

using unique_handle = std::unique_ptr<HANDLE, HandleDisposer>;

std::uint32_t get_process_id(std::string_view process_name)
{
	PROCESSENTRY32 processentry;
	const unique_handle snapshot_handle(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL));

	if (snapshot_handle.get() == INVALID_HANDLE_VALUE)
		return NULL;

	processentry.dwSize = sizeof(MODULEENTRY32);

	while (Process32Next(snapshot_handle.get(), &processentry) == TRUE)
	{
		if (process_name.compare(processentry.szExeFile) == NULL)
		{
			return processentry.th32ProcessID;
		}
	}
	return NULL;
}

static ULONG64 get_module_base_address(const char* module_name)
{
	NULL_MEMORY instructions = { 0 };
	instructions.pid = process_id;
	instructions.req_base = TRUE;
	instructions.read = FALSE;
	instructions.write = FALSE;
	instructions.module_name = module_name;
	call_hook(&instructions);
	
	ULONG64 base = NULL;
	base = instructions.base_address;
	return base;
}
template <class T>
T Read(UINT_PTR read_address)
{
	T response{};
	NULL_MEMORY instructions;
	instructions.pid = process_id;
	instructions.size = sizeof(T);
	instructions.address = read_address;
	instructions.read = TRUE;
	instructions.write = FALSE;
	instructions.req_base = FALSE;
	instructions.output = &response;
	call_hook(&instructions);

	return response;
}

bool write_memory(UINT_PTR write_address, UINT_PTR source_address, SIZE_T write_size)
{
	NULL_MEMORY instructions;
	instructions.address = write_address;
	instructions.pid = process_id;
	instructions.write = TRUE;
	instructions.read = FALSE;
	instructions.req_base = FALSE;
	instructions.buffer_address = (void*)source_address;
	instructions.size = write_size;

	call_hook(&instructions);

	return true;
}

template<typename S>
bool write(UINT_PTR write_address, const S& value)
{
	return write_memory(write_address, (UINT_PTR)&value, sizeof(S));
}


DWORD64 GetEntityById(int Ent, DWORD64 Base)
{
	DWORD64 EntityList = Base + 0x18da2a8;
	DWORD64 BaseEntity = Read<DWORD64>(EntityList);
	if (!BaseEntity) //done
		return NULL;

	return  Read<DWORD64>(EntityList + (Ent << 5));
}

void EnableHighlight(DWORD64 Entity, float r, float g, float b) {

	write<bool>(Entity + 0x3C8, true); 
	write<int>(Entity + 0x350, 1); 
	write<float>(Entity + 0x1D0, r); 
	write<float>(Entity + 0x1D4, g); 
	write<float>(Entity + 0x1D8, b); 

	for (int offset = 0x388; offset <= 0x3B4; offset += 0x4)
		write<float>(Entity + offset, FLT_MAX);

	write<float>(Entity + 0x2FC, 1000.f); // distance max
}


int main()
{
	if (hWnd == 0)
	{
		hWnd = FindWindow(NULL, "Apex Legends"); // find apex men
		cout << "[+] Found Apex" << endl; // print it ;)
	}
	else
	{
		cout << "[-] Couldn't Find Apex" << endl;
	}

	Sleep(2000);

	process_id = get_process_id("r5apex.exe"); // get pID
	base_address = get_module_base_address("r5apex.exe"); // get Mod Base Addy
	cout << process_id << endl; // print
	cout << base_address << endl;

	while (true) // lopp entities and find player and call Glow Func ;)
	{
		for (int i = 0; i < 100; i++)
		{
			DWORD64 Entity = GetEntityById(i, base_address);
			if (Entity == 0)
				continue;
			DWORD64 EntityHandle = Read<DWORD64>(Entity + 0x589);

			std::string Identifier = Read<std::string>(EntityHandle);
			LPCSTR IdentifierC = Identifier.c_str();

			if (strcmp(IdentifierC, "player"))
			EnableHighlight(Entity, 3.f, 10.f, 10.f); 
		}
	}
}