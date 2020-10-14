package agenda;

public abstract class Contato implements Comparable<Contato> {
	private String nome, endereco, email, telefone;
	
	public Contato(String nome, String endereco, String email, String telefone) {
		this.nome = nome;
		this.endereco = endereco;
		this.email = email;
		this.telefone = telefone;
	}
	
	public abstract String getIdUnico();
	
	public String getNome() { return nome; }
	public String getEndereco() { return endereco; }
	public String getEmail() { return email; }
	public String getTelefone() { return telefone; }
	
	public abstract String getTipo();
	
	@Override
	public boolean equals(Object obj) {
		return (obj instanceof Contato)? ((Contato)obj).getIdUnico() == this.getIdUnico(): false;
	}
	
	@Override
	public String toString() {
		return String.format("[%s] -> ", getTipo()) +
				String.format("Nome: '%s' ", getNome()) +	
				String.format("Endereço: '%s' ", getEndereco()) +
				String.format("Email: '%s' ", getEmail()) +
				String.format("Telefone: '%s' ", getTelefone());
	}
	
	@Override
	public int compareTo(Contato o) {
		//Na ordenação, é necessário distinguir o tipo de contato, além do id único.
		int compareTipo = this.getTipo().compareTo(o.getTipo());
		if (compareTipo == 0)
			return this.getIdUnico().compareTo(o.getIdUnico());
		else 
			return compareTipo;
				
	}
}
