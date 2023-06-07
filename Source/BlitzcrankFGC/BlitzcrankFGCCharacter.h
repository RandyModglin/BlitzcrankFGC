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
	VE_MovingForward	UMETA(DisplayName = "Forward"),
	VE_MovingBack	UMETA(DisplayName = "Backward"),
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

	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

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

	
	//Is the player crouching?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool isCrouching;

	//Is the player in the air?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
		bool isAirborne;



	//Is the player turned around?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		bool isFlipped;

	//The Character's Transform
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		FTransform transform;

	//The Character's Scale
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Model")
		FVector scale;



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

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
