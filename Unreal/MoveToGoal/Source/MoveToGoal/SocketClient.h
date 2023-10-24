// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sockets.h"
#include "SocketSubsystem.h"

/**
 *
 */
class SocketClient
{
public:
	SocketClient();
	~SocketClient();

	// TODO: Implement connection to python server, send data, receive data and disconnect;
	FSocket* ClientSocket;

};
