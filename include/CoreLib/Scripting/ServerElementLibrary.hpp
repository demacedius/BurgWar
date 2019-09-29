// Copyright (C) 2019 Jérôme Leclercq
// This file is part of the "Burgwar" project
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef BURGWAR_CORELIB_SCRIPTING_SERVERELEMENTLIBRARY_HPP
#define BURGWAR_CORELIB_SCRIPTING_SERVERELEMENTLIBRARY_HPP

#include <CoreLib/Scripting/SharedElementLibrary.hpp>

namespace bw
{
	class ServerElementLibrary : public SharedElementLibrary
	{
		public:
			ServerElementLibrary() = default;
			~ServerElementLibrary() = default;

			void RegisterLibrary(sol::table& elementMetatable) override;

		private:
			void RegisterServerLibrary(sol::table& elementTable);
	};
}

#include <CoreLib/Scripting/ServerElementLibrary.inl>

#endif