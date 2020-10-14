package agenda;

import java.util.ArrayList;
import java.util.Collections;

public class Agenda {
	
	private ArrayList<Contato> contatos;
	public Agenda() {
		contatos = new ArrayList<Contato>();
	}
	
	public void adicionarContatos(Contato... contatos) {
		for (Contato contato : contatos) {
			if (this.contatos.contains(contato)) 
				throw new RuntimeException(String.format("O contato de ID=%s já está registrado", contato.getIdUnico()));

			this.contatos.add(contato);
		}
	}
	
	public void removerContato(String CPX) {
		contatos.removeIf((Contato contato) -> contato.getIdUnico().equals(CPX));
	}
	
	public Contato pesquisarContato(String CPX) {		
		return contatos.stream().filter((Contato contato) -> contato.getIdUnico() == CPX).findFirst().orElse(null);
	}
	
	public String listarTodosOsContatos() {
		return contatos.stream().reduce("", (String accumulator, Contato contato) -> accumulator + contato.toString() + "\n", String::concat);
	}
	
	public void ordenarContatos() {
		Collections.sort(contatos);
	}
}
