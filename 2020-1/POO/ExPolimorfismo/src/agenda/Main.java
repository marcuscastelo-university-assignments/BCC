package agenda;

import java.io.IOException;

public class Main {
    private static Agenda agenda;

    public static void main(String[] args) throws IOException {
        agenda = new Agenda();

        int opcao;
        do {
            opcao = leOpcao();
            tratarOpcao(opcao);
        } while (opcao != 0);
    }

    private static void tratarOpcao(int opcao) throws IOException{
        switch (opcao) {
            case 1: {
                String nome,end,email,tel,cpf,datnas,estciv;
                System.out.println("Adicionando um novo contato de pessoa física...");

                System.out.println("Digite o nome:");
                nome = EntradaTeclado.leString();
                System.out.println("Digite o endereco:");
                end = EntradaTeclado.leString();
                System.out.println("Digite o email:");
                email = EntradaTeclado.leString();
                System.out.println("Digite o telefone:");
                tel = EntradaTeclado.leString();
                System.out.println("Digite o CPF:");
                cpf = EntradaTeclado.leString();
                System.out.println("Digite a data de nascimento:");
                datnas = EntradaTeclado.leString();
                System.out.println("Digite o estado civil:");
                estciv = EntradaTeclado.leString();

                System.out.println("Adicionando um novo contato...");

                agenda.adicionarContatos(new ContatoPF(nome,end,email,tel,cpf,datnas,estciv));
                System.out.println("Contato adicionado!");
                break;}
            case 2: {
                String nome, end, email, tel, cnpj, insc, raz;
                System.out.println("Adicionando um novo contato de pessoa jurídica...");

                System.out.println("Digite o nome:");
                nome = EntradaTeclado.leString();
                System.out.println("Digite o endereco:");
                end = EntradaTeclado.leString();
                System.out.println("Digite o email:");
                email = EntradaTeclado.leString();
                System.out.println("Digite o telefone:");
                tel = EntradaTeclado.leString();
                System.out.println("Digite o CNPJ:");
                cnpj = EntradaTeclado.leString();
                System.out.println("Digite a inscrição:");
                insc = EntradaTeclado.leString();
                System.out.println("Digite a razão social:");
                raz = EntradaTeclado.leString();

                System.out.println("Adicionando um novo contato...");
                agenda.adicionarContatos(new ContatoPJ(nome, end, email, tel, cnpj, insc, raz));
                System.out.println("Contato adicionado!");
                break;
            }
            case 3: {
                System.out.println("Exibindo todos os contatos...");
                System.out.println(agenda.listarTodosOsContatos());
                break;
            }
            case 4: {
                System.out.println("Ordenando os contatos...");
                agenda.ordenarContatos();
                System.out.println("Ordenados com sucesso!");
                break;
            }
            case 5: {
                String CPX;
                System.out.println("A remover um contato...");
                System.out.println("Digite o CPF/CNPJ do contato a ser removido: ");
                CPX = EntradaTeclado.leString();
                agenda.removerContato(CPX);
                System.out.println("Contato removido com sucesso!");
                break;
            }
            case 6: {
                String CPX;
                System.out.println("A pesquisar contato...");
                System.out.println("Digite o CPF/CNPJ a ser buscado: ");
                CPX = EntradaTeclado.leString();
                Contato c = agenda.pesquisarContato(CPX);
                if (c == null) System.out.println("Contato não encontrado!");
                else System.out.println(c);
            }
        }
    }

    private static int leOpcao() throws IOException {
        while (true) {
            try {
                System.out.println("Digite a opção [1-6]");
                return loja.EntradaTeclado.leInt();
            } catch (Exception e) {}
        }
    }
}
