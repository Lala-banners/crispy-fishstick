#include "ActorWorld.h"

#include "Actor.h"

void ActorWorld::Spawn(Actor* _actor, Actor* _parent)
{
	AddActor(_actor, _parent == nullptr ? m_root : _parent); // spawn actor and parent, if not already parented to _parent, get root
}

void ActorWorld::SpawnWithTransform(Actor* _actor, const Vec2& _pos, float _rot, const Vec2& _scale, Actor* _parent)
{
	_actor->SetActorTransform(Mat3::CreateTransform(_pos, _rot, &_scale));
	AddActor(_actor, _parent == nullptr ? m_root : _parent);
}

void ActorWorld::Eradicate(Actor* _actor)
{
	RemoveActor(_actor);
}

ActorWorld::ActorWorld()
	: m_root{ new Actor }, m_config{ nullptr }, m_screen{ nullptr }
{
}

ActorWorld::~ActorWorld()
{
	delete m_root;
	m_root = nullptr;
}

void ActorWorld::Tick(float _dt)
{
	// iterate through every change and call the changes
	for (auto& change : m_worldChanges)
		change();

	m_worldChanges.clear();

	if (m_root)
		m_root->Tick(_dt);
}

void ActorWorld::Render()
{
	if (m_root)
		m_root->Render();
}

/// Keeping snapshot of actor and parent at runtime
/// @param _actor actor object to be created and parented to _parent
/// @param _parent parent ready to contain actor 
void ActorWorld::AddActor(Actor* _actor, Actor* _parent)
{
	// store values at certain point to use later in the function
	m_worldChanges.emplace_back([_actor, _parent, this]
		{
			// Assign config and screen
			_actor->m_config = m_config;  // has access to contents of global config
			_actor->m_screen = m_screen; // has access to contents of global screen

			// Set parent and activate list changes
			_actor->SetParent(_parent);
			_actor->ApplyListChanges();

			// Begin play
			_actor->OnBeginPlay();
		});
}

/// Go through world change list and remove actor from the world.
/// @param _actor spawned actor object
void ActorWorld::RemoveActor(Actor* _actor)
{
	m_worldChanges.emplace_back([_actor, this]
		{
			_actor->OnEndPlay();
			delete _actor;
		});
}
