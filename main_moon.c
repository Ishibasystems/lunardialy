#include "moon.h"
#include <time.h>

void YMDHMS(long double jdt, long double lon)
{
	long mi, ho, dd, dm, dy;/*, k = 0;*/
	long double jdn, ds, z, f, aa, a, b, c, k, e;

	jdn = jdt + 0.5 + lon / 360;
	z = floor(jdn);
	f = jdn - z;
	aa = floor((z - 1867216.25)/36524.25);
	a = floor(z + 1 + aa - floor(aa / 4));
	b = a + 1524;
	c = floor((b - 122.1) / 365.25);
	k = floor(365.25 * c);
	e = floor((b - k) / 30.6001);

	dd = floor(b - k - floor(30.6001 * e));

	if (e < 13.5) dm = e - 1;
	else dm = e - 13;

	if (dm > 2.5) dy = c - 4716;
	else dy = c - 4715;

	ho = f * 24;
	mi = (f * 24 - ho) * 60;
	ds = ((f * 24 - ho) * 60 - mi) * 60;

	jdn = MoonPhaseGet(jdt);

	printf("%04d/%02d/%02d %02d:%02d:%06.3f ", dy, dm, dd, ho, mi, ds);
	//printf("%f ", jdn);

	if (45 < jdn && jdn < 135) printf("ãŒ·");
	else if (135 < jdn && jdn < 225) printf("–žŒŽ");
	else if (225 < jdn && jdn < 315) printf("‰ºŒ·");
	else printf("VŒŽ");

	printf(" ");

	if (45 < jdn && jdn < 315) printf("Œ»Ý‚ÌŒŽ—îF%.15f", MoonPhase(jdt));
	else printf("¡ŒŽ‚ÌñŠÔŠuF%.12f“ú", MoonPhase(jdt));

	printf(" (}50•b¸“x)\n");

	return;
}

void main()
{
	long double l, jdn;
	time_t cl;
	struct tm *to;
	int i = 0;

	time(&cl);
	to = localtime(&cl);

	l = JD(to->tm_year + 1900, to->tm_mon + 1, to->tm_mday - 1, to->tm_hour, to->tm_min, to->tm_sec, 0, 135);

	jdn = MoonPhaseGet(l);

	if (45 < jdn && jdn < 135) i = 90;
	else if (135 < jdn && jdn < 225) i = 180;
	else if (225 < jdn && jdn < 315) i = 270;

	YMDHMS(MoonPhaseNext(l, i), 135);
	ObservationPointSet(35.919084, 140.125637, 0); //ˆïéŒ§ŽæŽèŽs
	YMDHMS(MoonPhaseNext(l, i), 135);
	ObservationPointSet(35.986293, 139.374023, 0); //é‹ÊŒ§”µŽR’¬
	YMDHMS(MoonPhaseNext(l, i), 135);
	ObservationPointSet(35.958312, 139.854069, 0); //ç—tŒ§–ì“cŽs
	YMDHMS(MoonPhaseNext(l, i), 135);
	ObservationPointSet(35.729304, 139.710217, 0); //“Œ‹ž“s–L“‡‹æ
	YMDHMS(MoonPhaseNext(l, i), 135);
	exit(0);
}
