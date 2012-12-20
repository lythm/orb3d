#pragma once

#include "MeshImporter.h"

class MeshImporter_3DSMax : public MeshImporter
{
public:
	MeshImporter_3DSMax(void);
	virtual ~MeshImporter_3DSMax(void);

	bool								Import(const wchar_t* szFile);
};

