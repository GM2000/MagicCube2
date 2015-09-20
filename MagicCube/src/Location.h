#pragma once

//location
class loc
{
private:
	float X;
	float Y;
	float Z;

	float Facing[2];

	//get Player's position int
	int inline _GetPlayerXi()
	{
		if (X < 0)
		{
			return (int)X - 1;
		}
		else {
			return (int)X;
		}
	}
	int inline _GetPlayerYi()
	{
		if (Y < 0)
		{
			return (int)Y - 1;
		}
		else {
			return (int)Y;
		}
	}
	int inline _GetPlayerZi()
	{
		if (Z < 0)
		{
			return (int)Z - 1;
		}
		else {
			return (int)Z;
		}
	}

public:
	loc()
	{
		X = 0;
		Y = 0;
		Z = 0;
	}
	void inline MoveTo(float MX, float MY, float MZ)
	{
		X += MX;
		Y += MY;
		Z += MZ;
	}
	float inline GetX()
	{
		return X;
	}
	float inline GetY()
	{
		return Y;
	}
	float inline GetZ()
	{
		return Z;
	}

};
