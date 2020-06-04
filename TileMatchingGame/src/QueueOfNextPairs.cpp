#include "pch.h"
#include "QueueOfNextPairs.h"

#include "ColumnAvailability.h"
#include "PairOfPieces.h"
#include "Wrappers/Renderer.h"

QueueOfNextPairs::QueueOfNextPairs(const ColumnAvailability* const aColumnAvailability)
	:m_columnAvailability(aColumnAvailability)
{
	for (auto& nextPair : m_nextPairs)
	{
		nextPair = std::make_unique<PairOfPieces>(aColumnAvailability);
	}
}

void QueueOfNextPairs::Draw(Renderer* aRenderer) const
{
	for (auto& nextPair : m_nextPairs)
	{
		if (nextPair != nullptr) nextPair->Draw(aRenderer);
	}
}

std::unique_ptr<PairOfPieces> QueueOfNextPairs::GetPairToBeSpawned(const ColumnAvailability* const aColumnAvailability)
{
	std::unique_ptr<PairOfPieces> nextPairToBeSpawned = std::move(m_nextPairs.at(0));
	for (size_t i = 0; i < m_nextPairs.size() - 1; i++)
	{
		m_nextPairs.at(i) = std::move(m_nextPairs.at(i + 1));
	}
	m_nextPairs.at(m_nextPairs.size() - 1) = std::make_unique<PairOfPieces>(aColumnAvailability);
	return nextPairToBeSpawned;
}
