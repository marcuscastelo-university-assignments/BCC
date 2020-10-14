package agenda;

public class ContatoPJ extends Contato {
	private String CNPJ;
	
	private String inscricaoEstadual, razaoSocial;
	
	public ContatoPJ(String nome, String endereco, String email, String telefone, String CNPJ, String inscricaoEstadual, String razaoSocial) {
		super(nome, endereco, email, telefone);
		this.CNPJ = CNPJ;
		this.inscricaoEstadual = inscricaoEstadual;
		this.razaoSocial = razaoSocial;
	}

	public String getInscricaoEstadual() { return inscricaoEstadual; }
	public String getRazaoSocial() { return razaoSocial; }
	
	@Override
	public String getIdUnico() {
		return CNPJ;
	}
	
	@Override
	public String toString() {
		return super.toString() + 
				String.format("CNPJ: '%s' ", CNPJ) +
				String.format("Inscrição Estadual: '%s' ", getInscricaoEstadual()) +
				String.format("Razão Social: '%s' ", getRazaoSocial());			
	}

	@Override
	public String getTipo() {
		return "Pessoa Jurídica";
	}
}
