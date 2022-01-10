// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDLayout.h"

#include "DragItem.h"
#include "DragWidget.h"

bool UHUDLayout::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	
	UDragWidget* DragWidgetResult = Cast<UDragWidget>(InOperation);

	if (!IsValid(DragWidgetResult))
	{
		//UE_LOG(LogTemp, Warning, TEXT("DragWidget Cast returned null."))

		// Drop Dragged Inventory Item
		UDragItem* DragItemResult = Cast<UDragItem>(InOperation);
		if (!IsValid(DragItemResult))
		{
			//UE_LOG(LogTemp, Warning, TEXT("DragItem Cast returned null."))

			return false;
		}
		
		//UE_LOG(LogTemp, Warning, TEXT("DragItem Cast returned successfully."))
		
		return false;
	} //Drop Dragged UI Window
	else
	{
		const FVector2D DragWindowOffset = InGeometry.AbsoluteToLocal(InDragDropEvent.GetScreenSpacePosition());
		const FVector2D DragWindowOffsetResult = DragWindowOffset - DragWidgetResult->DragOffset;

		DragWidgetResult->WidgetReference->AddToViewport();
		DragWidgetResult->WidgetReference->SetVisibility(ESlateVisibility::Visible);
		DragWidgetResult->WidgetReference->SetPositionInViewport(DragWindowOffsetResult, false);
	
		return true;
	}
}