#include "FileManaging.h"

FileManaging::STATUS FileManaging::LoadFileToString(std::string path, std::string& bufor)
{
	LPSTR Bufor;
	DWORD dwRozmiar, dwPrzeczyt;
	HANDLE hPlik;

	hPlik = CreateFile(path.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hPlik == INVALID_HANDLE_VALUE) {
		return STATUS::CANNOT_OPEN;
	}

	dwRozmiar = GetFileSize(hPlik, NULL);
	if (dwRozmiar == 0xFFFFFFFF) {
		return STATUS::TOO_BIG;
	}

	Bufor = (LPSTR)GlobalAlloc(GPTR, dwRozmiar + 1);

	if (!ReadFile(hPlik, Bufor, dwRozmiar, &dwPrzeczyt, NULL)) {
		return STATUS::CANNOT_READ;
	}

	Bufor[dwRozmiar] = 0; // dodaj zero na końcu stringa
	
	bufor = Bufor;

	GlobalFree(Bufor); // Zwolnij bufor
	CloseHandle(hPlik); // Zamknij plik
}

FileManaging::STATUS FileManaging::SaveStringToFile(std::string path, std::string& toSave)
{
	LPSTR Bufor;
	DWORD dwRozmiar, dwZapisane;
	HANDLE hPlik;

	std::cout << "Checkpoint1" << std::endl;

	hPlik = CreateFile(path.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	if (hPlik == INVALID_HANDLE_VALUE) {
		return STATUS::CANNOT_OPEN;
	}

	dwRozmiar = toSave.length();
	if (dwRozmiar == 0) {
		return STATUS::TOO_BIG;
	}

	Bufor = (LPSTR)GlobalAlloc(GPTR, dwRozmiar + 1);


	Bufor = const_cast<char*>(toSave.c_str());

	Bufor[dwRozmiar] = 0; // dodaj zero na końcu stringa

	if (!WriteFile(hPlik, Bufor, dwRozmiar, &dwZapisane, NULL)) {
		return STATUS::CANNOT_WRITE;
	}

	//GlobalFree(Bufor); // Zwolnij bufor

	CloseHandle(hPlik); // Zamknij plik

}
