#include "Manager/ASLogManager.h"

DEFINE_LOG_CATEGORY(LogAttributeShift);

void FASLogManager::Log(const FString& Message)
{
	UE_LOG(LogAttributeShift, Log, TEXT("%s"), *Message);
}

void FASLogManager::Warning(const FString& Message)
{
	UE_LOG(LogAttributeShift, Warning, TEXT("%s"), *Message);
}

void FASLogManager::Error(const FString& Message)
{
	UE_LOG(LogAttributeShift, Error, TEXT("%s"), *Message);
}
