// TestClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../../bcl/include/bcl.h"

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace bcl;

	SHMemPipe* pipe = new SHMemPipe;

	if(SHMemReturnValue::ret_ok != pipe->Attach(_T("test_sm_pipe")))
	{
		printf("failed to open sm pipe\n");
		return 0;
	}




	int x = -1;

	pipe->Write(&x, sizeof(int));

	DWORD tick = GetTickCount();

#define G 3000

	char buffer[G];

	int count = 10000000;

	for(int i = 0; i < count; ++i)
	{
	
		while(SHMemReturnValue::ret_buffer_overflow == pipe->Write(buffer, G))
		{
			//printf("buffer over flow\n");
			Sleep(10);
			continue;
		}

	}
	
	tick = GetTickCount() - tick;

	double dt = double(tick) / 1000.0f;
	printf("%.3f  %.3f %.3f\n", dt, float(count) / dt, (count/(1024.0 * 1024.0)) * float(G) / dt);


	x = -2;

	pipe->Write(&x, sizeof(int));

	pipe->Close();
	delete pipe;
	system("pause");
	return 0;

}

