// Evita que este header se incluya mas de una vez.
#pragma once

// Tipos basicos de Unreal.
#include "CoreMinimal.h"
// Builder abstracto del que hereda.
#include "ConstructorPlataforma.h"
// Archivo generado por Unreal Header Tool; siempre el ultimo include.
#include "ConstructorPlataformaBasica.generated.h"

/**
 * PATRON BUILDER: "BUILDER CONCRETO" #1.
 * Construye una plataforma pequena: piso 400x400, barandas bajas, SIN techo, escalera de 5 escalones.
 */
UCLASS() // Registra la clase en el sistema de reflexion.
class LAB_7_API UConstructorPlataformaBasica : public UConstructorPlataforma
{
	GENERATED_BODY() // Codigo interno generado por Unreal.

public: // Seccion publica.
	// Implementa el paso: construir piso.
	virtual void ConstruirPiso() override;
	// Implementa el paso: construir barandas (paredes bajas).
	virtual void ConstruirParedes() override;
	// Implementa el paso: techo (esta version no construye techo).
	virtual void ConstruirTecho() override;
	// Implementa el paso: construir escalera.
	virtual void ConstruirEscalera() override;

protected: // Seccion protegida.
	// Nombre descriptivo de este tipo de plataforma.
	virtual FString ObtenerNombreTipo() const override;
};
