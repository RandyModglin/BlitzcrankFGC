// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Dummy.h"
#include "BlitzcrankFGCCharacter.generated.h"

UENUM(BlueprintType)
enum class EDirectionalInput : uint8
{
	VE_Default		UMETA(DisplayName = "Standing"),
	VE_MovingRight	UMETA(DisplayName = "Right"),
	VE_MovingLeft	UMETA(DisplayName = "Left"),
	VE_Jumping		UMETA(DisplayName = "Jumping"),
	VE_Crouching	UMETA(DisplayName = "Crouching")
};


USTRUCT(BlueprintType)
struct FInputInfo {
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		FString inputName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		float timeStamp;
};

UCLASS(config=Game)
class ABlitzcrankFGCCharacter : public ACharacter
{
	GENERATED_BODY()

	void StartAttackL();
	void StartAttackM();
	void StartAttackH();
	void StartAttackS();

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface


	//Overriding the Character and Pawn to have increased control over Jumping and Landing
	virtual void Jump() override;
	virtual void StopJumping() override;
	virtual void Landed(const FHitResult& Hit) override;

	//Begin Crouching
	UFUNCTION(BlueprintCallable)
		void StartCrouching();

	//Stop Crouching
	UFUNCTION(BlueprintCallable)
		void StopCrouching();




	//Reference to the Dummy
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Reference")
		ADummy* dummyRef;

	//The maximum distance apart Blitz and the Dummy can be
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float maxDistanceApart;




	//The direction the player is holding down
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		EDirectionalInput directionalInput;

	//Is the player using an attack?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
		bool isLightAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
		bool isMediumAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
		bool isHeavyAttacking;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attacks")
		bool isSpecialAttacking;

	


	//Can the player move?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool canMove;

	//Is the player crouching?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool isCrouching;

	//How high the player jumps
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float jumpHeight;

	//How far the player jumps
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		float jumpDistance;

	//Max number of times the player can jump before landing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		int maxJumpCount;

	//The current number of times the player has jumped since landing
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		int jumpCount;




	//Is the player turned around?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		bool isFlipped;

	//The Character's Transform
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		FTransform transform;

	//The Character's Scale
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		FVector scale;




	//Player's Mainhurtbox
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		AActor* playerHurtbox;

	//All of a Player's Hurtboxes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
		TArray<UStaticMeshComponent*> hurtboxArray;




	//Ignore's Collision betwen the Player and Dummy 
	UFUNCTION(BlueprintImplementableEvent)
	void IgnorePlayerToPlayerCollision(bool _shouldIgnore);

	//Adds Inputs to the Input Buffer
	UFUNCTION(BlueprintCallable)
	void LaunchPlayer(FVector _launchVelocity, bool _shouldOverrideXY, bool _shouldOverrideZ, bool _shouldIgnorePlayerCollision = false);




	//Adds Inputs to the Input Buffer
	UFUNCTION(BlueprintCallable)
		void AddInputToBuffer(FInputInfo _inputInfo);

	//Removes Inputs from the Input Buffer
	UFUNCTION(BlueprintCallable)
		void RemoveInputFromBuffer();

	//The array of inputs the player has performed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
		TArray<FInputInfo> inputBuffer;
	
	//The Timer Handle to remove inputs from the buffer
	FTimerHandle inputBufferTimerHandle;

	//The amount of time before inputs are removed from the buffer
	float removeInputFromBufferTime;

public:
	ABlitzcrankFGCCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
