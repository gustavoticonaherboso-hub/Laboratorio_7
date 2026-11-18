// Evita que este header se incluya mas de una vez.
#pragma once

// Tipos basicos de Unreal.
#include "CoreMinimal.h"
// Builder abstracto del que hereda.
#include "ConstructorPlataforma.h"
// Archivo generado por Unreal Header Tool; siempre el ultimo include.
#include "ConstructorPlataformaTorre.generated.h"

/**
 * PATRON BUILDER: "BUILDER CONCRETO" #2.
 * Construye una plataforma grande y cubierta: piso 600x600, 3 paredes altas, techo y escalera ancha.
 */
UCLASS() // Registra la clase en el sistema de reflexion.
class LAB_7_API UConstructorPlataformaTorre : public UConstructorPlataforma
{
	GENERATED_BODY() // Codigo interno generado por Unreal.

public: // Seccion publica.
	// Implementa el paso: construir piso.
	virtual void ConstruirPiso() override;
	// Implementa el paso: construir paredes altas.
	virtual void ConstruirParedes() override;
	// Implementa el paso: construir techo.
	virtual void ConstruirTecho() override;
	// Implementa el paso: construir escalera.
	virtual void ConstruirEscalera() override;

protected: // Seccion protegida.
	// Nombre descriptivo de este tipo de plataforma.
	virtual FString ObtenerNombreTipo() const override;
};
