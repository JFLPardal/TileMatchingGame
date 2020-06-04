#pragma once
#include "Constants.h"
/*
	QueueOfNextPairs encapsulates the representation 
	and implementation of how 'PairOfPieces' are shown
	on the screen as the next pairs to be spawned
*/

class PairOfPieces;
class ColumnAvailability;
class Renderer;

class QueueOfNextPairs
{
public:
	QueueOfNextPairs(const ColumnAvailability* const columnAvailability);
	
	void Draw(Renderer* renderer) const;
	
	std::unique_ptr<PairOfPieces> GetPairToBeSpawned(const ColumnAvailability* const columnAvailabiliry);
private:
	std::array<std::unique_ptr<PairOfPieces>, Consts::NUM_PAIRS_TO_SHOW> m_nextPairs;
	const ColumnAvailability* const m_columnAvailability;
};