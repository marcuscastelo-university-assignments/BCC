package agenda;

public class Teste {
	public static void main(String[] args) {
		Agenda agenda = new Agenda();
		agenda.adicionarContatos(
				new ContatoPF("Marcus", "Cond Edifício Solar - R. São Carlos do Pinhal, 290 - Bela Vista, São Paulo", "marcuscastelo@usp.br", "(11) 4003-1647", "527309897-28", "20/06/2000", "Solteiro"),
				new ContatoPJ("USP - Universidade de São Paulo Campus de São Carlos", "Av. Trab. São Carlense, 400 - Parque Arnold Schimidt, São Carlos", "emailficticio@usp.br", "(16) 3373-9997", "63.025.530/0049-59", "inscricaoUSP", "razaoUSP"),
				new ContatoPF("pf1", "1","1","1","527309897-29","11/09/2001","1")
		);
		System.out.println(agenda.listarTodosOsContatos());

		agenda.ordenarContatos();
		System.out.println(agenda.listarTodosOsContatos());

		Contato c = agenda.pesquisarContato("527309897-29");
		System.out.println(c);

		agenda.removerContato("527309897-29");
		Contato c2 = agenda.pesquisarContato("527309897-29");
		//Exibe null, pois o contato não foi encontrado
		System.out.println(c2);
	}
}
