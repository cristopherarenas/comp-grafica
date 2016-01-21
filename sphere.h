#ifndef sphere_h
#define sphere_h
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef class TSphere
{
private:
	float maxpos;
	float pos[3];
	float dir[3];
	float speed;
public:
	TSphere(float maxpos, float speed);
	void test();
	void modifySpeed(float inc);
	float * getPosv();
} TSphere;

#endif
