#ifndef __IVCONVERTERHEAD__
#define __IVCONVERTERHEAD__
	#ifdef IVCONVERTER_DLL_EXPORTS
		#define  IVCONVERTER_EXPORTS __declspec(dllexport)
	#else
		#define  IVCONVERTER_EXPORTS __declspec(dllimport)
	#endif
#endif