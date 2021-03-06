#ifndef NETMESSAGES_H
#define NETMESSAGES_H

enum ENetworkMessage
{
	// server
	eServerBegin = 0,
	eServerConnectionDenied = eServerBegin + 1,
	eServerSendInfo = eServerBegin + 2,
	eServerClientAuthed = eServerBegin + 3,
	eServerPingRequest = eServerBegin + 4,
	eServerClientKicked = eServerBegin + 5,
	eServerYourItemWas = eServerBegin + 6,

	// client
	eClientBegin = 1000,
	eClientInitConnection = eClientBegin + 1,
	eClientAuth = eClientBegin + 2,
	eClientPingReply = eClientBegin + 3,
	eClientItemGranted = eClientBegin + 4,

	eWORD = 0xFFFFFF,

};

enum EConnectionDenyReason
{
	EDenyServerFull,
	EDenyAuthFailed,
	EDenySteamIDBanned,
	EDenySteamIDExists,

	eBYTE = 0xFF,
};


struct NetMessageBase_t
{
	NetMessageBase_t(ENetworkMessage mt) : messageType(mt) {};

	const ENetworkMessage messageType;
};

struct NetServerConnectionDenied_t : NetMessageBase_t
{
	NetServerConnectionDenied_t() : NetMessageBase_t( eServerConnectionDenied ) { }

	EConnectionDenyReason denyReason;
};

#pragma pack(push, 1)
struct NetServerSendInfo_t : NetMessageBase_t
{
	NetServerSendInfo_t() : NetMessageBase_t( eServerSendInfo) {}

	CSteamID serverSteamID;
	bool vacSecure;
};
#pragma pack(pop)

struct NetServerClientAuthed_t : NetMessageBase_t
{
	NetServerClientAuthed_t() : NetMessageBase_t( eServerClientAuthed ) { }

	char messageOfTheDay[ MOTD_SIZE ];
	// maybe send other last details to an authed client?
};

struct NetServerPingRequest_t : NetMessageBase_t
{
	NetServerPingRequest_t() : NetMessageBase_t( eServerPingRequest ) { }

	uint32 itemsTotal;
};

struct NetServerClientKicked_t : NetMessageBase_t
{
	NetServerClientKicked_t() : NetMessageBase_t( eServerClientKicked ) { }

	char kickMessage[256];
};

struct NetServerYourItemWas_t : NetMessageBase_t
{
	NetServerYourItemWas_t() : NetMessageBase_t( eServerYourItemWas ) { };

	char itemName[ITEM_MAXNAMELEN];
};

struct NetClientInitConnection_t : NetMessageBase_t
{
	NetClientInitConnection_t() : NetMessageBase_t( eClientInitConnection ) { }

};

struct NetClientAuth_t : NetMessageBase_t
{
	NetClientAuth_t() : NetMessageBase_t( eClientAuth ) { }

	// uint64 clientSteamID; // probably located in the auth ticket
	uint32 ticketLen;
	byte authTicket[ AUTHTICKET_SIZE ];
	char username[ 32 ];
};

struct NetClientPingReply_t : NetMessageBase_t
{
	NetClientPingReply_t() : NetMessageBase_t( eClientPingReply ) { }


};

struct NetClientItemGranted_t : NetMessageBase_t
{
	NetClientItemGranted_t() : NetMessageBase_t( eClientItemGranted ) { }

	uint32 itemid;
};

#endif // NETMESSAGES_H
