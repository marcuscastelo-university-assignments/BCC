import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;
import java.util.TreeMap;

public class Loja {
	private final Map<Integer, Produto> produtosPorCodigoBarras;
	public Loja() {
		produtosPorCodigoBarras = new TreeMap<Integer, Produto>();
	}
	
	public void addProdutos(Produto... produtosAAdicionar) {
		for (Produto p: produtosAAdicionar) {
			Produto produtoEstocado = produtosPorCodigoBarras.getOrDefault(p.getCodigoBarras(), null);
			
			if (produtoEstocado == null) produtosPorCodigoBarras.put(p.getCodigoBarras(), p);
			else {
				if (!((produtoEstocado.getClass().isInstance(p)) || (p.getClass().isInstance(produtoEstocado)))) {
					throw new RuntimeException("Tentando atualizar produto por código de barras, mas a categoria não confere [Cod: " + p.getCodigoBarras() + "]");
				}
				if (!produtoEstocado.getNome().equalsIgnoreCase(p.getNome())) {
					throw new RuntimeException("O produto inserido [" + p.getNome() + "] não pode ser inserido em cima de [" + produtoEstocado.getNome() + "], que possui o memsmo código de barras: " + p.getCodigoBarras());
				}
				produtoEstocado.setQuantidade(produtoEstocado.getQuantidade() + p.getQuantidade());
			}
		}
	}
	
	public Produto buscarProduto(int codigoBarras) {
		return produtosPorCodigoBarras.get(codigoBarras);
	}
	
	public Produto buscarProduto(String nome) {
		Iterator<Produto> it = produtosPorCodigoBarras.values().iterator();
		Produto p;
		while (it.hasNext()) {
			p = it.next();
			if (p.getNome().equals(nome)) return p;
		}
		return null;
	}
	
	public void venderProduto(int codigoBarras) {
		Produto p = produtosPorCodigoBarras.get(codigoBarras);
		if (p.getQuantidade() == 0) throw new RuntimeException("Não há mais desse produto na loja");
		p.setQuantidade(p.getQuantidade()-1);
	}
	
	public void verificarEstoque() {
		String outputCodigoBarras = "";
		HashMap<String, Integer> quantidadePorCategoria = new HashMap<>();
		
		//Para cada produto
		for (Entry<Integer, Produto> cod_produto : produtosPorCodigoBarras.entrySet()) {
			Produto p = cod_produto.getValue();
			String categoria = p.getTipo();
			
			//Conta na categoria a quantidade
			quantidadePorCategoria.put(categoria, quantidadePorCategoria.getOrDefault(categoria, 0) + p.getQuantidade());
			
			outputCodigoBarras += String.format("Cod: [%s] --- Produto: [%s] '%s' --- Quantidade: %d\n", cod_produto.getKey(), p.getTipo(), p.getNome(), p.getQuantidade());
		}
		
		for (Entry<String, Integer> classe_quantidade: quantidadePorCategoria.entrySet() ) {
			System.out.println(String.format("Categoria: %s --- Quantidade: %d", classe_quantidade.getKey(), classe_quantidade.getValue()));
		}
		
		System.out.println();
		System.out.println(outputCodigoBarras);
	}
}	
