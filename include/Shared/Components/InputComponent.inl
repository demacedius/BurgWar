// Copyright (C) 2018 Jérôme Leclercq
// This file is part of the "Erewhon Server" project
// For conditions of distribution and use, see copyright notice in LICENSE

#include <Shared/Components/InputComponent.hpp>

namespace bw
{
	inline InputComponent::InputComponent(const InputData& inputData) :
	m_inputData(inputData)
	{
	}

	inline InputComponent::InputComponent(const InputComponent& inputComponent) :
	m_inputData(inputComponent.m_inputData)
	{
	}

	inline const InputData& InputComponent::GetInputData() const
	{
		return m_inputData;
	}

	inline void InputComponent::UpdateInputs(const InputData& inputData)
	{
		m_inputData = std::move(inputData);

		OnInputUpdate(this);
	}
}
