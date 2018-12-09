// Copyright (C) 2018 J�r�me Leclercq
// This file is part of the "Burgwar Shared" project
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#ifndef BURGWAR_CLIENTAPP_HPP
#define BURGWAR_CLIENTAPP_HPP

#include <Shared/BurgApp.hpp>
#include <Shared/NetworkReactor.hpp>
#include <Shared/MatchSessions.hpp>
#include <Shared/Protocol/Packets.hpp>
#include <Client/LocalCommandStore.hpp>
#include <Nazara/Graphics/Sprite.hpp>
#include <Nazara/Math/Angle.hpp>
#include <Nazara/Network/IpAddress.hpp>
#include <Nazara/Renderer/RenderWindow.hpp>
#include <NDK/Application.hpp>
#include <NDK/Entity.hpp>
#include <NDK/World.hpp>
#include <vector>

namespace bw
{
	class LocalMatch;
	class Match;
	class NetworkClientBridge;
	class NetworkReactor;

	class ClientApp : public Ndk::Application, public BurgApp
	{
		friend class ClientSession;

		public:
			ClientApp(int argc, char* argv[]);
			~ClientApp();

			inline std::size_t AddReactor(std::unique_ptr<NetworkReactor> reactor);
			inline void ClearReactors();

			inline const LocalCommandStore& GetCommandStore() const;
			inline Nz::RenderWindow& GetMainWindow() const;
			inline const std::unique_ptr<NetworkReactor>& GetReactor(std::size_t reactorId);
			inline std::size_t GetReactorCount() const;

			int Run();

		private:
			std::shared_ptr<LocalMatch> CreateLocalMatch(ClientSession& session, const Packets::MatchData& matchData);
			std::shared_ptr<NetworkClientBridge> ConnectNewServer(const Nz::IpAddress& serverAddress, Nz::UInt32 data);

			void HandlePeerConnection(bool outgoing, std::size_t peerId, Nz::UInt32 data);
			void HandlePeerDisconnection(std::size_t peerId, Nz::UInt32 data);
			void HandlePeerInfo(std::size_t peerId, const NetworkReactor::PeerInfo& peerInfo);
			void HandlePeerPacket(std::size_t peerId, Nz::NetPacket& packet);

			std::vector<std::shared_ptr<LocalMatch>> m_localMatches;
			std::vector<std::unique_ptr<NetworkReactor>> m_reactors;
			std::vector<std::shared_ptr<NetworkClientBridge>> m_connections;
			LocalCommandStore m_commandStore;
			std::unique_ptr<Match> m_match;
			std::unique_ptr<ClientSession> m_clientSession;
			Nz::RenderWindow& m_mainWindow;
#if 0
			Ndk::EntityHandle m_camera;
			Ndk::EntityHandle m_burger;
			Ndk::EntityHandle m_weapon;
			Ndk::World& m_world;
			Nz::DegreeAnglef m_attackOriginAngle;
			Nz::SpriteRef m_burgerSprite;
			Nz::SpriteRef m_weaponSprite;
			bool m_isAttacking;
			bool m_isTargetingRight;
			bool m_isFacingRight;
			bool m_isOnGround;
			bool m_isMoving;
			float m_attackTimer;
#endif
	};
}

#include <Client/ClientApp.inl>

#endif