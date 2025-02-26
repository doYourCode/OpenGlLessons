#pragma once

namespace Utils
{
	namespace Math
	{
		/// <summary>
		/// Restringe um valor a um intervalo determinado pelo usu�rio.
		/// Por�m ao atingir os limites o valor � substitu�do para o
		/// outro extremo desse intervalo. Ex: Em um intervalo entre 0.0
		/// (min) e 1.0 (max) se um valor crescente atingir 1.01 ele
		/// ser� substitu�do por 0.0.
		/// </summary>
		/// <param name="x"> O valor a ser processado. </param>
		/// <param name="min"> O valor m�nimo dentro do intervalo. </param>
		/// <param name="max"> O valor m�ximo dentro do intervalo. </param>
		/// <returns> O valor j� processado. </returns>
		float ClampSwap(float x, float min, float max);
	}
}
