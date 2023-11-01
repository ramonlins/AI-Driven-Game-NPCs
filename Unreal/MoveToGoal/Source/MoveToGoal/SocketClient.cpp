// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketClient.h"
#include "Templates/SharedPointer.h"
#include "Containers/StringConv.h"
#include "Engine/NetDriver.h"
#include "SocketTypes.h"

SocketClient::SocketClient()
{
    // Create a new socket based on subsystem platform, TCP (NAME_Stream)
    socketSubsytem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);
    clientSocket = socketSubsytem->CreateSocket(NAME_Stream, TEXT("ClientSocket"), false);

    // Here you can check the socket creation and print messages
    if (IsSocketCreated()) {
        UE_LOG(LogTemp, Warning, TEXT("Client Socket was created successfully!!!"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Client Socket creation failed!!!"));
    }

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

    // Here you can check the socket connection
    if (IsSocketConnected()) {
        UE_LOG(LogTemp, Warning, TEXT("Client Socket was connected successfully!!!"));
		HandShake();
	} else {
        UE_LOG(LogTemp, Warning, TEXT("Client Socket connection failed!!!"));
    }

    return isCon;
}

void SocketClient::HandShake()
{
    // Send a test message for handshake
    const FString data = "Hello Server";

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

    // Receive a test message for handshake
    const int32 bufferSize = 1024;
    uint8 recvBuffer[bufferSize] = {0};
    int32 bytesRead;

    if (clientSocket->Recv(recvBuffer, bufferSize, bytesRead)){
        FString receivedMessage = UTF8_TO_TCHAR(recvBuffer);
        // Optional: Print or handle the received message
        UE_LOG(LogTemp, Warning, TEXT("Received from server: %s"), *receivedMessage);
    }else{
        UE_LOG(LogTemp, Warning, TEXT("Failed to receive data or no data was received."));
    }

}

// Send array of bytes to server
void SocketClient::Send(TArray<float>& data)
{
    // Create the buffer
    TArray<uint8> SendBuffer;
	FMemoryWriter writer(SendBuffer);

    for (int32 i=0; i < data.Num(); i++)
    {
        float val = data[i];
		writer << val;
		UE_LOG(LogTemp, Warning, TEXT("Observation Value [%i]: %f"), i, val);
    }

    // Track how many bytes were actually sent over the socket.
    int32 BytesSent = 0;

    // Retrieve pointer, number of bytes and send over socket
    clientSocket->Send(SendBuffer.GetData(), SendBuffer.Num(), BytesSent);
}

FVector SocketClient::Receive()
{
    const int32 bufferSize = 1024;  // or whatever size you expect
    uint8 recvBuffer[bufferSize] = {0};
    int32 bytesRead;
    FVector newLocation;  // Default to (0, 0, 0)

    if (clientSocket->Recv(recvBuffer, bufferSize, bytesRead)){
        TArray<uint8> dataArray(recvBuffer, bytesRead);
        FMemoryReader reader(dataArray);  // Construct FMemoryReader with the data

        float val;
        int32 counter = 0;
        while(!reader.AtEnd())
        {
            reader << val;
            UE_LOG(LogTemp, Warning, TEXT("Received Value: %f"), val);

            switch (counter){
            case 0:
                newLocation.X = val;
                break;
            case 1:
                newLocation.Y = val;
                break;
            default:
                // Handle case where more than 3 floats are received
                UE_LOG(LogTemp, Warning, TEXT("Unexpected extra value received: %f"), val);
                break;
            }
            counter++;
        }

        UE_LOG(LogTemp, Warning, TEXT("Received FVector: (%f, %f, %f)"), newLocation.X, newLocation.Y, newLocation.Z);
    }
    else{
        UE_LOG(LogTemp, Warning, TEXT("No action received !!!"));
    }

    return newLocation;
}

// Check if socket was created successfully
bool SocketClient::IsSocketCreated()
{
	return clientSocket != nullptr;
}

// Check if socket was created successfully
bool SocketClient::IsSocketConnected()
{
	if (IsSocketCreated()){
		ESocketConnectionState connectionState = clientSocket->GetConnectionState();
		return connectionState == ESocketConnectionState::SCS_Connected;
	}
	return false;
}
