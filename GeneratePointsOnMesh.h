// GeneratePointsOnMesh.h

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeneratePointsOnMesh.generated.h"  // #include "GenerateMeshPoints.generated.h"

UCLASS()
class VCC_CARCONFIG01_API AGeneratePointsOnMesh : public AActor
{
    GENERATED_BODY()

public:
    AGeneratePointsOnMesh();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generation")
        bool bGeneratePointsInsideHollow;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generation")
        int32 NumberOfPoints;

    UFUNCTION(BlueprintCallable, Category = "Spline")
        void GeneratePointsInsideHollow();

    UPROPERTY(VisibleAnywhere)
        class UStaticMeshComponent* MeshComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generation")
        class USplineComponent* SplineComponent;
protected:


    virtual void BeginPlay() override;

    //void GeneratePointsInsideHollow();
};
