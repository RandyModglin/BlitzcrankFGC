// Fill out your copyright notice in the Description page of Project Settings.
#include "Dummy.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ADummy::ADummy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    dummyHealth = 1.0f;

	//Model variables
	dummyTransform = FTransform();
	dummyScale = FVector(1.0f, 1.0f, 1.0f);
	isFlipped = true;
	dummyHurtbox = nullptr;
}

void ADummy::TakeDamage(float _damageValue) {

    UE_LOG(LogTemp, Warning, TEXT("You dealt %f damage"), _damageValue);

    dummyHealth -= _damageValue;

    if (dummyHealth < 0.0f) {
        dummyHealth = 0.0f;
    }
}

void ADummy::FlipDummy() 
{
	if (isFlipped)
	{
		if (auto mesh = GetCapsuleComponent()->GetChildComponent(1)) //Get Mesh from Capsule Component
		{
			dummyTransform = mesh->GetRelativeTransform();
			dummyScale = dummyTransform.GetScale3D();
			dummyScale.Y = 1;
			dummyTransform.SetScale3D(dummyScale);
			mesh->SetRelativeTransform(dummyTransform);
		}
		isFlipped = false;
	}

	else
	{
		if (auto mesh = GetCapsuleComponent()->GetChildComponent(1)) //Get Mesh from Capsule Component
		{
			dummyTransform = mesh->GetRelativeTransform();
			dummyScale = dummyTransform.GetScale3D();
			dummyScale.Y = -1;
			dummyTransform.SetScale3D(dummyScale);
			mesh->SetRelativeTransform(dummyTransform);
		}
		isFlipped = true;
	}
}

// Called when the game starts or when spawned
void ADummy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADummy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

