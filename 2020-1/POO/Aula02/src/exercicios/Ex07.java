package exercicios;

import entrada.FilteredInput;

public class Ex07 {
	static class Interval {
		public double a, b, root = -1;
		public double calcMeio() { return (a+b)/2.0; }
	}
	
	public static void main(String[] args) {
		//Função usada: x³ - x² - 13x + 8
		
		System.out.println("Digite o intervalo [a,b]");
		Interval interval = new Interval();
		interval.a = FilteredInput.readAsDouble("a: ");
		interval.b = FilteredInput.readAsDouble("b: ");
		
		handleSpecialCases(interval);
		
		while (!bissec(interval));
		System.out.println("A raiz aproximada é: " + interval.root);		
		
	}
	
	//handle cases like f(a) = 0, f(b) = 0 or f(a) is same signal of f(b)
	static void handleSpecialCases(Interval interval) {
		if (Math.abs(calcFuncVal(interval.a)) < 1e-5) {
			System.out.println("A raiz é o limite inferior do intervalo (a): " + interval.a);
			System.exit(0);
		}
		if (Math.abs(calcFuncVal(interval.b)) < 1e-5) {
			System.out.println("A raiz é o limite superior do intervalo (b): " + interval.b);
			System.exit(0);
		}
		if (isSameSignal(calcFuncVal(interval.a), calcFuncVal(interval.b))) {
			System.out.println("Nada pode ser concluído, pois f(a) tem o mesmo sinal de f(b)");
			System.exit(0);
		}
	}
	
	static boolean bissec(Interval interval) {
		double meio = interval.calcMeio();
		if (Math.abs(calcFuncVal(meio)) < 1e-5) {
			interval.root = meio;
			return true;
		}
		else if (isSameSignal(calcFuncVal(interval.a), calcFuncVal(meio)))
			interval.a = meio;
		else if (isSameSignal(calcFuncVal(interval.b), calcFuncVal(meio)))
			interval.b = meio;
		return false;
	}
	
	static double calcFuncVal(double x) {
		return x*x*x - x*x - 13*x + 8;
	}
	
	static boolean isSameSignal(double a, double b) {
		return a<0&&b<0||a>0&&b>0;
	}
}
