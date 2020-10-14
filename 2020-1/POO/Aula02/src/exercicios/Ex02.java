package exercicios;

import entrada.FilteredInput;

public class Ex02 {
	public static void main(String[] args) {
		int treeSize = FilteredInput.readAsInt("Digite o tamanho da árvore: ");
		for (int i=treeSize; i > 0; i--) {
			for (int j = 0; j < i; j++) {
				System.out.print("*");
			}
			System.out.println();
		}
	}
	

}
