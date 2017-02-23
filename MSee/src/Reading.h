#ifndef __TEAM4141_MSEE_READING__
#define __TEAM4141_MSEE_READING__

class Reading
{
private:
	bool synch;
	float angle;
	float distance;
	unsigned char quality;
	unsigned char quagrant;
	int x;
	int y;
	unsigned short color;
	unsigned short opacity;
	void calculateQuadrant();
	void calculateXY();
	void calculateColor();
public:
	Reading(bool, float, float, unsigned char);
	~Reading();
	static const float range;
	bool isSynch();
	float getAngle();
	float getDistance();
	unsigned char getQuality();
	int getX();
	int getY();
	unsigned short getColor();
	unsigned short getOpacity();
};

#endif /* __TEAM4141_MSEE_READING__ */
