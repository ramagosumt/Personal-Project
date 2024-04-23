// Fill out your copyright notice in the Description page of Project Settings.

#include "World/StalkCamera.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/MainCharacter.h"
#include "Components/SphereComponent.h"

AStalkCamera::AStalkCamera()
{
	ScanRadius = CreateDefaultSubobject<USphereComponent>(TEXT("ScanRadius"));
	ScanRadius->SetupAttachment(MainMesh);
	ScanRadius->SetRelativeLocation(FVector(0.f, 0.f, 190.f));
	ScanRadius->SetSphereRadius(1000.f);
	ScanRadius->OnComponentBeginOverlap.AddDynamic(this, &AStalkCamera::OnOverlapBegin);
	ScanRadius->OnComponentEndOverlap.AddDynamic(this, &AStalkCamera::OnOverlapEnd);
	
	CameraPart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CameraPart"));
	CameraPart->SetupAttachment(MainMesh);
	CameraPart->SetRelativeLocation(FVector(-0.3f, 0.7f, -10.f));
	CameraPart->SetRelativeRotation(FRotator(27.f, 234.f, 345.f));

	InitialInteractionCheckDelayTime = 1.f;
}

void AStalkCamera::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(InitialInteractionCheck, this, &AStalkCamera::InteractionCheck, InitialInteractionCheckDelayTime, false);
}

void AStalkCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InteractingCharacter)
	{
		const FVector DesiredLookAtLocation = MainMesh->GetComponentLocation() - InteractingCharacter->GetActorLocation();
		const FRotator DesiredRotation = FRotationMatrix::MakeFromZ(DesiredLookAtLocation).Rotator();
		
		CameraPart->SetWorldRotation(DesiredRotation);
	}
}

void AStalkCamera::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		InteractingCharacter = Cast<AMainCharacter>(OtherActor);
	}
}

void AStalkCamera::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (InteractingCharacter)
	{
		InteractingCharacter = nullptr;
	}
}

void AStalkCamera::InteractionCheck()
{
	ScanRadius->GetOverlappingActors(InteractingActors, AMainCharacter::StaticClass());

	if (InteractingActors.Num() > 0)
	{
		InteractingCharacter = Cast<AMainCharacter>(InteractingActors[0]);
	}
}
