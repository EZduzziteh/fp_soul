#pragma once

// Always log to output
#define DEBUG(Message) \
    UE_LOG(LogTemp, Display, TEXT("%s"), *FString(Message))

// On-screen debug
#define Debug(Message) \
    do { \
        if (GEngine) \
        { \
            GEngine->AddOnScreenDebugMessage( \
                -1, \
                0.1f, \
                FColor::Green, \
                FString::Printf(TEXT("%s"), TEXT(Message)) \
            ); \
        } \
    } while (0)