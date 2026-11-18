// Incluye el header de esta clase.
#include "PlataformaPiso.h"

// Constructor de la pieza.
APlataformaPiso::APlataformaPiso()
{
	// Agrega una etiqueta (Tag) al actor para poder identificarlo en Blueprints o busquedas.
	Tags.Add(FName(TEXT("Piso")));
}

// Devuelve el nombre del tipo de pieza.
FString APlataformaPiso::ObtenerTipo() const
{
	// Texto que se usa al mostrar la composicion de la plataforma.
	return TEXT("Piso");
}
