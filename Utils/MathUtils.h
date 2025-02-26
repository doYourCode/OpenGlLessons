#pragma once

namespace Utils
{
	namespace Math
	{
		/// <summary>
		/// Restringe um valor a um intervalo determinado pelo usuário.
		/// Porém ao atingir os limites o valor é substituído para o
		/// outro extremo desse intervalo. Ex: Em um intervalo entre 0.0
		/// (min) e 1.0 (max) se um valor crescente atingir 1.01 ele
		/// será substituído por 0.0.
		/// </summary>
		/// <param name="x"> O valor a ser processado. </param>
		/// <param name="min"> O valor mínimo dentro do intervalo. </param>
		/// <param name="max"> O valor máximo dentro do intervalo. </param>
		/// <returns> O valor já processado. </returns>
		float ClampSwap(float x, float min, float max);
	}
}
