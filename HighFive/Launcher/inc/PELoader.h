/*
	* Copyright (C) GTA:Multiplayer Team (https://wiki.gta-mp.net/index.php/Team)
	*
	* Redistribution and use in source and binary forms, with or without
	* modification, are permitted provided that the following conditions are
	* met:
	*
	*     * Redistributions of source code must retain the above copyright
	*		notice, this list of conditions and the following disclaimer.
	*     * Redistributions in binary form must reproduce the above
	*		copyright notice, this list of conditions and the following disclaimer
	*		in the documentation and/or other materials provided with the
	*		distribution.
	*     * Neither the name of GTA-Network nor the names of its
	*		contributors may be used to endorse or promote products derived from
	*		this software without specific prior written permission.
	*
	* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
	* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
	* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
	* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
	* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
	* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES INCLUDING, BUT NOT
	* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
	* DATA, OR PROFITS; OR BUSINESS INTERRUPTION HOWEVER CAUSED AND ON ANY
	* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	* INCLUDING NEGLIGENCE OR OTHERWISE ARISING IN ANY WAY OUT OF THE USE
	* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once

class PELoader
{
public:
	void(*entryPoint)();

	uint8 * data = nullptr;

	PIMAGE_DOS_HEADER dosHeader = nullptr;
	PIMAGE_NT_HEADERS old_header = nullptr;
	PIMAGE_NT_HEADERS result_headers = nullptr;
	HMODULE m_module = nullptr;
	HMODULE(*m_libraryLoader)(const char*);
	LPVOID(*m_functionResolver)(HMODULE, const char*);
	HMODULE code = nullptr;

	auto GetHeaderDictionary(uint32 idx)
	{
		return &result_headers->OptionalHeader.DataDirectory[idx];
	}

public:
	PELoader()
	{
		SetLibraryLoader([](const char* name)
		{
			return LoadLibraryA(name);
		});

		SetFunctionResolver([](HMODULE module, const char* name)
		{
			return (LPVOID)GetProcAddress(module, name);
		});
	}
	~PELoader()
	{
		delete[] data;
	}


	void VerifyPE();
	void LoadHeaders();
	void LoadSections();
	void Relocate();
	void BuildIAT();
	void ApplyPermissions();
	void DoTLS();

	int LoadFile(const char* filename);

	inline void SetLibraryLoader(HMODULE(*loader)(const char*))
	{
		m_libraryLoader = loader;
	}

	inline void SetFunctionResolver(LPVOID(*functionResolver)(HMODULE, const char*))
	{
		m_functionResolver = functionResolver;
	}

	inline void Run()
	{
		this->entryPoint();
	}
};