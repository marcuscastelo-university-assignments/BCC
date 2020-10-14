package exercicios;

import entrada.FilteredInput;

public class Ex08 {

	static class CritialPointExcepion extends Exception {
		static final long serialVersionUID = 20392038270620l;
		public CritialPointExcepion(String message) {
			super(message);
		}
	}
	
	
	public static void main(String[] args) {
		//Função usada: x³ - x² - 13x + 8
		
		double x1 = FilteredInput.readAsDouble("Digite um palpite de raiz: ");
		try {
			double x2 = newton(x1);
			
			while (Math.abs(x1-x2) > 1e-5) {
				x1 = x2;
				x2 = newton(x2);
			}
			
			System.out.println("A raiz aproximada é: " + x2);
		} catch (CritialPointExcepion e) {
			System.out.println("O palpite dado é um ponto crítico da função, logo o método não pode ser aplicado");
		}
		
	}

	static double newton(double x1) throws CritialPointExcepion{
		double derivX = calcDerivVal(x1);
		if (derivX == 0) throw new CritialPointExcepion("O ponto especificado é um ponto crítico");
		return x1 - ( calcFuncVal(x1) /  derivX);
	}

	static double calcFuncVal(double x) {
		return x*x*x - x*x - 13*x + 8;
	}
	
	static double calcDerivVal(double x) {
		return 3*x*x - 2*x - 13;
	}

	static boolean isSameSignal(double a, double b) {
		return a<0&&b<0||a>0&&b>0;
	}
}
