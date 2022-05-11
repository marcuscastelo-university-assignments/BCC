Após a reversão das DFs, obtém-se esta lista de DFs:

1. ${CPF} \rightarrow {Nome}, {DataNasc}, {Endereço}, {Atividade}$
2. ${Atividade} \rightarrow {Categoria}$
2. ${Categoria} \rightarrow {CodigoDepto}$
1. ${CodigoDepto} \rightarrow {Chefe}, {Nome}, {Categoria}$
1. ${CodigoProj} \rightarrow {NomeProj}, {Categoria}$
1. ${Categoria} \rightarrow {CodigoDepto}$

Segundo a 3FN (Terceira forma normal), é necessário que haja tabelas para cada determinante de DF.

Desse modo, seriam criadas as seguintes tabelas:

1. **Empregado** = { $ \underline{CPF} ,$}
2. **Atividade** com chave $Titulo$