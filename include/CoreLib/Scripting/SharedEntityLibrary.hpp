// Copyright (C) 2019 Jérôme Leclercq
// This file is part of the "Burgwar" project
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef BURGWAR_CORELIB_SCRIPTING_SHAREDENTITYLIBRARY_HPP
#define BURGWAR_CORELIB_SCRIPTING_SHAREDENTITYLIBRARY_HPP

#include <CoreLib/Scripting/AbstractElementLibrary.hpp>

namespace bw
{
	class SharedEntityLibrary : public AbstractElementLibrary
	{
		public:
			SharedEntityLibrary() = default;
			~SharedEntityLibrary() = default;

			void RegisterLibrary(sol::table& elementMetatable) override;

		private:
			void RegisterSharedLibrary(sol::table& elementMetatable);
	};
}

#include <CoreLib/Scripting/SharedEntityLibrary.inl>

#endif