#include "StdAfx.h"
#include "MeshImporter_3DSMax.h"


MeshImporter_3DSMax::MeshImporter_3DSMax(void)
{
}


MeshImporter_3DSMax::~MeshImporter_3DSMax(void)
{
}
bool MeshImporter_3DSMax::Import(const wchar_t* szFile)
{

	/*IStorage * pStorage = nullptr;

	HRESULT ret = StgOpenStorageEx(szFile, STGM_READ, STGFMT_FILE, FILE_ATTRIBUTE_NORMAL, nullptr, 0, IID_IStorage,(void**) &pStorage);


	FILE* file = _wfopen(szFile, L"rb+");

	if(file == nullptr)
	{
		return false;
	}
	

	fclose(file);*/
	return true;
}