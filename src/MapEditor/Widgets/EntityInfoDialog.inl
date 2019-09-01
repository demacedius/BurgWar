// Copyright (C) 2019 J�r�me Leclercq
// This file is part of the "Burgwar Map Editor" project
// For conditions of distribution and use, see copyright notice in LICENSE

#include <MapEditor/Widgets/EntityInfoDialog.hpp>

namespace bw
{
	const EntityInfo& EntityInfoDialog::GetInfo() const
	{
		return m_entityInfo;
	}

	inline const Nz::Vector2f& EntityInfoDialog::GetPosition() const
	{
		return m_entityInfo.position;
	}

	inline const Nz::DegreeAnglef& EntityInfoDialog::GetRotation() const
	{
		return m_entityInfo.rotation;
	}

	const Ndk::EntityHandle& EntityInfoDialog::GetTargetEntity() const
	{
		return m_targetEntity;
	}
}