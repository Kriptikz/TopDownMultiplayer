#include "TargetableInterface.h"


bool ITargetableInterface::IsNULL()
{
	if (GetTargetableType() == ETargetableType::TT_NULL)
	{
		return true;
	}

	return false;
}

bool ITargetableInterface::IsFloor()
{
		if (GetTargetableType() == ETargetableType::TT_Floor)
	{
		return true;
	}

	return false;
}

bool ITargetableInterface::IsAttackable()
{
	if (GetTargetableType() == ETargetableType::TT_Attackable)
	{
		return true;
	}

	return false;
}

bool ITargetableInterface::IsUsable()
{
	if (GetTargetableType() == ETargetableType::TT_Usable)
	{
		return true;
	}

	return false;
}
