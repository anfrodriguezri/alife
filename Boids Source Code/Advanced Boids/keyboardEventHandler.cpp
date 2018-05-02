#include "keyboardEventHandler.h"
#include <iostream>

using namespace osgGA;

bool myKeyboardEventHandler::handle(const GUIEventAdapter& ea, GUIActionAdapter& aa)
{
	switch(ea.getEventType())
	{
	case(GUIEventAdapter::KEYDOWN):
		{
			switch(ea.getKey())
			{
			case 65362: //Up Arrow?
				InputDeviceState->acceleratePlayer = true;
				return false;
				break;
			case 65364:	//Down Arrow?
				InputDeviceState->decceleratePlayer = true;
				return false;
				break;
			case 65361:	//Left Arrow?
				InputDeviceState->playerTurnLeft = true;
				return false;
				break;
			case 65363:	//Right Arrow?
				InputDeviceState->playerTurnRight = true;
				return false;
				break;
			case 61:	// '=' key
				InputDeviceState->expandWallsRequest = true;
				return false;
				break;
			case 45:	// '-' key
				InputDeviceState->shrinkWallsRequest = true;
				return false;
				break;
			default:
				return false;
			} 
		}
	case(GUIEventAdapter::KEYUP):
		{
			switch(ea.getKey())
			{
				case 65362: //Up Arrow?
				InputDeviceState->acceleratePlayer = false;
				return false;
				break;
			case 65364:	//Down Arrow?
				InputDeviceState->decceleratePlayer = false;
				return false;
				break;
			case 65361:	//Left Arrow?
				InputDeviceState->playerTurnLeft = false;
				return false;
				break;
			case 65363:	//Right Arrow?
				InputDeviceState->playerTurnRight = false;
				return false;
				break;
			case 61:
				InputDeviceState->expandWallsRequest = false;
				return false;
				break;
			case 45:
				InputDeviceState->shrinkWallsRequest = false;
				return false;
				break;
			case 79 :	//'O' key pressed (only on key up so it runs once per key press)
				InputDeviceState->addObstacle = true;
				return false;
				break;
			case 111 :	//'o' key pressed (only on key up so it runs once per key press)
				InputDeviceState->addObstacle = true;
				return false;
				break;
			case 80:	// 'P' key pressed (only once)
				InputDeviceState->removeObstacles = true;
				return false;
				break;
			case 112:	// 'p' key pressed (only once)
				InputDeviceState->removeObstacles = true;
				return false;
				break;
			case 67:	// 'C' key pressed (only once)
				InputDeviceState->cleanObstacles = true;
				return false;
				break;
			case 99:	// 'c' key pressed (only once)
				InputDeviceState->cleanObstacles = true;
				return false;
				break;
			case 60:
				InputDeviceState->removeBoids = true;
				return false;
				break;
			case 62:
				InputDeviceState->addMoreBoids = true;
				return false;
				break;
			case 49:	// 1 Key pressed
				if (!InputDeviceState->alignmentMode)
					InputDeviceState->alignmentMode = true;
				else
					InputDeviceState->alignmentMode = false;
				std::cout << "Alignment toggled (0=off,1=on) : " << InputDeviceState->alignmentMode << std::endl;
				return false;
				break;
			case 50:	// 2 Key pressed
				if (!InputDeviceState->cohesionMode)
					InputDeviceState->cohesionMode = true;
				else
					InputDeviceState->cohesionMode = false;
				std::cout << "Cohesion toggled (0=off,1=on) : " << InputDeviceState->cohesionMode << std::endl;
				return false;
				break;
			case 51:	// 3 Key pressed
				if (!InputDeviceState->seperationMode)
					InputDeviceState->seperationMode = true;
				else
					InputDeviceState->seperationMode = false;
				std::cout << "Seperation toggled (0=off,1=on) : " << InputDeviceState->seperationMode << std::endl;
				return false;
				break;
			case 91:	// '[' key Pressed
				InputDeviceState->addPredator = true;
				return false;
				break;
			case 93:	// ']' key pressed
				InputDeviceState->removePredator = true;
				return false;
				break;
			case 56:
				if (!InputDeviceState->predatorSep)
					InputDeviceState->predatorSep = true;
				else
					InputDeviceState->predatorSep = false;
				std::cout << "Predators Seperation toggled (0=off,1=on) : " << InputDeviceState->predatorSep << std::endl;
				return false;
				break;
			case 57:	// '9' key pressed
				if (!InputDeviceState->predatorsHunt)
					InputDeviceState->predatorsHunt = true;
				else
					InputDeviceState->predatorsHunt = false;
				std::cout << "Predators Hunting toggled (0=off,1=on) : " << InputDeviceState->predatorsHunt << std::endl;
				return false;
				break;
			case 114:
				InputDeviceState->randomRelocate = true;
				return false;
				break;
			case 102:
				InputDeviceState->spawnFollowBoid = true;
				return false;
				break;
			default :
				break;
			}
		}
	default:
		return false;
	}
}

void myKeyboardEventHandler::accept(osgGA::GUIEventHandlerVisitor& v)
{ 
	v.visit(*this);
}