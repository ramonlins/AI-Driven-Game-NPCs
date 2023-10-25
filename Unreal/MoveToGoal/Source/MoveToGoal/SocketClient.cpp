// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketClient.h"
#include "Templates/SharedPointer.h"
#include "Containers/StringConv.h"
#include "Engine/NetDriver.h"

SocketClient::SocketClient()
{
    socketSubsytem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
    // Create a new socket based on subsystem platform, TCP (NAME_Stream)
    clientSocket = socketSubsytem->CreateSocket(NAME_Stream, TEXT("ClientSocket"), false);

}

SocketClient::~SocketClient()
{

}

bool SocketClient::Connect()
{
    // Set localhost and port
    ipAddress = "127.0.0.1";
    port = 8888;

    // Convert to IPv4
    FIPv4Address address;
    FIPv4Address::Parse(ipAddress, address);
    // Store ip address in a smart pointer for safe memory management
    TSharedRef<FInternetAddr> shareAddress = socketSubsytem->CreateInternetAddr();
    // Set socket into localhost:port
    shareAddress->SetIp(address.Value);
    shareAddress->SetPort(port);

    return clientSocket->Connect(*shareAddress);
}
