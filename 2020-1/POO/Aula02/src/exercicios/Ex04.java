package exercicios;

import entrada.FilteredInput;

public class Ex04 {
	public static void main(String[] args) {
		int num = FilteredInput.readAsInt("Number to test prime: ");
		for (int i = 2; i <= Math.sqrt(num); i++) {
			if (num%i == 0) {
				System.out.println(i);
				return;
			}
		}
		System.out.println(num + " é primo");
	}
}
