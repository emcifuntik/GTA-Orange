#pragma once
class UserLibrary
{
private:
	std::vector<uint8_t> m_libraryBuffer;
public:
	UserLibrary(const wchar_t* fileName);
	const uint8_t* GetExportCode(const char* name) const;
	const uint8_t* GetOffsetPointer(uint32_t offset) const;
};