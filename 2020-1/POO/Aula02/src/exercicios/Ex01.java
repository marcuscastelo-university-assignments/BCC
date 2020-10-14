package exercicios;

import entrada.FilteredInput;

public class Ex01 {
	
	static final double ERRO = 0.00000001;
	
	public static void main(String argv[]) {
		double numero, chute1, chute2;
				
		numero = FilteredInput.readAsDouble("Valor de x: ");
		chute1 = FilteredInput.readAsDouble("Chute inicial: ");
		
		chute2 = calcProxVal(chute1, numero);
		while (chute1 - chute2 > ERRO || chute2 - chute1 > ERRO) {
			chute1 = chute2;
			chute2 = calcProxVal(chute2, numero);			
		}
		System.out.println("A raiz é aproximadamente " + chute2);		
	}

	
	static double calcProxVal(double valAnterior, double numeroOriginal) {
		double contraPeso = numeroOriginal / valAnterior;
		return (contraPeso + valAnterior) / 2.0;
	}
}
