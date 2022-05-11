/*
	SCC 0240 - Bases de Dados (2021, Turma 01)
	Exercício Individual 03

	Marcus Vinicius Castelo Branco Martins
	nUSP: 11219237
*/


-- 1.
SELECT T.nome, T.estado 
FROM Uniforme U 
  INNER JOIN Time T ON T.nome = U.time
WHERE 
	U.tipo = 'TITULAR' 
	AND 
	U.cor_principal IS NULL;

-- 2.
SELECT J.nome, J.data_nasc, J.time, T.estado, P.data, P.local
FROM
	Jogador J
	INNER JOIN Time T ON J.time = T.nome
	LEFT JOIN Joga Ja ON
		(JA.classico = 'S')
		AND
		(Ja.time1 = T.nome OR Ja.time2 = T.nome)
	LEFT JOIN Partida P ON
		P.time1 = Ja.time1 AND P.time2 = Ja.time2
;

-- 3.
SELECT COUNT(*) AS quantidade FROM Partida P
WHERE EXTRACT(MONTH FROM P.data) IN (1, 2);

-- 4.
SELECT EXTRACT(MONTH FROM P.data) AS mes, COUNT(*) AS quantidade FROM Joga Ja, Partida P
WHERE 
	EXTRACT(YEAR FROM P.data) = '2018'
	Ja.time1 = P.time1 AND Ja.time2 = P.time2
GROUP BY EXTRACT(MONTH FROM P.data)
ORDER BY COUNT(*) DESC

-- 5.
SELECT T.nome, T.estado, T.saldo_gols, EXTRACT(YEAR FROM P.data) AS ano, COUNT(*) AS jogos_por_ano
FROM Time T, Partida P, Joga Ja
WHERE
	Ja.classico = 'S'
	AND
	(T.nome = Ja.time1 OR T.nome = Ja.time2)
	AND
	(Ja.time1 = P.time1 AND Ja.time2 = P.time2 )
GROUP BY T.nome, T.estado, T.saldo_gols, EXTRACT(YEAR FROM P.data);

-- 6.
SELECT T.nome FROM Time T, Partida P, Joga Ja
WHERE (
	T.tipo = 'PROFISSIONAL'
	AND
	Ja.classico = 'S'
	AND
	(Ja.time1 = P.time1 AND Ja.time2 = P.time2)
	AND
	(
		(P.time1 = T.nome AND P.placar LIKE '0X%')
		OR
		(P.time2 = T.nome AND P.placar LIKE '%X0')
	)
)
GROUP BY T.nome
HAVING COUNT(*) >= 2;


-- 7.
SELECT T.estado, T.tipo, COUNT(*) AS quantidade, AVG(T.saldo_gols) AS media_gols
FROM Time T
GROUP BY T.estado, T.tipo
ORDER BY T.estado, T.tipo;

-- 8.
SELECT Ja.time1, Ja.time2, COUNT(*) AS confrontos
FROM Joga Ja, Partida P
WHERE 
	Ja.classico = 'S' AND
	Ja.time1 = P.time1 AND Ja.time2 = P.time2
GROUP BY Ja.time1, Ja.time2;

-- 9.
SELECT T.nome 
FROM Time T 
WHERE 
(
  T.estado = 'SP'
  AND
  NOT EXISTS
  (
      (
          SELECT P.local FROM Partida P
          WHERE P.time1 = 'Santos' or P.time2 = 'Santos'
      )
      MINUS
      (
          SELECT P.local FROM Partida P
          WHERE (P.time1 = T.nome OR P.time2 = T.nome) 
      )      
  )
)

-- 10.
-- OBS: caso dois times do mesmo estado tenham o mesmo saldo de gols X
-- e X seja o menor saldo do estado, o time escolhido é o
-- primeiro em ordem alfabética ( MIN(T.nome) )
-- Se a ideia for mostrar mais de um time por estado nesse caso de empate,
-- basta trocar MIN(T.nome) por T.nome e remover a última cláusula GROUP BY.
-- Isso permitirá mais de uma tupla por estado
SELECT MIN(T.nome) AS time , T.estado, T.saldo_gols 
FROM 
  Time T
  INNER JOIN
  (
    SELECT Tinn.estado, MIN(Tinn.saldo_gols) AS min_saldo 
    FROM Time Tinn
    GROUP BY Tinn.estado
   ) MINT
  ON T.estado = MINT.estado AND T.saldo_gols = MINT.min_saldo
GROUP BY T.estado, T.saldo_gols;