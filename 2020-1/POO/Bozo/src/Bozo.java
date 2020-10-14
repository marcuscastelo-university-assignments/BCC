
/**
 * Essa é a classe inicial do programa Bozó. Possui apenas o método main, que cuida da execução do jogo.
 * @author marucs
 *
 */
public class Bozo {
	static final int NUM_RODADAS = 10;
	static final int NUM_ROLAR_DENOVO = 3;
	static final int NUM_DADOS = 5;
	
	/**
	 * Método inicial do programa. Ele cuida da execução do jogo e possui um laço, no qual cada iteração representa uma rodada do jogo. Em cada rodada, o jogador joga os dados até 3 vezes e depois escolhe a posição do placar que deseja preencher. No final das rodadas a pontuação total é exibida.
	 * @param args
	 */
	public static void main(String[] args) {
		RolaDados rd = new RolaDados(NUM_DADOS);
		Placar p = new Placar();
		
		int[] dadosRolados = new int[NUM_DADOS]; //Valor inicial, eclipse exige.
		String rolarDenovo;
		for (int i = 0; i < NUM_RODADAS; i++) {
			System.out.println("Pressione ENTER para começar a rodada");
			rolarDenovo = EntradaTeclado.leString();
			rd.rolar();
			for (int j = 0; j < NUM_ROLAR_DENOVO-1; j++) {
				System.out.println(rd);
				System.out.println("Digite os dados a rolar novamente separados por espaço:");
				rolarDenovo = EntradaTeclado.leString();
				dadosRolados = rd.rolar(rolarDenovo);
			}
			System.out.println("Dados rolados (final):");
			System.out.println(rd);
			System.out.println("Placar atual:");
			System.out.println(p);
			boolean positionValid = false;
			while (!positionValid) {
				try {
					int posSalvar = leIntBounded("Em que posição deseja colocar os pontos dessa jogada (1-10)?", 1, 10);
					p.add(posSalvar, dadosRolados);
					positionValid = true;
				} catch (IllegalArgumentException e) {
					System.out.println(e.getMessage());
				}
			}
			System.out.println("Placar atualizado:");
			System.out.println(p);		
		}
		System.out.println("Fim do jogo, pontuação total:"+p.getScore());
		
	}
	
	/**
	 * Função auxiliar que exige que o int digitado não esteja fora do intervalo especificado
	 * @param prompt mensagem de requisição do inteiro
	 * @param min valor mínimo para o int digitado (inclusivo)
	 * @param max valor máximo para o int digitado (inclusivo)
	 * @return int dentro dos limites especificado lido do teclado
	 */
	private static int leIntBounded(String prompt, int min, int max) {
		int res = min-1;
		while (res < min || res > max) {
			System.out.println(prompt);
			res = EntradaTeclado.leInt();
		}
		return res;
	}
}
