// Incluye el header de esta clase.
#include "ConstructorPlataformaBasica.h"
// Pieza: piso.
#include "PlataformaPiso.h"
// Pieza: pared.
#include "PlataformaPared.h"
// Pieza: escalera (escalon).
#include "PlataformaEscalera.h"

// Constantes de este Builder en un namespace con nombre propio (evita choques en los "unity builds" de Unreal; 100 uu = 1 metro).
namespace ConfigBasica
{
	// Mitad del lado de la plataforma (lado total = 400).
	constexpr float Mitad = 200.f;
	// Altura a la que queda la superficie del piso respecto al suelo.
	constexpr float AlturaPiso = 100.f;
	// Grosor del piso.
	constexpr float GrosorPiso = 20.f;
	// Altura de las barandas.
	constexpr float AlturaBaranda = 50.f;
	// Grosor de las barandas.
	constexpr float GrosorBaranda = 10.f;
	// Cantidad de escalones.
	constexpr int32 NumEscalones = 5;
	// Ancho de la escalera (eje Y).
	constexpr float AnchoEscalera = 150.f;
	// Profundidad de cada escalon (eje X).
	constexpr float FondoEscalon = 50.f;
}

// PASO 1: construye el piso.
void UConstructorPlataformaBasica::ConstruirPiso()
{
	// Lado completo del piso.
	const float Lado = ConfigBasica::Mitad * 2.f;
	// Crea el piso centrado; su cara superior queda en ConfigBasica::AlturaPiso. Escala = tamano / 100 (el cubo mide 100).
	CrearComponente(APlataformaPiso::StaticClass(),
		FVector(0.f, 0.f, ConfigBasica::AlturaPiso - ConfigBasica::GrosorPiso / 2.f), // Posicion relativa a la plataforma.
		FVector(Lado / 100.f, Lado / 100.f, ConfigBasica::GrosorPiso / 100.f), // Escala (X, Y, Z).
		FLinearColor(0.35f, 0.35f, 0.35f)); // Color gris.
}

// PASO 2: construye 3 barandas (el lado +X queda libre para la escalera).
void UConstructorPlataformaBasica::ConstruirParedes()
{
	// Lado completo de la plataforma.
	const float Lado = ConfigBasica::Mitad * 2.f;
	// Altura del centro de las barandas (sobre el piso).
	const float Z = ConfigBasica::AlturaPiso + ConfigBasica::AlturaBaranda / 2.f;
	// Color marron para las barandas.
	const FLinearColor Color(0.35f, 0.18f, 0.05f);

	// Baranda del lado +Y.
	CrearComponente(APlataformaPared::StaticClass(), FVector(0.f, ConfigBasica::Mitad - ConfigBasica::GrosorBaranda / 2.f, Z),
		FVector(Lado / 100.f, ConfigBasica::GrosorBaranda / 100.f, ConfigBasica::AlturaBaranda / 100.f), Color);
	// Baranda del lado -Y.
	CrearComponente(APlataformaPared::StaticClass(), FVector(0.f, -(ConfigBasica::Mitad - ConfigBasica::GrosorBaranda / 2.f), Z),
		FVector(Lado / 100.f, ConfigBasica::GrosorBaranda / 100.f, ConfigBasica::AlturaBaranda / 100.f), Color);
	// Baranda del lado -X (atras).
	CrearComponente(APlataformaPared::StaticClass(), FVector(-(ConfigBasica::Mitad - ConfigBasica::GrosorBaranda / 2.f), 0.f, Z),
		FVector(ConfigBasica::GrosorBaranda / 100.f, Lado / 100.f, ConfigBasica::AlturaBaranda / 100.f), Color);
}

// PASO 3: esta plataforma basica NO tiene techo.
void UConstructorPlataformaBasica::ConstruirTecho()
{
	// Intencionalmente vacio: es una variacion valida del Builder (un paso puede no hacer nada).
}

// PASO 4: construye la escalera de acceso por el lado +X.
void UConstructorPlataformaBasica::ConstruirEscalera()
{
	// Recorre cada escalon desde el mas bajo (1) hasta el mas alto (ConfigBasica::NumEscalones).
	for (int32 k = 1; k <= ConfigBasica::NumEscalones; ++k)
	{
		// Altura total del escalon k (cada escalon sube 20 unidades).
		const float Altura = (ConfigBasica::AlturaPiso / ConfigBasica::NumEscalones) * k;
		// Posicion X: los escalones mas altos estan mas cerca del piso.
		const float X = ConfigBasica::Mitad + ConfigBasica::FondoEscalon / 2.f + (ConfigBasica::NumEscalones - k) * ConfigBasica::FondoEscalon;
		// Crea el escalon: su centro Z es la mitad de su altura (apoyado en el suelo).
		CrearComponente(APlataformaEscalera::StaticClass(), FVector(X, 0.f, Altura / 2.f),
			FVector(ConfigBasica::FondoEscalon / 100.f, ConfigBasica::AnchoEscalera / 100.f, Altura / 100.f),
			FLinearColor(0.6f, 0.6f, 0.2f)); // Color amarillento.
	}
}

// Nombre descriptivo del tipo de plataforma.
FString UConstructorPlataformaBasica::ObtenerNombreTipo() const
{
	// Se mostrara en pantalla al terminar la construccion.
	return TEXT("Plataforma Basica");
}
