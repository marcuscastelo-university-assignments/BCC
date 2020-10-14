package loja;

import java.io.IOException;

public class Main {
    private static Loja loja;

    public static void main(String[] args) throws IOException {
        loja = new Loja();
        int opcao;
        do {
            opcao = leOpcao();
            tratarOpcao(opcao);
        } while (opcao != 0);
    }

    private static void tratarOpcao(int opcao) throws IOException{
        Produto p;
        switch (opcao) {
            case 1: {
                int codBar, quantidade;
                String nome;
                System.out.println("Adicionando um novo CD...");

                System.out.println("Digite o codBars:");
                codBar = EntradaTeclado.leInt();
                System.out.println("Digite o nome:");
                nome = EntradaTeclado.leString();
                System.out.println("Digite a quantidade:");
                quantidade = EntradaTeclado.leInt();

                p = new CD(codBar, nome, quantidade);
                loja.addProdutos(p);

                System.out.println("CD adicionado!");
                break;
            }
            case 2: {
                int codBar, quantidade;
                String nome;
                System.out.println("Adicionando um novo DVD...");

                System.out.println("Digite o codBars:");
                codBar = EntradaTeclado.leInt();
                System.out.println("Digite o nome:");
                nome = EntradaTeclado.leString();
                System.out.println("Digite a quantidade:");
                quantidade = EntradaTeclado.leInt();

                p = new DVD(codBar, nome, quantidade);
                loja.addProdutos(p);

                System.out.println("DVD adicionado!");
                break;
            }
            case 3: {
                int codBar, quantidade;
                String nome;
                System.out.println("Adicionando um novo Livro...");

                System.out.println("Digite o codBars:");
                codBar = EntradaTeclado.leInt();
                System.out.println("Digite o nome:");
                nome = EntradaTeclado.leString();
                System.out.println("Digite a quantidade:");
                quantidade = EntradaTeclado.leInt();

                p = new Livro(codBar, nome, quantidade);
                loja.addProdutos(p);

                System.out.println("Livro adicionado!");
                break;
            }
            case 4: {
                System.out.println("Verificando estoque...");
                loja.verificarEstoque();
                break;
            }
            case 5: {
                int codBars;
                System.out.println("A vender um produto...");
                System.out.println("Digite o código de barras do produto:");
                codBars = EntradaTeclado.leInt();

                try {
                    loja.venderProduto(codBars);
                    System.out.println("Produto vendido com sucesso!");
                } catch (RuntimeException e) {
                    System.out.println("O produto não está em estoque");
                }
                break;
            }
            case 6: {
                int codBars;
                System.out.println("A buscar um produto...");
                System.out.println("Digite o código de barras do produto:");
                codBars = EntradaTeclado.leInt();
                p = loja.buscarProduto(codBars);
                if (p==null) {
                    System.out.println("O produto informado não está cadastrado");
                } else System.out.println(p);
            }
            case 7: {
                String nome;
                System.out.println("A buscar um produto...");
                System.out.println("Digite o nome do produto:");
                nome = EntradaTeclado.leString();
                p = loja.buscarProduto(nome);
                if (p==null) {
                    System.out.println("O produto informado não está cadastrado");
                } else System.out.println(p);
            }
        }
    }

    private static int leOpcao() throws IOException {
        while (true) {
            try {
                System.out.println("Digite a opção [1-7]");
                return EntradaTeclado.leInt();
            } catch (Exception e) {}
        }
    }
}
