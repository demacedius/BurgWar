// Copyright (C) 2020 Jérôme Leclercq
// This file is part of the "Burgwar" project
// For conditions of distribution and use, see copyright notice in LICENSE

#include <ClientLib/Scripting/ClientEntityLibrary.hpp>
#include <CoreLib/LayerIndex.hpp>
#include <CoreLib/LogSystem/Logger.hpp>
#include <ClientLib/ClientAssetStore.hpp>
#include <ClientLib/LocalMatch.hpp>
#include <ClientLib/Components/LocalMatchComponent.hpp>
#include <ClientLib/Components/SoundEmitterComponent.hpp>
#include <ClientLib/Components/VisibleLayerComponent.hpp>
#include <ClientLib/Components/VisualComponent.hpp>
#include <ClientLib/Components/VisualInterpolationComponent.hpp>
#include <ClientLib/Scripting/ClientScriptingLibrary.hpp>
#include <ClientLib/Scripting/Sprite.hpp>
#include <ClientLib/Scripting/Tilemap.hpp>
#include <ClientLib/Utility/TileMapData.hpp>
#include <Nazara/Graphics/Model.hpp>
#include <Nazara/Graphics/Sprite.hpp>
#include <Nazara/Graphics/TileMap.hpp>
#include <Nazara/Math/EulerAngles.hpp>
#include <NDK/Components/GraphicsComponent.hpp>
#include <NDK/Components/NodeComponent.hpp>
#include <NDK/Components/PhysicsComponent2D.hpp>

namespace bw
{
	void ClientEntityLibrary::RegisterLibrary(sol::table& elementMetatable)
	{
		SharedEntityLibrary::RegisterLibrary(elementMetatable);

		RegisterClientLibrary(elementMetatable);
	}

	void ClientEntityLibrary::InitRigidBody(lua_State* L, const Ndk::EntityHandle& entity, float mass)
	{
		SharedEntityLibrary::InitRigidBody(L, entity, mass);

		entity->GetComponent<Ndk::PhysicsComponent2D>().EnableNodeSynchronization(false);
		entity->AddComponent<VisualInterpolationComponent>();
	}

	void ClientEntityLibrary::RegisterClientLibrary(sol::table& elementMetatable)
	{
		elementMetatable["AddLayer"] = LuaFunction([](sol::this_state L, const sol::table& entityTable, const sol::table& parameters)
		{
			Ndk::EntityHandle entity = AssertScriptEntity(entityTable);

			auto& localMatch = entity->GetComponent<LocalMatchComponent>().GetLocalMatch();

			LayerIndex layerIndex = parameters["LayerIndex"];
			if (layerIndex >= localMatch.GetLayerCount())
				TriggerLuaArgError(L, 2, "layer index out of bounds");

			int renderOrder = parameters.get_or("RenderOrder", 0);
			Nz::Vector2f parallaxFactor = parameters.get_or("ParallaxFactor", Nz::Vector2f::Unit());
			Nz::Vector2f scale = parameters.get_or("Scale", Nz::Vector2f::Unit());

			if (!entity->HasComponent<VisibleLayerComponent>())
				entity->AddComponent<VisibleLayerComponent>(localMatch.GetRenderWorld());

			auto& visibleLayer = entity->GetComponent<VisibleLayerComponent>();
			visibleLayer.RegisterLocalLayer(localMatch.GetLayer(layerIndex), renderOrder, scale, parallaxFactor);
		});

		elementMetatable["AddTilemap"] = LuaFunction([this](const sol::table& entityTable, const Nz::Vector2ui& mapSize, const Nz::Vector2f& cellSize, const sol::table& content, const std::vector<TileData>& tiles, int renderOrder = 0) -> sol::optional<Tilemap>
		{
			Ndk::EntityHandle entity = AssertScriptEntity(entityTable);

			// Compute tilemap
			tsl::hopscotch_map<std::string /*materialPath*/, std::size_t /*materialIndex*/> materials;
			for (const auto& tile : tiles)
			{
				auto it = materials.find(tile.materialPath);
				if (it == materials.end())
					materials.emplace(tile.materialPath, materials.size());
			}

			if (materials.empty())
				return {};

			Nz::TileMapRef tileMap = Nz::TileMap::New(mapSize, cellSize, materials.size());
			for (auto&& [materialPath, matIndex] : materials)
			{
				Nz::MaterialRef material = Nz::Material::New(); //< FIXME
				material->SetDiffuseMap(m_assetStore.GetTexture(materialPath));

				if (material)
				{
					// Force alpha blending
					material->Configure("Translucent2D");
					material->SetDiffuseMap(m_assetStore.GetTexture(materialPath)); //< FIXME
				}
				else
					material = Nz::Material::GetDefault();

				tileMap->SetMaterial(matIndex, material);
			}

			std::size_t cellCount = content.size();
			std::size_t expectedCellCount = mapSize.x * mapSize.y;
			if (cellCount != expectedCellCount)
			{
				bwLog(GetLogger(), LogLevel::Warning, "Expected {0} cells, got {1}", expectedCellCount, cellCount);
				cellCount = std::min(cellCount, expectedCellCount);
			}

			for (std::size_t i = 0; i < cellCount; ++i)
			{
				unsigned int value = content[i + 1];

				Nz::Vector2ui tilePos = { static_cast<unsigned int>(i % mapSize.x), static_cast<unsigned int>(i / mapSize.x) };
				if (value > 0)
				{
					if (value <= tiles.size())
					{
						const auto& tileData = tiles[value - 1];

						auto matIt = materials.find(tileData.materialPath);
						assert(matIt != materials.end());

						tileMap->EnableTile(tilePos, tileData.texCoords, Nz::Color::White, matIt->second);
					}
				}
			}

			Nz::Matrix4f transformMatrix = Nz::Matrix4f::Identity();

			auto& visualComponent = entity->GetComponent<VisualComponent>();

			Tilemap scriptTilemap(visualComponent.GetLayerVisual(), std::move(tileMap), transformMatrix, renderOrder);
			scriptTilemap.Show();

			return scriptTilemap;
		});

		elementMetatable["ClearLayers"] = LuaFunction([](const sol::table& entityTable)
		{
			Ndk::EntityHandle entity = AssertScriptEntity(entityTable);

			if (entity->HasComponent<VisibleLayerComponent>())
				entity->GetComponent<VisibleLayerComponent>().Clear();
		});
	}
}
