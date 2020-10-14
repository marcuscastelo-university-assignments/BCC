
public class CD extends Produto {
	public CD(int codigoBarras, String nome, int quantidade) {
		super(codigoBarras, nome, quantidade);
	}
	
	@Override
	public String getTipo() {
		return "CD";
	}
}
