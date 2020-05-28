
/*
	Group is responsible for partially encapsulating 
	the implementation of a Group
*/
class Vector2;

class Group
{
public:
	Group(std::set<Vector2>& positionsAsGridIndexes);
	
	void PlayDestructionAnimation();
	const std::set<Vector2>& GetPiecePositions();
private:
	std::set<Vector2> m_GridPositions;
};