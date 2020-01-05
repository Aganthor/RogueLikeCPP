#include "Engine.h"

#include <algorithm>
#include <iostream>

#include "../Utility/Random.h"

//#include "ecs/components/asciicomponent.h"
//#include "ecs/components/transformcomponent.h"
//#include "ecs/systems/asciisystem.h"

Engine::Engine()
{
    //m_entityManager = std::make_unique<ecs::EntityManager<ComponentCount, SystemCount>>();
}

Engine::~Engine()
{
}

///////////////////////////////////////////////////////////////////////////////
// Initialize TCOD consoles; create game map and place player in the 1st room.
///////////////////////////////////////////////////////////////////////////////
void Engine::initEngine()
{
    //Initialize the random number generator.
	Random::init();

    //Initialize the renderer.
    m_Renderer.setRenderSize(MAP_WIDTH, MAP_HEIGHT);
    m_Renderer.initRenderer();

	TCODConsole::setCustomFont("res/fonts/arial10x10.png", TCOD_FONT_TYPE_GRAYSCALE | TCOD_FONT_LAYOUT_TCOD);
	TCODConsole::initRoot(SCREEN_WIDTH, SCREEN_HEIGHT, "Roguelike tutorial in C++", false, TCOD_RENDERER_OPENGL);

    m_GameMap.makeMap();
	m_GameMap.setRecomputeFov(true);

	//Place our player in the first room.
	auto [x, y] = m_GameMap.getFirstRoom().getCenter();
    createEntity(x, y, "Player", '@', TCODColor::white, false, true);
    //CreateEntityTest<Entity>

	m_IsRunning = true;
}

void Engine::setupEntityManager() {
    //m_entityManager.reserve(MAX_ENTITY);
//    m_entityManager.registerComponent<ecs::AsciiComponent>();
//    m_entityManager.createSystem<ecs::AsciiSystem>();
}

///////////////////////////////////////////////////////////////////////////////
// Called each loop to update the graphics part.
///////////////////////////////////////////////////////////////////////////////
void Engine::update(float dt)
{
    if (m_GameMap.recomputeFov())
	{
//        //TODO Will need to be updated to new ECS...
//		if (auto player = getPlayerEntity(); player)
//		{
////			m_GameMap.RecomputeFovMap(player->getXPos(), player->getYPos());
//		}
	}
    m_Renderer.renderAll(m_GameMap, m_GameMap.recomputeFov());
	m_GameMap.setRecomputeFov(false);
//	m_Renderer.ClearAll(m_Entities);
}

void Engine::handleInput()
{
    playersTurn();
    enemiesTurn();
}
///////////////////////////////////////////////////////////////////////////////
// Function that register keyboard input. FOr fullscreen and exit, we just
// set some boolean. FOr mouvement, we set up the m_InputAction tuple to
// represent what the user did.
///////////////////////////////////////////////////////////////////////////////
void Engine::registerInput()
{
	m_TCODEvent = TCODSystem::checkForEvent(TCOD_EVENT_KEY | TCOD_EVENT_MOUSE, &m_TCODKey, &m_TCODMouse);

	//Handle character mouvement
	if (m_TCODEvent == TCOD_EVENT_KEY_PRESS)
	{
		switch (m_TCODKey.vk)
		{
		case TCODK_UP:
			m_InputAction = std::make_tuple("move", 0, -1);
			break;
		case TCODK_DOWN:
			m_InputAction = std::make_tuple("move", 0, 1);
			break;
		case TCODK_LEFT:
			m_InputAction = std::make_tuple("move", -1, 0);
			break;
		case TCODK_RIGHT:
			m_InputAction = std::make_tuple("move", 1, 0);
			break;
		}
		switch (m_TCODKey.c)
		{
		case 'y':
			m_InputAction = std::make_tuple("move", -1, -1);
			break;
		case 'u':
			m_InputAction = std::make_tuple("move", 1, -1);
			break;
		case 'b':
			m_InputAction = std::make_tuple("move", -1, 1);
			break;
		case 'n':
			m_InputAction = std::make_tuple("move", 1, 1);
			break;
		}

		//Check for Escape key or fullscreen sequence
        if (m_TCODKey.vk == TCODK_ESCAPE) {
			m_IsRunning = false;
		}
        if (m_TCODKey.vk == TCODK_ENTER && m_TCODKey.lalt) {
			m_FullScreen = !m_FullScreen;
			TCODConsole::setFullscreen(m_FullScreen);
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Helper function to determine if an entity is present at location x and y.
///////////////////////////////////////////////////////////////////////////////
bool Engine::entityPresentAt(int x, int y)
{
//	auto entity_present = std::find_if(m_Entities.begin(), m_Entities.end(), [x, y](const auto &entity)
//	{
//        //TODO Will need to be updated to new ECS...
//		return entity->getXPos() == x && entity->getYPos() == y;
//	});

//	if (entity_present != std::end(m_Entities))
		return true;
//	else
//		return false;
}

///////////////////////////////////////////////////////////////////////////////
// Helper function to create a new entity for the game.
///////////////////////////////////////////////////////////////////////////////
void Engine::createEntity(int x, int y, const std::string& name, char display,
                          TCODColor color, bool block, bool isPlayer)
{
    if (isPlayer)
    {
        //auto player = m_entityManager.createEntity();
        //m_entityManager.addComponent<ecs::AsciiComponent>(player, display, color);
        //m_entityManager.addComponent<ecs::TransformComponent>(player, x, y);
    }
    else
    {
  //      m_Entities.emplace_back(std::make_unique<ecs::Entity>(x, y, name, display, color, block));
    }
}

///////////////////////////////////////////////////////////////////////////////
// Takes care of handling the input registered in RegisterInput.
///////////////////////////////////////////////////////////////////////////////
void Engine::playersTurn()
{
	auto [action, dx, dy] = m_InputAction;

    setGameState(GameState::PLAYERS_TURN);

	if ((action == "move") && (m_GameState == GameState::PLAYERS_TURN))
	{
//		if (auto player = getPlayerEntity(); player)
//		{
//            //TODO Will need to be updated to new ECS...
////			auto destination_x = player->getXPos() + dx;
////			auto destination_y = player->getYPos() + dy;

//			//Check to see if we can move...
////			if (!m_GameMap.isBlocked(destination_x, destination_y))
////			{
////				if (auto target = getBlockingEntityAtLocation(destination_x, destination_y); target)
////				{
////					std::cout << "You kick the crap out of " << target->getName() << ", much to it's annoyance!\n";
////				}
////				else
////				{
////                    //TODO Will need to be updated to new ECS...
////					player->Move(dx, dy);
////					m_GameMap.setRecomputeFov(true);
////				}
////				setGameState(GameState::ENEMIES_TURN);
////			}
//		}
		//Reset the InputAction to nothing.
		m_InputAction = std::make_tuple("", 0, 0);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Loops through all the entities and allowing them to take a turn.
///////////////////////////////////////////////////////////////////////////////
void Engine::enemiesTurn()
{
//	for (auto &entity : m_Entities)
//	{
//        //TODO Will need to be updated to new ECS...
////		if (entity->getName() != "Player")
////		{
////            std::cout << "The " << entity->getName() << " ponders the meaning of its existence.\n";
////		}
//	}

	setGameState(GameState::PLAYERS_TURN);
}

