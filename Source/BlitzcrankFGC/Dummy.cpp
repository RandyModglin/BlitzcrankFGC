// Fill out your copyright notice in the Description page of Project Settings.
#include "Dummy.h"

// Sets default values
ADummy::ADummy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    DummyHealth = 1.0f;
}

void ADummy::TakeDamage(float _damageValue) {

    UE_LOG(LogTemp, Warning, TEXT("You dealt %f damage"), _damageValue);

    DummyHealth -= _damageValue;

    if (DummyHealth < 0.0f) {
        DummyHealth = 0.0f;
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

