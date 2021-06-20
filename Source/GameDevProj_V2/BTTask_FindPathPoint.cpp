// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindPathPoint.h"
#include "ShooterCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTTask_FindPathPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) 
{
    Super::ExecuteTask(OwnerComp,NodeMemory);

    AShooterCharacter *Owner = Cast<AShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    
    if (Owner != nullptr)
    {
        int PatrolPathIndexValue = OwnerComp.GetBlackboardComponent()->GetValueAsInt(GetSelectedPatrolPathIndexKey());
        FVector PathVectorValue = Owner->GetPatrolPath().GetData()[PatrolPathIndexValue];
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedPathVectorKey(), PathVectorValue);
    }

    // OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

    return EBTNodeResult::Succeeded;
}

FName UBTTask_FindPathPoint::GetSelectedPathVectorKey() const
{
    return PathVector.SelectedKeyName;
}

FName UBTTask_FindPathPoint::GetSelectedPatrolPathIndexKey() const
{
    return PatrolPathIndex.SelectedKeyName;
}
