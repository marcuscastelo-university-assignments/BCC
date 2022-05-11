# [SCC0240] Exercício 2 - Normalização

Nome: Marcus Vinicius Castelo Branco Martins \
nUSP: 11219237

## Observações iniciais

### Interpretação

Analisando a descrição do problema, houve uma certa ambiguidade na semântica entre $Categoria$ e $Departamento$. Durante o exercício, supos-se que um departamento tem seu código único e é responsável por uma categoria (tanto de atividades quanto de projetos). Por exemplo, o departamento de código 2 tem categoria TI e, por isso, será responsável por todos os projetos da categoria de TI e todos os funcionários cujas atividades sejam da categoria de TI estarão associados a este departamento. Note que o nome do departamento não tem relação com sua categoria nessa interpretação.


### Comentários

Na descrição apresentada, não foi definida a natureza das relações do chefe de departamento. Portanto, o campo será tratado como uma simples string, sem qualquer restrição.

Caso houvesse uma descrição mais detalhada do relacionamento do $Chefe$ com os empregados ou com seu departamento, valeria a pena tratá-lo como uma entidade dedicada, mas dada a semântica descrita, decidiu-se mantê-lo como uma simples string.

# Resolução:

## Item A: Análise Informal
Quanto à análise informal, o projeto apresentado apresenta problemas:

1. As tabelas não estão refletindo a semântica do problema.
	A tabela **Empregado** apresenta campos não relacionados ao empregado: ${Categoria}$, ${ChefeDepto}$ e ${NomeDepto}$. \
	OBS: $Projeto$, apesar de ser relacionado ao empregado e permitir um tipo de relacionamento múltiplo ao ser parte da chave, está feito de forma incorreta, como discutido mais a frente. \
	OBS 2: ${CodigoDepto}$, apesar de se referir ao departamento e não ao empregado diretamente, é da semântica do empregado, pois ele trabalha em um departamento, o que exige uma referência ao departamento.

	Seguindo a descrição à risca, a tabela **Projeto** também possui um campo fora de sua semântica: o campo ${CodigoDepto}$. Isso se deve ao fato de que um projeto nunca é diretamente associado a um departamento, mas sim a uma $Categoria$. Na descrição, o exemplo dado foi o de um projeto de categoria "TI", que seria atribuído ao departamento de "TI".
	Não ficou muito claro o que é exatamente a categoria no geral, portanto segue-se a definição apresentada na introdução deste documento.

2. Presença ou necessidade de valores nulos em certas ocasiões:
	Não há nenhuma indicação de _not null_ nas tabelas apresentadas, o que permite o cadastro de diversas tuplas sem significado algum.
	Além disso, nada impede a violação destas restricões:
	1. Tabela Empregado:
		1. Todo empregado deve pertencer a um departamento
		1. Todo empregado deve realizar uma atividade
		1. Toda atividade deve ter uma categoria.
		1. Todo empregado deve ter suas informações (Nome, DataNasc, Endereço), ou pelo menos parte delas, não nulas (a ser determinado com o cliente).
		1. Todo departamento deve ter um chefe e um nome.
	1. Tabela Projeto:
		1. Todo departamento deve ter uma categoria
		1. Todo projeto deve estar relacionado a um departamento por meio de sua categoria (categoria not null).
		1. Todo projeto deve ter um nome.
	
3. Anomalias:
	- Inserção:
		1. Tabela Empregado:
			- Inserir a mesma atividade com categorias diferentes: viola restrições
			- Inserir o mesmo projeto com departamentos diferentes (mudando o CPF): viola restrições
			- Inserir o mesmo CPF duas vezes, trocando o projeto e outro campo (e.g. DataNasc): inconsistência de dados
			- Inserir dois empregados quaisquer com o mesmo CodigoDepto, mas com ChefeDepto ou NomeDepto inconsistentes
			- É obrigatório inserir o empregado já atrelado a um projeto.
		2. Tabela Projeto:
			- Inserir dois projetos com o mesmo CodigoDepto e Categorias diferentes: viola a restrição de que um depto tem apenas uma categoria.
	- Atualização:
		1. Tabela Empregado:
			- Se a atualização do campos ${ChefeDepto}$, ${NomeDepto}$ for feita de maneira parcial, gera inconsistência (devem ser os mesmos dado ${CodigoDepto}$).
			- Se a atualização dos campos ${Nome}$, ${DataNasc}$, ${Endereço}$, ${Atividade}$ for feita de maneira parcial, gera inconsistência (devem ser os mesmos dado um par {${CPF}$, ${Projeto}$}).
			- Se a atualização do campo ${Categoria}$ for feita de maneira parcial, gera inconsistência (deve ser o mesmo dada ${Atividade}$.
		2. Tabela Projeto:
			a. Se a atualização do campo ${Categoria}$ não acompanhar as atualizações feitas na tabela **Empregado** ou não for aplicada a todos os registros que possuirem o mesmo CodigoDepto, gera inconsistência.
	- Remoção:
		1. Tabela Empregado:
			- Ao remover todos os projetos de um empregado, são perdidas todas as informações do empregado.
			- Ao remover um certo departamento, todos os empregado daquele departamento também são perdidos.
			- Ao remover todos os empregado que exercem uma dada atividade, a atividade acaba sendo perdida.
		2. Tabela Projeto:
			- Ao remover todos os projetos de um determinado departamento, perde-se a informação da categoria do departamento.
	 - Tuplas ilegítimas: Por causa de todas essas anomalias apresentadas, é possível que certas consultas feitas ao banco gerem tuplas ilegítimas, isto é, tuplas que trazem lixo em seus campos. Isso occore porque o banco não está impondo as regras que a semântica do problema exige para manter as informações consistentes. Alguns exemplos de operações que gerariam tuplas ilegítimas são estes:
		1. Registrar dois projetos para um empregado e, na segunda inserção, trocar qualquer um dos campos.
		1. Registrar um projeto com um departamento e uma categoria e depois registrar um funcionário desse mesmo departamento e outra categoria.
		1. Registrar dois funcionários do mesmo departamento e trocar um dos campos relacionados ao departamento (NomeDepto ou ChefeDepto).


Além das anomalias acima descritas, vale ressaltar a enorme ineficiência no armazenamento de dados do projeto de banco atual. Segue um exemplo do pior caso de replicação de dados sem motivo: Inserir $n$ registros de projeto para o mesmo empregado: resulta na cópia de **todos** os outros campos $n$ vezes. Além desse há diversos outros casos de uso ineficiente de espaço que serão tratados na análise formal (Item B).

## Item B: Análise Formal

De acordo com as tabelas e a descrição dadas, é possível obter algumas informações sobre o problema:

Primeiramente, levanta-se os conceitos (entidades) referentes ao problema:

Um **empregado** é unicamente identificado por seu CPF. (${Projeto}$ está presente como chave apenas para permitir que um empregado participe de mais de um projeto, não há valor semântico).

Uma **Atividade** é unicamente identificada pelo seu ${Titulo}$. 

Um **Projeto** é unicamente identificado pelo seu ${CódigoProj}$.

Um **Departamento** é unicamente identificado pelo seu ${CodigoDepto}$.

Uma **Categoria** é apenas uma string. Não é possível duas strings iguais representarem duas categorias diferentes.

Além disso, analisa-se as dependências funcionais:

1. Referentes ao **empregado**:
	1. ${CPF}$ $\rightarrow$ ${Nome}$, ${DataNasc}$, ${Endereço}$, ${Atividade}$
	2. ${Atividade}$ $\rightarrow$ ${Categoria}$ (ver item 2)
	2. ${Categoria}$ $\rightarrow$ ${CodigoDepto}$ (ver item 4)
1. Referentes à **Atividade**:
	1. ${TituloAtividade}$ $\rightarrow$ ${Categoria}$
1. Referentes ao **Projeto**:
	1. ${CodigoProj}$ $\rightarrow$ ${NomeProj}$, ${Categoria}$
	2. ${NomeProj}$ $\rightarrow$ ${CodigoProj}$
	1. ${Categoria}$ $\rightarrow$ ${CodigoDepto}$ (ver item 4)
1. Referentes à **Categoria**:
	1. ${Categoria}$ $\rightarrow$ ${CodigoDepto}$
1. Referentes ao **Departamento**:
	1. ${CodigoDepto}$ $\rightarrow$ ${Chefe}$, ${Nome}$, ${Categoria}$

Em seguida, aplica-se as regras de normalização para determinar quais passos devem ser seguidos para tranformar as tabelas do banco na forma normal desejada.

## 1FN

A primeira forma normal já está atendida, pois todos os atributos são atômicos, ou seja, nenhum deles é multivalorado.

## 2FN

Para atender à segunda forma normal, deve-se primeiro levantar as chaves candidatas. Com as dependências funcionais acima, é trivial escolher a maioria: ${CPF}$ para **Funcinário** e ${CodigoProj}$ para **Projeto**.

### Tabela empregado

A tabela **empregado** está, atualmente, utilizando como chave composta os campos ${CPF}$ e ${Projeto}$, o que, segundo a segunda forma normal, está incorreto, como explicado a seguir:

Na tabela atual tem-se:
${CPF}$, ${Projeto}$ $\rightarrow$ ${Nome}$, ${DataNasc}$, ${Endereço}$, ${Atividade}$, ${Categoria}$, ${CodigoDepto}$, ${ChefeDepto}$, ${NomeDepto}$

A tabela não fere as dependências empregado apresentadas anteriormente, basta rearranjar os termos e usar transitividade:

Juntando:
1. ${CPF}$ $\rightarrow$ ${Nome}$, ${DataNasc}$, ${Endereço}$, ${Atividade}$
2. ${Atividade}$ $\rightarrow$ ${Categoria}$
2. ${Categoria}$ $\rightarrow$ ${CodigoDepto}$
1. ${CodigoDepto}$ $\rightarrow$ ${Chefe}$, ${Nome}$, ${Categoria}$

Obtêm-se: ${CPF}$ $\rightarrow$ ${Nome}$, ${DataNasc}$, ${Endereço}$, ${Atividade}$, ${Categoria}$, ${CodigoDepto}$, ${ChefeDepto}$, ${NomeDepto}$

Percebe-se que ${CPF}$ é suficiente para determinar todos os campos de **empregado**, exceto o próprio projeto. Além disso, apenas ${Projeto}$ não é suficiente para determinar todos os campos.

Desse modo, fica claro que ${Projeto}$ não é candidato a chave e, por isso, a tabela **empregado** deve ser modificada.

A vantagem de remover ${Projeto}$ da tabela **empregado** é a de minimizar a replicação de dados. Atualmente, um empregado que participa de $n$ projetos vai ter **todos** os seus campos (${CPF}$, ${Nome}$, ${DataNasc}$, ${Endereço}$, ${Atividade}$, ${Categoria}$, ${CodigoDepto}$, ${ChefeDepto}$, ${NomeDepto}$) replicados $n$ vezes, a fim de registrar a participação em um projeto. Além de ineficiente em termos de espaço ocupado, essa abordagem permite anomalias de inserção e de atualização.

Uma solução possível para esse problema é separar a relação de **empregado** participando em muitos **Projetos** por meio de uma tabela **EmpregadoProjeto**, que conteria apenas dois campos em cada registro: ${CPFFunc}$ e ${CodigoProj}$, ambos chave primária (para evitar a replicação de dados).

A desvantagem dessa abordagem é que agora é necessário fazer uma junção de tabelas sempre que se desejar saber as informações de um **empregado** que participa num dado **Projeto**, enquanto antes tudo estava na mesma tabela. Porém, levando em conta a quantidade de espaço economizado e de problemas evitados, é sim um pequeno preço a se pagar.


Com essa modificação, a segunda forma normal é atendida.

Até agora as tabelas estão assim (Versão 2NF):

**Empregado** = { $Nome$, $\underline{CPF}$, $DataNasc$, $Endereço$, $Atividade$, $Categoria$, $CodigoDepto$, $ChefeDepto$, $NomeDepto$}

**Projeto** = { $\underline{\underline{NomeProj}}$, $\underline{CodigoProj}$, $CodigoDepto$, $Categoria$ }

**EmpregadoProjeto** = { $\underline{CPF, CodigoProj}$ }

Mudanças: as consultas envolvendo dados do **empregado** não foram alteradas, mas caso se deseje consultar, por exemplo, o nome de todos os funcionários que trabalham no **projeto** $1$, é necessário fazer uma junção das tabelas **EmpregadoProjeto** e **Empregado**. No caso de uma consulta como "Listar o nome de todos os projetos de que o funcionário de nome $João$ participa", ainda é necessário fazer uma junção, mas agora em vez de juntar as tabelas **Empregado** e **Projeto**, junta-se as tabelas **EmpregadoProjeto** e **Projeto**. As demais consultas permanecem inalteradas.

### Tabela Projeto

Do mesmo modo, também é possível mesclar as dependências funcionais e formar uma só para a tabela **Projeto**:

Juntando:
1. ${CodigoProj}$ $\rightarrow$ ${NomeProj}$, ${Categoria}$
1. ${Categoria}$ $\rightarrow$ ${CodigoDepto}$

Obtém-se: $CodigoProj \rightarrow NomeProj, Categoria, CodigoDepto$.

Que é exatamente o que está definido na tabela apresentada. Portanto, a tabela **Projeto** já atende à segunda forma normal. Nota-se que há uma indicação de chave secundária no $NomeProjeto$. Isso indica a dependência funcional $NomeProjeto \rightarrow CodigoProj, Categoria$, e, por isso, $NomeProjeto$ também é uma chave candidata e poderia ter sido escolhida como chave da tabela. Essa escolha depende de qual dos campos é mais usado nas consultas, qual é menor em tamanho (facilita comparações), entre outras.

## 3FN

Quanto à terceira forma normal, é indicado que as tabelas não representem, em seus campos, dependências funcionais transitivas.

Na tabela **Empregado**, observa-se o uso de dependências funcionais transitivas.
 
A DF (Dependência Funcional) utilizada para escolher a chave na seção **2NF** foi esta:

${CPF}$ $\rightarrow$ ${Nome}$, ${DataNasc}$, ${Endereço}$, ${Atividade}$, ${Categoria}$, ${CodigoDepto}$, ${ChefeDepto}$, ${NomeDepto}$

Entretanto, essa dependência funcional foi criada apartir de regras de transitividade. Na verdade, a semântica apresentada na descrição do problema reflete nas seguintes regras:

1. ${CPF}$ $\rightarrow$ ${Nome}$, ${DataNasc}$, ${Endereço}$, ${Atividade}$
2. ${Atividade}$ $\rightarrow$ ${Categoria}$
2. ${Categoria}$ $\rightarrow$ ${CodigoDepto}$
1. ${CodigoDepto}$ $\rightarrow$ ${Chefe}$, ${Nome}$, ${Categoria}$

O mesmo vale para a tabela **Projeto**.
Revertendo a DF $CodigoProj \rightarrow NomeProj, Categoria, CodigoDepto$:

Tem-se
1. ${CodigoProj}$ $\rightarrow$ ${NomeProj}$, ${Categoria}$
1. ${Categoria}$ $\rightarrow$ ${CodigoDepto}$

Após a reversão das DFs, obtém-se esta lista de DFs:

1. ${CPF}$ $\rightarrow$ ${Nome}$, ${DataNasc}$, ${Endereço}$, ${Atividade}$
2. ${Atividade}$ $\rightarrow$ ${Categoria}$
2. ${Categoria}$ $\rightarrow$ ${CodigoDepto}$
1. ${CodigoDepto}$ $\rightarrow$ ${Chefe}$, ${Nome}$, ${Categoria}$
1. ${CodigoProj}$ $\rightarrow$ ${NomeProj}$, ${Categoria}$

Segundo a 3FN (Terceira forma normal), é necessário que haja tabelas para cada determinante de DF.

Desse modo, seriam criadas as seguintes tabelas:
1. **Empregado** = { $\underline{CPF}, Nome, DataNasc, Endereço, Atividade$ }
2. **Atividade** = { $\underline{Titulo}, Categoria$ }
4. **CategoriaDepto** = { $\underline{Categoria}, CodigoDepto$ }
3. **Departamento** = { $\underline{CodigoDepto}, Nome, Chefe$ }
3. **Projeto** = { $\underline{CodigoProj}, Nome, Categoria$ }

Porém, é possível simplificar o esquema a fim de diminuir a quantidade de tabelas e, consequentemente, de junções:

Basta remover a tabela **CategoriaDepto** e tornar $Categoria$ uma chave secundária de **Departamento** (vide interpretação descrita na introdução do exercício):

**Departamento** = { $\underline{CodigoDepto}, Nome, Chefe, \underline{\underline{Categoria}}$ }

Desse modo, todas as outras tabelas que usam o campo $Categoria$ devem o apontar como chave estrangeira à tabela **Departamento**.

Como o relacionamento entre a $Categoria$ e o $Departamento$ é de 1 para 1, não há desvantagem em unificar os campos dessa forma. A vantagem é a economia de junções, poupando um passo, além de diminuir o consumo de espaço que seria ocupado pelos $CodigoDepto$.

## 4 FN

Todas as dependências funcionais já são monovaloradas, dessa forma, não é necessário tomar nenhuma medida extra.

### Próximas formas normais

É possível ir além da quarta forma normal, mas quanto mais normalizado o banco, mais lento ele se torna, devido ao grande numero de checagens de consistência e de junções de tabelas. 

Na semântica apresentada, a quarta forma normal já cumpre os pontos críticos do sistema e garante um bom nível de consistência para o banco.

Portanto, a análise deste exercício vai se limitar à quarta forma normal.