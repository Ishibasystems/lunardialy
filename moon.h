
#ifndef __MOON_H__

	#define __MOON_H__

	#ifndef _USE_MATH_DEFINES
		#define _USE_MATH_DEFINES
	#endif

	#include <math.h>

	#ifndef M_PI
		#define M_PI 3.1415926535897932384626433832795L
	#endif

	#ifndef fmodl
		#define fmodl fmod
	#endif

	#define rad2deg(d) ((long double)d) * 180 / M_PI
	#define deg2rad(d) ((long double)d) * M_PI / 180
	#define sind(d) sinl(deg2rad(d))
	#define cosd(d) cosl(deg2rad(d))
	#define tand(d) tanl(deg2rad(d))
	#define asind(d) rad2deg(asinl(d))
	#define acosd(d) rad2deg(acosl(d))
	#define atand(d) rad2deg(atanl(d))

	long double fmod360(long double);
	void ObservationPointSet(long double, long double, long double);
	long double JD(long, char, char, char, char, char, short, long double)
	long double dT(long double);
	long double MoonPhaseGet(long double);
	long double MoonPhasePrevious(long double, long double);
	long double MoonPhaseNext(long double, long double);
	long double MoonPhase(long double);

#endif
