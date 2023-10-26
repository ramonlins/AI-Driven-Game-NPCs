// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "Containers/UnrealString.h"

/**
 *
 */
class SocketClient
{
public:
	SocketClient();
	~SocketClient();

	ISocketSubsystem* socketSubsytem;
	FSocket* clientSocket;

	bool Connect();
	void HandShake();
	//bool Send();
	//bool Receive();

	// Debug
	bool IsSocketCreated();
	bool IsSocketConnected();

private:
	// Set localhost and port
    FString ipAddress = "127.0.0.1";
	int32 port = 8888;

};
