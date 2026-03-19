#pragma once

#include "CoreMinimal.h"

// AttributeShift 프로젝트 전용 로그 카테고리
DECLARE_LOG_CATEGORY_EXTERN(LogAttributeShift, Log, All);

// 공용 로그 출력 유틸리티
class ATTRIBUTESHIFT_API FASLogManager
{
public:
	// 일반 디버그 로그를 출력
	static void Log(const FString& Message);

	// 경고 로그를 출력
	static void Warning(const FString& Message);

	// 에러 로그를 출력
	static void Error(const FString& Message);
};
