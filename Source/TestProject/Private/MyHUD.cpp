// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "FWidgetsLayoutBP.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UI/InteractText.h"
#include "UI/InventoryLayout.h"
#include "UI/ProfileLayout.h"

AMyHUD::AMyHUD()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> BP_WidgetDB(TEXT("/Game/Blueprints/Widgets_DB.Widgets_DB"));
	if (BP_WidgetDB.Succeeded())
	{
		WidgetDB = BP_WidgetDB.Object;
	}
}

void AMyHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();
	
	const UDataTable* WidgetTable = WidgetDB;
	FWidgetsLayoutBP* NewWidgetData = nullptr;
	
	HUDReference = CreateWidgetFromDataTable(WidgetTable, NewWidgetData, FName("HUDLayout_WBP"));
	if (HUDReference)
	{	
		HUDReference->AddToViewport();		
	}

	ProfileLayout = CreateWidgetFromDataTable(WidgetTable, NewWidgetData, FName("ProfileLayout_WBP"));
	if (ProfileLayout)
	{
		ProfileLayout->AddToViewport();
		ProfileLayout->SetAnchorsInViewport(FAnchors{0.2f, 0.2f});
		ProfileLayout->SetVisibility(ESlateVisibility::Hidden);
	}

	InventoryLayout = CreateWidgetFromDataTable(WidgetTable, NewWidgetData, FName("InventoryLayout_WBP"));
	if (InventoryLayout)
	{
		InventoryLayout->AddToViewport();
		InventoryLayout->SetAnchorsInViewport(FAnchors{0.7f, 0.2f});
		InventoryLayout->SetVisibility(ESlateVisibility::Hidden);
	}

	InteractTextWidget = CreateWidgetFromDataTable(WidgetTable, NewWidgetData, FName("InteractText_WBP"));
	if (InteractTextWidget)
	{
		InteractTextWidget->AddToViewport();
		InteractTextWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

UUserWidget* AMyHUD::GetInteractWidget()
{
	const UDataTable* WidgetTable = WidgetDB;
	FWidgetsLayoutBP* NewWidgetData = nullptr;
	
	return CreateWidgetFromDataTable(WidgetTable, NewWidgetData, FName("InteractText_WBP"));

	//UUserWidget* TempWidget = InteractTextWidget;
	//return TempWidget;
}

bool AMyHUD::IsAnyWidgetVisible()
{
	if (InventoryLayout->IsVisible() || ProfileLayout->IsVisible())
	{
		return true;
	}
	return false;
}

void AMyHUD::ToggleWindow(const ELayout Layout)
{
	if (Layout == ELayout::Inventory)
	{
		Cast<UInventoryLayout>(InventoryLayout)->ToggleWindow();
	}
	else if (Layout == ELayout::Equipment)
	{
		Cast<UProfileLayout>(ProfileLayout)->ToggleWindow();
	}
}

void AMyHUD::RefreshWidgetUILayout(const ELayout Layout)
{
	if (Layout == ELayout::Inventory)
	{
		if (UInventoryLayout* InventoryWidget = Cast<UInventoryLayout>(InventoryLayout))
		{
			InventoryWidget->RefreshWindow();
		}
	}
	else if (Layout == ELayout::Equipment)
	{
		if (UProfileLayout* ProfileWidget = Cast<UProfileLayout>(ProfileLayout))
		{
			ProfileWidget->RefreshWindow();
		}
	}
}

UUserWidget* AMyHUD::CreateWidgetFromDataTable(const UDataTable* WidgetTable, FWidgetsLayoutBP*& NewWidgetData, FName Name)
{
	NewWidgetData = WidgetTable->FindRow<FWidgetsLayoutBP>(Name, "", true);
	if (NewWidgetData)
	{
		return CreateWidget<UUserWidget>(GetWorld(), NewWidgetData->Widget);
	}
	return nullptr;
}

FWidgetsLayoutBP* AMyHUD::GetWidgetBPClass(const FName Name)
{
	const UDataTable* WidgetTable = WidgetDB;
	return WidgetTable->FindRow<FWidgetsLayoutBP>(Name, "", true);
}
