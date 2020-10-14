package agenda;

public class ContatoPF extends Contato{
	private String CPF;
	
	private String dataNascimento, estadoCivil;
	
	public ContatoPF(String nome, String endereco, String email, String telefone, String CPF, String dataNascimento, String estadoCivil) {
		super(nome, endereco, email, telefone);
		this.CPF = CPF;
		this.dataNascimento = dataNascimento;
		this.estadoCivil = estadoCivil;		
	}
	
	public String getDataNascimento() { return dataNascimento; }
	public String getEstadoCivil() { return estadoCivil; }

	@Override
	public String getIdUnico() {
		return CPF;
	}
	
	@Override
	public String toString() {
		return super.toString() + 
				String.format("CPF: '%s' ", CPF) +
				String.format("Data Nascimento: '%s' ", dataNascimento) +
				String.format("Estado Civil: '%s' ", estadoCivil);
	}

	@Override
	public String getTipo() {
		return "Pessoa Física";
	}
	
}
