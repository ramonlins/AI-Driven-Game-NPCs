// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketClient.h"
#include "Templates/SharedPointer.h"
#include "Containers/StringConv.h"
#include "Engine/NetDriver.h"

SocketClient::SocketClient()
{
    // Create a new socket based on subsystem platform, TCP (NAME_Stream)
    socketSubsytem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
    clientSocket = socketSubsytem->CreateSocket(NAME_Stream, TEXT("ClientSocket"), false);

}

SocketClient::~SocketClient()
{

}

bool SocketClient::Connect()
{
    // Convert to IPv4
    FIPv4Address address;
    FIPv4Address::Parse(ipAddress, address);
    // Store ip address in a smart pointer for safe memory management
    TSharedRef<FInternetAddr> safeAddress = socketSubsytem->CreateInternetAddr();
    // Set socket into localhost:port
    safeAddress->SetIp(address.Value);
    safeAddress->SetPort(port);

    bool isCon = clientSocket->Connect(*safeAddress);

    // Send a test message for handshake
    const FString data = "Hello";

    if (isCon){
        // Create the buffer
        TArray<uint8> SendBuffer;
        // Initializes the converter with the content of the data
        FTCHARToUTF8 Converter(*data); // Dereference to give access to TCHAR array
        // Retrieve converter pointer, cast to byte of pointers (treat as array of bytes)
        SendBuffer.Append((uint8*)Converter.Get(), Converter.Length());
        // Track how many bytes were actually sent over the socket.
        int32 BytesSent = 0;
        // Retrieve pointer, number of bytes and send over socket
        clientSocket->Send(SendBuffer.GetData(), SendBuffer.Num(), BytesSent);
    }

    //ClientSocket->Close();
    //ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(clientSocket);

    return isCon;
}
