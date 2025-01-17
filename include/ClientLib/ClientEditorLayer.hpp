// Copyright (C) 2020 Jérôme Leclercq
// This file is part of the "Burgwar" project
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef BURGWAR_CLIENTLIB_CLIENTEDITORLAYER_HPP
#define BURGWAR_CLIENTLIB_CLIENTEDITORLAYER_HPP

#include <CoreLib/SharedLayer.hpp>
#include <ClientLib/Export.hpp>
#include <ClientLib/VisualLayer.hpp>
#include <Nazara/Core/Bitset.hpp>
#include <Nazara/Core/Signal.hpp>

namespace bw
{
	class BURGWAR_CLIENTLIB_API ClientEditorLayer : public SharedLayer, public VisualLayer
	{
		public:
			ClientEditorLayer(SharedMatch& match, LayerIndex layerIndex);
			ClientEditorLayer(const ClientEditorLayer&) = delete;
			ClientEditorLayer(ClientEditorLayer&&) noexcept = default;
			~ClientEditorLayer() = default;

			void FrameUpdate(float elapsedTime);
			void PreFrameUpdate(float elapsedTime);
			void PostFrameUpdate(float elapsedTime);

			void TickUpdate(float elapsedTime) override;

			ClientEditorLayer& operator=(const ClientEditorLayer&) = delete;
			ClientEditorLayer& operator=(ClientEditorLayer&&) = delete;
	};
}

#include <ClientLib/ClientEditorLayer.inl>

#endif
