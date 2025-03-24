CREATE TABLE account
(
	id INTEGER PRIMARY KEY
	name VARCHAR(255),
	login VARCHAR(255),
	password VARCHAR(255)
);

--1° abordagem : Criar uma nova tabela

--EBNF : 

CREATE TABLE <nome>
(
	[<SELECTION> -- você quer criar uma nova tabela com base em outra
	FROM <TABLE>]
);

SELECTION ::= {<parameter> [AS <alias>][,]}

--IMPLEMENTAÇÃO

CREATE TABLE account_encyprt AS

SELECT
	id,
	pwd,
	MD5(pwd) AS MD5_encrypted_pwds
FROM
	account;


--2° abordagem : fazer um select
--(Essa foi aceita)

SELECT
	id,
	password,
	MD5(password) AS MD5 -- this is a new line
FROM
	account;
