// Incluye el header de esta clase.
#include "PlataformaTecho.h"

// Constructor de la pieza.
APlataformaTecho::APlataformaTecho()
{
	// Agrega una etiqueta (Tag) al actor para poder identificarlo en Blueprints o busquedas.
	Tags.Add(FName(TEXT("Techo")));
}

// Devuelve el nombre del tipo de pieza.
FString APlataformaTecho::ObtenerTipo() const
{
	// Texto que se usa al mostrar la composicion de la plataforma.
	return TEXT("Techo");
}
