
Old: 

a) Na descrição textual, não há restrição para o número de projetos que um empregado específico pode realizar. Isso é refletido no banco por meio da chave primária composta (CPF, Projeto) na tabela Empregado. Infelizmente, essa abordagem causa a replicação de dados do Empregado para cada projeto novo que ele participar, podendo causar anomalias de inserção. Por exemplo, se o mesmo empregado (CPF = "123-45) faz parte de dois projetos e é inserido duas vezes, nada garante que, na segunda inserção, todos campo seja inseridos de forma a condizer com a primeira inserção. Sendo assim, para um mesmo CPF, dois nomes, endereços, categorias, etc. diferentes podem ser cadastrados. Nesses casos, é impossível determinar qual das informações é a correta. Pelo mesmo argumento, também podem haver anomalias de atualização caso, por exemplo, a aplicação faça uma abordagem superficial e altere o nome de apenas um dos registros com o CPF especificado.

Outro ponto, ainda na tabela Empregado é a existência de informações não relacionadas diretamente ao funcionário sendo armazenadas de forma "casada" com os funcionários.
Suponha os seguinte cenários:
	1. Deseja-se criar um departamento vazio (sem funcionários)
	2. Deseja-se remover um departamento
	3. Deseja-se atualizar o chefe de um departamento.

Em 1., é simplesmente impossível fazê-lo, já que todas as inserções requerem um funcionário como chave.
Em 2., a remoção de um departamento implica na remoção de todos os funcionários da tabela ou na definição de diversos nulos na tabela nos campos de depto (o que viola uma dependencia funcional transitiva: Funcionario -> Departamento). A primeira opção é inviável e a segunda nem categoriza, de fato, uma remoção, além de ser cara e gastar espaço.
Em 3., será necessário percorrer todos os registros de Empregado, um a um, atualizando todos os chefes de um departamento específico. Mais uma vez um processo caro.
Em todos os casos acima, os mesmos argumentos de anomalias de inserção e atualização se aplicam, caso não haja tratamento em nível de aplicação, podendo gerar mais de um chefe por departamento, departamentos sem chefe e funcionários sem departamento.

Na tabela de Projeto, é definido como chave primária o código do projeto, o que representa corretamente a semântica do problema e suas dependências funcionais. A tabela Empregado possui uma chave estrangeira para esse código do projeto. Levando em conta que cada entrada da tabela Empregado é, na verdade, uma instância do mesmo empregado em um dado projeto, a aplicação de chave estrangeira está correta. O problema dessa tabela está no campo CodigoDepto não ser uma chave estrangeira, o que faz com que tuplas ilegítimas possam ser formadas, conforme comentado abaixo.

O campo CodigoDepto não é chave nem na tabela Empregado nem na tabela Projeto, permitindo que a junção dessas tabelas gere tuplas ilegítimas. Por exemplo, imaginando duas tuplas:
	empregadoX = ("Zé", "123", ..., CodigoDepto=1, ..., Projeto=10)
	empregadoY = ("Zé", "123", ..., CodigoDepto=2, ..., Projeto=2)
Quando for feita uma junção das tabelas Projeto e Empregado, 


Tuplas ilegítimas .......



A replicação de dados apresentada acima mostra-se um ponto de extrema vulnerabilidade do banco de dados para inconsistências, além de gastar espaço armazenando informações repetidas. Portanto ...........




















Chute sem teoria:


Funcionario = {Nome, Atividade, Departamento}

Atividade = {Titulo, Categoria}

Departamento = {Nome, Chefe, Categoria}

in Atividades:
	("programador", "TI")
	("analista de dados", "TI")

Projeto = {Título, Categoria}

MembrosProjeto = {TituloProjeto, NomeFunc}


