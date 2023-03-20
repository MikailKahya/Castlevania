#pragma once
#include "Skeleton.h"
class Texture;

class RangedSkeleton : public Skeleton
{
public:
	RangedSkeleton();
	virtual ~RangedSkeleton();

private:
	static const Texture* RANGED_SKELETON;
};

