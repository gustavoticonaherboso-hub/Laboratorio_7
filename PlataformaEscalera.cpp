// Incluye el header de esta clase.
#include "PlataformaEscalera.h"

// Constructor de la pieza.
APlataformaEscalera::APlataformaEscalera()
{
	// Agrega una etiqueta (Tag) al actor para poder identificarlo en Blueprints o busquedas.
	Tags.Add(FName(TEXT("Escalera")));
}

// Devuelve el nombre del tipo de pieza.
FString APlataformaEscalera::ObtenerTipo() const
{
	// Texto que se usa al mostrar la composicion de la plataforma.
	return TEXT("Escalera");
}
