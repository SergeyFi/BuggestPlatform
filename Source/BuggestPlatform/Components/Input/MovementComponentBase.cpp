#include "MovementComponentBase.h"

// Sets default values for this component's properties
UMovementComponentBase::UMovementComponentBase()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UMovementComponentBase::BeginPlay()
{
	Super::BeginPlay();

	FindInputComponent();

	BindToInputComponent();
	
}

void UMovementComponentBase::FindInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
}

void UMovementComponentBase::BindToInputComponent()
{
	PlayerCharacter = Cast<ACharacter>(GetOwner());

	if (PlayerCharacter && InputComponent)
	{
		InputComponent->BindAxis("MoveForward", this, &UMovementComponentBase::MoveForward);

		InputComponent->BindAxis("MoveRight", this, &UMovementComponentBase::MoveRight);

		InputComponent->BindAxis("Turn", PlayerCharacter, &ACharacter::AddControllerYawInput);

		InputComponent->BindAxis("LookUp", PlayerCharacter, &ACharacter::AddControllerPitchInput);

		InputComponent->BindAction("Jump", IE_Pressed, PlayerCharacter, &ACharacter::Jump);
	}
}

void UMovementComponentBase::MoveForward(float Value)
{
	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorForwardVector() * Value);
}

void UMovementComponentBase::MoveRight(float Value)
{
	PlayerCharacter->AddMovementInput(PlayerCharacter->GetActorRightVector() * Value);
}
