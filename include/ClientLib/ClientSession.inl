// Copyright (C) 2019 Jérôme Leclercq
// This file is part of the "Burgwar" project
// For conditions of distribution and use, see copyright notice in LICENSE

#include <ClientLib/ClientSession.hpp>
#include <Nazara/Network/NetPacket.hpp>

namespace bw
{
	inline ClientSession::ClientSession(BurgApp& application, const LocalCommandStore& commandStore, MatchFactory matchFactory) :
	m_application(application),
	m_commandStore(commandStore),
	m_matchFactory(std::move(matchFactory))
	{
	}

	inline BurgApp& ClientSession::GetApp()
	{
		return m_application;
	}

	inline const BurgApp& ClientSession::GetApp() const
	{
		return m_application;
	}

	inline const ClientSession::ConnectionInfo& ClientSession::GetConnectionInfo() const
	{
		return m_connectionInfo;
	}

	inline const NetworkStringStore& ClientSession::GetNetworkStringStore() const
	{
		return m_stringStore;
	}

	inline bool ClientSession::IsConnected() const
	{
		return m_bridge && m_bridge->IsConnected();
	}

	template<typename T>
	void ClientSession::SendPacket(const T& packet)
	{
		if (!IsConnected())
			return;

		Nz::NetPacket data;
		m_commandStore.SerializePacket(data, packet);

		const auto& command = m_commandStore.GetOutgoingCommand<T>();
		m_bridge->SendPacket(command.channelId, command.flags, std::move(data));
	}

	inline void ClientSession::UpdateInfo(const ConnectionInfo& connectionInfo)
	{
		OnConnectionInfoUpdate(this, connectionInfo);
		m_connectionInfo = connectionInfo;
	}
}