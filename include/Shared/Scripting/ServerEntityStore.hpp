// Copyright (C) 2018 Jérôme Leclercq
// This file is part of the "Burgwar Shared" project
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef BURGWAR_SHARED_SCRIPTING_SERVERENTITYSTORE_HPP
#define BURGWAR_SHARED_SCRIPTING_SERVERENTITYSTORE_HPP

#include <Shared/Scripting/ScriptedEntity.hpp>
#include <Shared/Scripting/SharedEntityStore.hpp>
#include <NDK/Entity.hpp>
#include <NDK/World.hpp>

namespace bw
{
	class ServerEntityStore : public SharedEntityStore
	{
		public:
			inline ServerEntityStore(std::shared_ptr<Gamemode> gamemode, std::shared_ptr<SharedScriptingContext> context);
			~ServerEntityStore() = default;

			const Ndk::EntityHandle& InstantiateEntity(Ndk::World& world, std::size_t entityIndex);

		private:
			void InitializeElementTable(Nz::LuaState& state) override;
			void InitializeElement(Nz::LuaState& state, ScriptedEntity& element) override;
	};
}

#include <Shared/Scripting/ServerEntityStore.inl>

#endif