// Copyright (C) 2020 Jérôme Leclercq
// This file is part of the "Burgwar" project
// For conditions of distribution and use, see copyright notice in LICENSE

#include <CoreLib/Match.hpp>
#include <cassert>

namespace bw
{
	inline EntityId Match::AllocateUniqueId()
	{
		return m_nextUniqueId++;
	}

	template<typename T>
	void Match::BroadcastPacket(const T& packet, bool onlyReady, Player* except)
	{
		ForEachPlayer([&packet, onlyReady, except](Player* player)
		{
			if ((!onlyReady || player->IsReady()) && player != except)
				player->SendPacket(packet);
		});
	}

	template<typename F>
	void Match::ForEachPlayer(F&& func)
	{
		for (auto& playerPtr : m_players)
		{
			if (playerPtr)
				func(playerPtr.get());
		}
	}

	inline BurgApp& Match::GetApp()
	{
		return m_app;
	}

	inline AssetStore& Match::GetAssetStore()
	{
		assert(m_assetStore);
		return *m_assetStore;
	}

	inline const std::shared_ptr<ServerGamemode>& Match::GetGamemode()
	{
		return m_gamemode;
	}

	inline sol::state& Match::GetLuaState()
	{
		return m_scriptingContext->GetLuaState();
	}

	inline const Packets::MatchData& Match::GetMatchData() const
	{
		m_matchData.currentTick = GetNetworkTick();
		return m_matchData;
	}

	inline Player* Match::GetPlayerByIndex(Nz::UInt16 playerIndex)
	{
		if (playerIndex >= m_players.size() || m_freePlayerId.Test(playerIndex))
			return nullptr;

		Player* player = m_players[playerIndex].get();
		assert(player);

		return player;
	}

	inline MatchSessions& Match::GetSessions()
	{
		return m_sessions;
	}

	inline const MatchSessions& Match::GetSessions() const
	{
		return m_sessions;
	}

	inline const std::shared_ptr<ServerScriptingLibrary>& Match::GetScriptingLibrary() const
	{
		return m_scriptingLibrary;
	}

	inline Terrain& Match::GetTerrain()
	{
		assert(m_terrain);
		return *m_terrain;
	}

	inline const Terrain& Match::GetTerrain() const
	{
		assert(m_terrain);
		return *m_terrain;
	}
}
