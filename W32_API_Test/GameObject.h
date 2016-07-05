#pragma once


class GameObject
{
public:

	GameObject(){}
	virtual ~GameObject(){}

	virtual void Reset() = 0;
};

