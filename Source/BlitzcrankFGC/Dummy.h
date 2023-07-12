// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Dummy.generated.h"

UCLASS()
class BLITZCRANKFGC_API ADummy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADummy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//Damage the Dummy
	UFUNCTION(BlueprintCallable)
		void TakeDamage(float _damageValue);


	//Amount of Health the Dummy has
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float dummyHealth;



	//Dummy's Hurtbox
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		AActor* dummyHurtbox;

	//All of a Dummy's Hurtboxes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		TArray<UStaticMeshComponent*> hurtboxArray;



	//Is the player turned around?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		bool isFlipped;

	//The Character's Transform
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		FTransform dummyTransform;

	//The Character's Scale
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		FVector dummyScale;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Flip Dummy
	void FlipDummy();
};
