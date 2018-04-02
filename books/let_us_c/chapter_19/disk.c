#include <windows.h>
#include <stdio.h>
#include <conio.h>

#pragma pack(1)
struct boot
{
	BYTE jump[3];
	char bsOemName[8];
	WORD bytesperSector;
	BYTE sectorspercluster;
	WORD sectorsreservedarea;
	BYTE copiesFAT;
	WORD maxrootdirenties;
	WORD totalSectors;
	BYTE mediaDesctiptor;
	WORD sectorsperFAT;
	WORD sectorsperTrack;
	WORD sides;
	WORD hiddenSectors;
	char reserve[480];
};

void ReadSector(char *src, int ss, int num, void* buff);

int main()
{
	struct boot b;
	ReadSector("\\\\.\\A:", 0, 1, &b);

	printf("Boot Sector name:    %s\n", b.bsOemName);
	printf("Bytes per Sector:    %d\n", b.bytesperSector);
	printf("Sectors per Cluster: %d\n", b.sectorspercluster);
	
	return(0);
}

void
ReadSector(char *src, int ss, int num, void* buff)
{
	HANDLE h;
	unsigned int br;
	h = CreateFile(src, GENERIC_READ,
				   FILE_SHARE_READ, 0,
				   OPEN_EXISTING, 0, 0);
	SetFilePointer(h, (ss * 512), NULL, FILE_BEGIN);
	ReadFile(h, buff, 512 * num, &br, NULL);
	CloseHandle(h);
}

void
WriteSector(char *src, int ss, int num, void* buff)
{
	HANDLE h;
	unsigned int br;
	h = CreateFile(src, GENERIC_WRITE,
				   FILE_SHARE_READ, 0,
				   OPEN_EXISTING, 0, 0);
	SetFilePointer(h, (ss * 512), NULL, FILE_BEGIN);
	WriteFile(h, buff, 512 * num, &br, NULL);
	CloseHandle(h);
}
