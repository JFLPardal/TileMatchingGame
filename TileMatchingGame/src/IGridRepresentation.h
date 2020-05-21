#pragma once

/*
	IGridRepresentation defines all the functions any 
	implementation of Grid should provide
*/
class Renderer;

class IGridRepresentation
{
public:
	virtual void Draw(Renderer* renderer) = 0;
	
	virtual ~IGridRepresentation() {};
};