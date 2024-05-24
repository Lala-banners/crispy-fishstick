#include "Actor.h"

Actor::Actor()
	: m_parent{ nullptr }, m_transform{ Mat3::Identity() }, m_config{ nullptr }, m_screen{ nullptr }
{
}

Actor::~Actor()
{
	for (const auto& child : m_children)
		delete child;

	m_children.clear();
	m_parent = nullptr;
}

Vec2 Actor::GetActorPosition() const
{
	return GlobalTransform().GetTranslation();
}

float Actor::GetActorRotation() const
{
	return GlobalTransform().GetRotationX() * RAD2DEG;
}

Vec2 Actor::GetActorScale() const
{
	return GlobalTransform().GetScale();
}

void Actor::SetActorPosition(const Vec2& _pos)
{
	m_transform.SetTranslation(_pos);
}

void Actor::SetActorRotation(float _rot)
{
	m_transform.SetRotationZ(_rot * DEG2RAD);
}

void Actor::SetActorScale(const Vec2& _scale)
{
	m_transform.SetScale(_scale);
}

void Actor::SetActorTransform(const Mat3& _transform)
{
	m_transform = _transform;
}

void Actor::UpdateActorTransform(const Mat3& _transform)
{
	m_transform = _transform * m_transform;
}

#pragma region Virtual Voids to be overriden by child classes
void Actor::OnBeginPlay() { }

void Actor::OnTick(float _dt) { }

void Actor::OnRender() { }

void Actor::OnEndPlay() { }
#pragma endregion

Actor* Actor::Parent() const
{
	return m_parent;
}

void Actor::SetParent(Actor* _newParent)
{
	if (_newParent == nullptr)
	{
		if (m_parent)
			m_parent->RemoveChild(this);
	}
	else
	{
		_newParent->AddChild(this);
	}
}

Mat3& Actor::Transform()
{
	return m_transform;
}

// Travel up chain of command to multiply the matrices together.
Mat3 Actor::GlobalTransform() const
{
	return m_parent != nullptr ? m_transform * m_parent->GlobalTransform() : m_transform;
}

Config* Actor::GetConfig() const
{
	return m_config;
}

Screen* Actor::GetScreen() const
{
	return m_screen;
}

void Actor::ApplyListChanges()
{
	// go through every change and trigger change function
	for (auto& change : m_childListChanges)
		change();

	m_childListChanges.clear();
}

void Actor::Tick(float _dt)
{
	OnTick(_dt);

	ApplyListChanges();

	// Apply generational trauma XD
	for (const auto& child : m_children)
		child->Tick(_dt);
}

void Actor::Render()
{
	OnRender();

	for (const auto& child : m_children)
		child->Render();
}

/// If the child has a parent, orphan the child. Give child new parent
/// @param _child batman the child
void Actor::AddChild(Actor* _child)
{
	m_childListChanges.emplace_back([_child, this]
		{
			if (_child->m_parent)
				_child->m_parent->RemoveChild(_child);

			_child->m_parent = this;
			m_children.emplace_back(_child);
		});
}

/// Remove child from parent if already assigned a parent and remove from the list of children.
/// @param _child orphaned child.
void Actor::RemoveChild(Actor* _child)
{
	m_childListChanges.emplace_back([_child, this]
		{
			if (_child->m_parent == this)
			{
				_child->m_parent = nullptr;
				m_children.remove(_child);
			}
		});
}