#include "pch.h"
#include "Group.h"

#include "Vector2.h"

Group::Group(std::set<Vector2>& positions)
{
	m_GridPositions = positions;
}

void Group::PlayDestructionAnimation()
{
	printf("playing destruction\n");
}

const std::set<Vector2>& Group::GetPiecePositions()
{
	return m_GridPositions;
}
