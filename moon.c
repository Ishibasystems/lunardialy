#include "moon.h"

static long double d0 = 0;
static long double LAT;
static long double RLT = 0;
static long double longitude;

long double fmod360(long double d)
{
	d = fmodl(d, 360);
	if (d < 0) d += 360;
	return d;
}

void ObservationPointSet(long double NS,long double EW,long double ro)
{
			if (NS <  -90) NS =  -90;
			if (NS >   90) NS =  -90;
			if (EW < -180) EW = -180;
			if (EW >  180) EW =  180;

			longitude = EW;
			LAT = NS - 0.19241666667 * sind(NS * 2);	/* 天文緯度 */
			RLT = ((0.998327112 + 0.001676399 * cosd(NS * 2) - 0.000003519 * cosd(NS * 4)) * 6378140 + ro) / 6371012;
			if (RLT < 0) RLT = 0;
			return;
}

long double JD(long y2,char m2,char d,char h,char min,char s,short ms,long double lon)
{
	long y = y2;
	char m = m2 - 2;

	if (m < 1){
		m += 12;
		y--;
	}
	d0 = (((0.001L * ms + s) / 60 + min) / 60 + h) * 15;
	return 2400000.5 + (long)(365.25 * y) + (y / 400) - (y / 100) + (long)(30.59 * m) + d - 678912 + ((((0.001L * ms + s) / 60 + min) / 60 + h - lon / 15) / 24);
}

long double dT(long double jdt)
{
	long double T = ((jdt - 2451544.53) / 365.2422 + 2000) * 360;
	return 64.0732 + 0.0007 * (jdt - 2451862.5) + 0.022 * sind(T) - 0.012 * cosd(T) - 0.006 * sind(T * 2) + 0.007 * cosd(T * 2);
}

long double MoonPhaseGet(long double jdt)
{
	/* DUMMY */
	/* まず「天文年鑑」もしくは海上保安庁「天体位置表」を入手して頂きます。 */
	/* 地心黄経、地心黄経・黄緯を計算して月齢を求める処理がここに入ります。 */

	return 0.0;
}

long double Squeeze(long double di, long double phase)
{
	long double z = 1.0, d0 = di;
	short cnt;

	phase = fmod360(phase);

	for(cnt = 0; cnt < 500; cnt++)
	{
		d0 -= z;
		if (fmod360(MoonPhaseGet(d0) - phase) > 180){
			d0 += z;
			z /= 2;
		}
	}
	return d0;
}

long double Squeeze2(long double di, long double phase)
{
	long double z = 1.0, d0 = di;
	short cnt;

	phase = fmod360(phase);

	for(cnt = 0; cnt < 500; cnt++)
	{
		d0 += z;
		if (fmod360(MoonPhaseGet(d0) - phase) < 180){
			d0 -= z;
			z /= 2;
		}
	}
	return d0;
}

long double MoonPhasePrevious(long double jdt, long double phase)
{
	return Squeeze(jdt - 29.6 * fmod360(MoonPhaseGet(jdt) - phase) / 360 + 1, phase);
}

long double MoonPhaseNext(long double jdt, long double phase)
{
	return Squeeze(jdt - 29.6 * fmod360(MoonPhaseGet(jdt) - phase) / 360 + 30, phase);
}

long double MoonPhase(long double jdt)
{
	static long double d1, d2;

	if (jdt > d2){
		d1 = d2;
		if (d1 == 0) d1 = MoonPhasePrevious(jdt, 0);
		d2 = Squeeze(d1 + 30, 0);
	}
	return jdt - d1;
}
