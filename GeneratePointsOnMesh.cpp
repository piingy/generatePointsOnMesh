// GeneratePointsOnMesh.cpp

#include "GeneratePointsOnMesh.h"
#include "Components/SplineComponent.h"

AGeneratePointsOnMesh::AGeneratePointsOnMesh()
{
    PrimaryActorTick.bCanEverTick = false;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));

    RootComponent = MeshComponent;
    SplineComponent->SetupAttachment(RootComponent);

    NumberOfPoints = 10;
}

void AGeneratePointsOnMesh::BeginPlay()
{
    Super::BeginPlay();

    if (bGeneratePointsInsideHollow)
    {
        GeneratePointsInsideHollow();
    }
}

void AGeneratePointsOnMesh::GeneratePointsInsideHollow()
{
    FVector BoxExtent = MeshComponent->Bounds.BoxExtent;
    FVector StartLocation = MeshComponent->Bounds.Origin;

    int32 PointsAdded = 0;
    int32 MaxAttempts = 1000;
    while (PointsAdded < NumberOfPoints && MaxAttempts > 0)
    {
        FVector RandomPoint = FMath::RandPointInBox(FBox(StartLocation - BoxExtent, StartLocation + BoxExtent));

        // Generate a 3D grid or voxel representation of the hollow mesh
        // Here, we will use a simple 3D array to represent the voxel grid
        const int32 GridSize = 1000;
        bool VoxelGrid[GridSize][GridSize][GridSize] = { false };

        // Iterate through the voxels inside the hollow mesh and mark them as occupied
        // This step may be more complicated and depends on your mesh's geometry
        // You can use ray-tracing or other algorithms to determine voxel occupancy

        // For simplicity, we'll assume all voxels within the bounding box are occupied
        for (int32 x = 0; x < GridSize; x++)
        {
            for (int32 y = 0; y < GridSize; y++)
            {
                for (int32 z = 0; z < GridSize; z++)
                {
                    VoxelGrid[x][y][z] = true;
                }
            }
        }

        // Convert the random point into voxel coordinates
        FVector VoxelSize = BoxExtent * 2.0f / GridSize;
        FVector VoxelOrigin = StartLocation - BoxExtent + VoxelSize * 0.5f;
        FVector VoxelCoords = (RandomPoint - VoxelOrigin) / VoxelSize;

        // Check if the random point lies within a voxel that is inside the hollow mesh
        if (VoxelCoords.X >= 0 && VoxelCoords.X < GridSize &&
            VoxelCoords.Y >= 0 && VoxelCoords.Y < GridSize &&
            VoxelCoords.Z >= 0 && VoxelCoords.Z < GridSize &&
            VoxelGrid[int32(VoxelCoords.X)][int32(VoxelCoords.Y)][int32(VoxelCoords.Z)])
        {
            // If the point is inside the hollow mesh, add it to the spline
            SplineComponent->AddSplinePoint(RandomPoint, ESplineCoordinateSpace::World);
            PointsAdded++;
        }

        MaxAttempts--;
    }
}
