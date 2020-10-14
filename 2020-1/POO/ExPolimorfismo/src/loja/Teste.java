package loja;

public class Teste {
	public static void main(String[] args) {
		Loja loja = new Loja();
		loja.addProdutos(
				new DVD(110, "Star Wars III", 10),
				new CD(112, "Windows XP SP2", 1000),
				new CD(113, "Fotos Família 2009", 1),
				new Livro(111, "Sapiens - Uma Breve História da Humanidade", 90)
		);
		
		//Chegam mais 200 mil cópias do windows xp
		loja.addProdutos(new CD(112, "Windows XP SP2", 200000));
		
		loja.venderProduto(111);
		loja.venderProduto(111);
		loja.verificarEstoque();
		
		System.out.println(loja.buscarProduto(111));
		System.out.println(loja.buscarProduto("Windows XP SP2"));
	}
}
