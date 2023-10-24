// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketClient.h"

SocketClient::SocketClient()
{
    ISocketSubsystem* SocketSubsytem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
    // Create a new socket based on subsystem platform, TCP (NAME_Stream)
    ClientSocket = SocketSubsytem->CreateSocket(NAME_Stream, TEXT("ClientSocket"), false);
}

SocketClient::~SocketClient()
{
}
