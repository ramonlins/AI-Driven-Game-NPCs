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
	FString ipAddress;
	int32 port;

	bool Connect();

};
