// Copyright (C) 2018 Jérôme Leclercq
// This file is part of the "Burgwar Client" project
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef BURGWAR_SHARED_SCRIPTING_SCRIPTSTORE_HPP
#define BURGWAR_SHARED_SCRIPTING_SCRIPTSTORE_HPP

#include <Shared/Scripting/ScriptedElement.hpp>
#include <Shared/Scripting/SharedScriptingContext.hpp>
#include <hopscotch/hopscotch_map.h>
#include <limits>
#include <memory>
#include <type_traits>
#include <vector>

namespace bw
{
	class Gamemode;

	template<typename Element>
	class ScriptStore
	{
		static_assert(std::is_base_of_v<ScriptedElement, Element>);

		public:
			inline ScriptStore(std::shared_ptr<Gamemode> gamemode, std::shared_ptr<SharedScriptingContext> context, bool isServer);
			virtual ~ScriptStore() = default;

			template<typename F> void ForEachElement(const F& func) const;

			inline const std::shared_ptr<Element>& GetElement(std::size_t index) const;
			inline std::size_t GetElementIndex(const std::string& name) const;

			bool Load(const std::string& folder);

			static constexpr std::size_t InvalidIndex = std::numeric_limits<std::size_t>::max();

		protected:
			virtual void InitializeElementTable(Nz::LuaState& state) = 0;
			virtual void InitializeElement(Nz::LuaState& state, Element& element) = 0;

			Nz::LuaState& GetLuaState();
			const std::shared_ptr<Gamemode>& GetGamemode();
			const std::shared_ptr<SharedScriptingContext>& GetScriptingContext();

			void SetElementTypeName(std::string typeName);
			void SetTableName(std::string tableName);

			static int GetScriptFunction(Nz::LuaState& state, const std::string& functionName);

		private:
			std::shared_ptr<Gamemode> m_gamemode;
			std::shared_ptr<SharedScriptingContext> m_context;
			std::string m_elementTypeName;
			std::string m_tableName;
			std::vector<std::shared_ptr<Element>> m_elements;
			tsl::hopscotch_map<std::string /*name*/, std::size_t /*elementIndex*/> m_elementsByName;
			bool m_isServer;
	};
}

#include <Shared/Scripting/ScriptStore.inl>

#endif