// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IncrementPathIndex.h"
#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

EBTNodeResult::Type UBTTask_IncrementPathIndex::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) 
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    int PathIndex = OwnerComp.GetBlackboardComponent()->GetValueAsInt(GetSelectedBlackboardKey());
    PathIndex++;

    AShooterCharacter *Owner = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    
    if (Owner != nullptr)
    {
        PathIndex = (PathIndex + Owner->GetPatrolPath().Num()) % (Owner->GetPatrolPath().Num());
    }

    OwnerComp.GetBlackboardComponent()->SetValueAsInt(GetSelectedBlackboardKey(), PathIndex);

    return EBTNodeResult::Succeeded;
    
}
