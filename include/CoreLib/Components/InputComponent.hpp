// Copyright (C) 2019 Jérôme Leclercq
// This file is part of the "Burgwar" project
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef BURGWAR_CORELIB_COMPONENTS_INPUTCOMPONENT_HPP
#define BURGWAR_CORELIB_COMPONENTS_INPUTCOMPONENT_HPP

#include <Nazara/Core/Signal.hpp>
#include <NDK/Components.hpp>
#include <CoreLib/InputData.hpp>

namespace bw
{
	class InputComponent : public Ndk::Component<InputComponent>
	{
		public:
			InputComponent() = default;
			inline InputComponent(const InputData& inputData);
			inline InputComponent(const InputComponent& inputComponent);

			inline const InputData& GetInputs() const;

			inline void UpdateInputs(const InputData& inputData);

			static Ndk::ComponentIndex componentIndex;

			NazaraSignal(OnInputUpdate, InputComponent* /*input*/);

		private:
			InputData m_inputData;
	};
}

#include <CoreLib/Components/InputComponent.inl>

#endif
