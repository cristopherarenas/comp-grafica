#include "sphere.h"

int pass=0;

TSphere::TSphere(float maxpos, float speed)
{
	this->maxpos = maxpos;
	if (!pass)
	{
		srandom(time(NULL));
		pass = 1;
	}
	pos[0] = (random() % (int)maxpos) - maxpos/2;
	pos[1] = (random() % (int)maxpos) - maxpos/2;
	pos[2] = (random() % (int)maxpos) - maxpos/2;
	dir[0] = random();
	dir[1] = random();
	dir[2] = random();
	float dirmod = sqrt(dir[0]*dir[0] + dir[1]*dir[1] + dir[2]*dir[2]);


	dir[0] /= dirmod;
	dir[1] /= dirmod;
	dir[2] /= dirmod;
	dir[0] *= speed;
	dir[1] *= speed;
	dir[2] *= speed;
}
void TSphere::test()
{
	((pos[0] < -maxpos) || (pos[0] > maxpos))?dir[0]*=-1:0;
	((pos[1] < -maxpos) || (pos[1] > maxpos))?dir[1]*=-1:0;
	((pos[2] < -maxpos) || (pos[2] > maxpos))?dir[2]*=-1:0;
	pos[0] += dir[0];
	pos[1] += dir[1];
	pos[2] += dir[2];
}

void TSphere::modifySpeed(float inc)
{
	float factor = (speed+inc)/speed;
	speed += inc;
	dir[0] *= factor;
	dir[1] *= factor;
	dir[2] *= factor;
}

float * TSphere::getPosv()
{
	return pos;
}
