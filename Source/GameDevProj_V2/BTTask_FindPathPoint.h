// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindPathPoint.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEVPROJ_V2_API UBTTask_FindPathPoint : public UBTTaskNode
{
	GENERATED_BODY()

public:
	FName GetSelectedPathVectorKey() const;
	FName GetSelectedPatrolPathIndexKey() const;

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector PathVector;
	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector PatrolPathIndex;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
