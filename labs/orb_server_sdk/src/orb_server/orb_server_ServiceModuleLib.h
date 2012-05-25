#pragma once

namespace orb
{
	class ServiceModuleLib
	{
	public:
		ServiceModuleLib(void);
		virtual ~ServiceModuleLib(void);

		//bool										Load(boost::filesystem::wpath

	private:
		kernel_object								m_lib;

		std::wstring								m_libname;
	};

}