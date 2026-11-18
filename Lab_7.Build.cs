// Importa las clases de UnrealBuildTool necesarias para definir el modulo.
using UnrealBuildTool;

// Reglas de compilacion del modulo Lab_7 (el nombre de la clase = nombre del modulo).
public class Lab_7 : ModuleRules
{
	// Constructor de las reglas del modulo.
	public Lab_7(ReadOnlyTargetRules Target) : base(Target)
	{
		// Usa PCH explicitos/compartidos (configuracion estandar de UE 4.27).
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		// Modulos de Unreal que necesitamos: nucleo, objetos, motor e input.
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
		// Dependencias privadas (ninguna por ahora).
		PrivateDependencyModuleNames.AddRange(new string[] { });
	}
}
