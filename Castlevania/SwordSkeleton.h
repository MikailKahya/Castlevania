#pragma once
#include "Skeleton.h"

class Texture;

class SwordSkeleton : public Skeleton
{
public:
	SwordSkeleton();
	virtual ~SwordSkeleton();

private:
	static const Texture* SWORD_SKELETON;
};

