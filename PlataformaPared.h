// Evita que este header se incluya mas de una vez.
#pragma once

// Tipos basicos de Unreal.
#include "CoreMinimal.h"
// Clase base de la que hereda esta pieza.
#include "ComponentePlataforma.h"
// Archivo generado por Unreal Header Tool; siempre el ultimo include.
#include "PlataformaPared.generated.h"

/**
 * PRODUCTO CONCRETO (componente): Pared o baranda lateral de la plataforma.
 */
UCLASS() // Registra la clase en el sistema de reflexion de Unreal.
class LAB_7_API APlataformaPared : public AComponentePlataforma // Hereda de la pieza base.
{
	GENERATED_BODY() // Codigo interno generado por Unreal.

public: // Seccion publica.
	// Constructor de la pieza.
	APlataformaPared();

	// Sobrescribe el nombre del tipo para identificar esta pieza.
	virtual FString ObtenerTipo() const override;
};
