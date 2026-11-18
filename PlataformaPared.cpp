// Incluye el header de esta clase.
#include "PlataformaPared.h"

// Constructor de la pieza.
APlataformaPared::APlataformaPared()
{
	// Agrega una etiqueta (Tag) al actor para poder identificarlo en Blueprints o busquedas.
	Tags.Add(FName(TEXT("Pared")));
}

// Devuelve el nombre del tipo de pieza.
FString APlataformaPared::ObtenerTipo() const
{
	// Texto que se usa al mostrar la composicion de la plataforma.
	return TEXT("Pared");
}
