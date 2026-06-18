// Fill out your copyright notice in the Description page of Project Settings.


#include "RoguePlayerCharacter.h"

#include <ThirdParty/ShaderConductor/ShaderConductor/External/DirectXShaderCompiler/include/dxc/DXIL/DxilConstants.h>

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Projectiles/RogueBlackholeProjectile.h"

// Sets default values
ARoguePlayerCharacter::ARoguePlayerCharacter()
{
	MuzzleSocketName = "Muzzle_01";
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ARoguePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ARoguePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInput->BindAction(Input_Move, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::Move);
	EnhancedInput->BindAction(Input_Look, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::Look);
	EnhancedInput->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &ARoguePlayerCharacter::Jump);
	
	EnhancedInput->BindAction(Input_PrimaryAttack, ETriggerEvent::Triggered, this, 
		&ARoguePlayerCharacter::StartProjectileAttack, PrimaryAttackProjectileClass);
	EnhancedInput->BindAction(Input_SecondaryAttack, ETriggerEvent::Triggered, this, 
		&ARoguePlayerCharacter::StartProjectileAttack, SecondaryAttackProjectileClass);
	EnhancedInput->BindAction(Input_SpecialAttack, ETriggerEvent::Triggered, this, 
		&ARoguePlayerCharacter::StartProjectileAttack, SpecialAttackProjectileClass);
}

void ARoguePlayerCharacter::Move(const FInputActionValue& InValue)
{
	FVector2D InputValue = InValue.Get<FVector2D>();
	
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	
	//Forward / Back
	AddMovementInput(ControlRot.Vector(), InputValue.X);
	//Sideways
	FVector RightDirection = ControlRot.RotateVector(FVector::RightVector);
	AddMovementInput(RightDirection, InputValue.Y);
}

void ARoguePlayerCharacter::Look(const FInputActionInstance& InValue)
{
	FVector2D InputValue = InValue.GetValue().Get<FVector2D>();
	
	AddControllerPitchInput(InputValue.Y);
	AddControllerYawInput(InputValue.X);
}

void ARoguePlayerCharacter::Jump()
{
	ACharacter::Jump();
}

void ARoguePlayerCharacter::StartProjectileAttack(TSubclassOf<ARogueProjectile> ProjectileClass)
{
	PlayAnimMontage(AttackMontage);
	
	FTimerHandle AttackTimerHandle;
	const float AttackDelayTime = 0.2f;
	
	UNiagaraFunctionLibrary::SpawnSystemAttached(CastingEffect, GetMesh(), MuzzleSocketName
		,FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::Type::SnapToTarget, true);
	
	UGameplayStatics::PlaySound2D(this, CastingSound);
	
	FTimerDelegate Delegate;
	Delegate.BindUObject(this, &ARoguePlayerCharacter::AttackTimerElapsed, ProjectileClass);
	GetWorldTimerManager().SetTimer(AttackTimerHandle, Delegate, AttackDelayTime, false);
}

void ARoguePlayerCharacter::AttackTimerElapsed(TSubclassOf<ARogueProjectile> ProjectileClass)
{
	FVector SpawnLocation = GetMesh()->GetSocketLocation(MuzzleSocketName);
	FRotator SpawnRotation = GetControlRotation(); //direction of the camera, rotator from camera
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	AActor* NewProjectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

	MoveIgnoreActorAdd(NewProjectile);
}

// Called every frame
void ARoguePlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



