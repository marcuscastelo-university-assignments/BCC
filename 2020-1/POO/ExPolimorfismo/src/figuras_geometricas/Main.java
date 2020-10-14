package figuras_geometricas;

import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        int opcao;
        do {
            opcao = leOpcao();
            tratarOpcao(opcao);
        } while (opcao != 0);
    }

    private static void tratarOpcao(int opcao) throws IOException{
        FiguraGeometrica fig;
        switch (opcao) {
            case 1: {
                System.out.println("Criando novo círculo...");
                System.out.println("A forma é preenchida? (s/N)");
                boolean filled = EntradaTeclado.leString().equalsIgnoreCase("s");
                System.out.println("Digite a cor:");
                String cor = EntradaTeclado.leString().toLowerCase();

                System.out.println("Digite o raio:");
                fig = new Circulo(cor,filled,(float)EntradaTeclado.leDouble());

                System.out.println("A área da figura é: " + fig.getArea());
                System.out.println("O perímetro da figura é: " + fig.getPerimetro());

                break;
            }
            case 2: {
                System.out.println("Criando novo círculo...");
                System.out.println("A forma é preenchida? (s/N)");
                boolean filled = EntradaTeclado.leString().equalsIgnoreCase("s");
                System.out.println("Digite a cor:");
                String cor = EntradaTeclado.leString().toLowerCase();

                System.out.println("Digite a base:");
                float base = (float)EntradaTeclado.leDouble();

                System.out.println("Digite a altura:");
                fig = new Retangulo(cor,filled, base, (float)EntradaTeclado.leDouble());

                System.out.println("A área da figura é: " + fig.getArea());
                System.out.println("O perímetro da figura é: " + fig.getPerimetro());
            }
            case 3: {
                System.out.println("Criando novo círculo...");
                System.out.println("A forma é preenchida? (s/N)");
                boolean filled = EntradaTeclado.leString().equalsIgnoreCase("s");
                System.out.println("Digite a cor:");
                String cor = EntradaTeclado.leString().toLowerCase();

                System.out.println("Digite o lado:");
                fig = new Quadrado(cor,filled,(float)EntradaTeclado.leDouble());

                System.out.println("A área da figura é: " + fig.getArea());
                System.out.println("O perímetro da figura é: " + fig.getPerimetro());
            }
        }
    }

    private static int leOpcao() throws IOException {
        while (true) {
            try {
                System.out.println("Digite a opção [1-3]");
                return loja.EntradaTeclado.leInt();
            } catch (Exception e) {}
        }
    }
}
