package entrada;

import java.io.IOException;

public class FilteredInput {
	public static int readAsInt(String promptMessage) {
		int res = 0; boolean success = false;
		while (!success) {
			try { res = EntradaTeclado.leInt(); success = true; }
			catch (IOException e) { System.out.println("O conteúdo digitado não é um número"); }
		}
		return res;		
	}
	
	public static double readAsDouble(String promptMessage) {
		double res = 0; boolean success = false;
		while (!success) {
			try { res = EntradaTeclado.leDouble(); success = true; }
			catch (IOException e) { System.out.println("O conteúdo digitado não é um número"); }
		}
		return res;		
	}
}
