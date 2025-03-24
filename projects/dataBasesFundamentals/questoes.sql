/*
Disclaimer : algumas vezes eu citei o governador de um estado na questões, mas só foi pra ilustrar, qualquer semelhança com
a realidade é mera coincidência

As 4 questões que usam funções de agragação e agrupamento são as 4 primeiras:

1- O governador do estado quer saber  o salário de cada enfermeiro do menor ao maior(reza a lenda que ele quer dar um bônus extra a eles). No entanto, por alguma razão,
ele requere que você multiple o salário do enfermeiro por 2 depois divida ele por dois ... políticos e burocrácia !

2- Depois de o governador do estado ter dado um bônus aos enfermeiros, os medicos ficaram muito chateados de não terem recebido um bônus também,
então ele está estudando a possibilidade de bonificá-los também, para tanto, ele quer que você liste os salários de todos o médicos
adotando aquela mesma metodologia estranha, mas dessa vez do maior para o menor !

3- O governador do estado acaba de torrar todo o dinheiro dos cofres públicos com o bônus dos médicos e enfermeiros, agora ele quer saber
qual a média salarial dos médicos e enfermeiros do hospital para estudar a possibilidade de diminuir o salário deles por um tempo, ordene
as médias de maior para menor

4 - O governador do estado estado está pensando em dar um prémio honorífico (medalhas de ouro)para os médicos que tem doutorado, pois eles são os únicos médicos que
podem ser chamados de doutores. No entanto, depois da crise econômico gerada pela bonificação de salários dos funcionários do hospital, ele só tem
dinheiro o bastante para confeccionar 3 medalhas, mas há um problema : há 4 doutores no hospital ! Então ele precisa da sua ajuda para selecionar
os 3 doutores que tenha o nome lexigraficamente menor. Retorne o CPF e o nome completo desses médicos. 

5- As autoridades competentes tem muito interesse em saber os CPF's dos pacientes que marcaram consulta e estão internados, faça isso ou será demitido !

6- As autoridades competentes querem saber qual o nome do médico que marcou a consulta do paciente com CPF 123.456.789-12 e tem afiliação no "Conselho Federal de Medicina"

7 - Por alguma razão as autoridades competentes querem descobrir qual é o nome do enfermeiro que tem número de celular "+55 89 9 1234-5678" e avaliou a recuperação do paciente do CPF "123.456.789-12"

8 - É necessário saber o nome do paciente que é alérgico a "Frutos do mar" e está internado na enfermaria (só tem um que se enquadra)

9 - Qual o CPF do enfermeiro que gerencia a enfermaria e avaliou a recuperação do paciente com CPF "233.567.891-23"
(o ID da hotelaria é 1, além de o enfermeiro poder gereciá-la em qualquer horário) ?

10 - Os médicos nunca viram algo parecido, mas o cancêr no estomago do paciente Louis de la Rois está avançando rapidamente. No entanto, o paciente continau calmo
e risonho - o sorriso de uma pessoa que parece não ter remorssos na vida. Ele só tem um único desejo e quer que você o cumpra :
Saber quantos pacientes tem alergia a paracetamal, marcaram consulta com o médico de CPF "456.789.123-98" e estão internados na enfermaria ... não tem muito a ver com a situação dele, mas dá muita pena em negar
o último desejo de um moribundo, então é necessário ajudar ele. Obs.: Lembre-se que o id da enferemaria é 2.
*/

--1
 
SELECT ((2*enfermeiro.salario_enf)/2) AS enfSalario
FROM enfermeiro
ORDER BY enfSalario ASC;

--2

SELECT ((2*medico.salario_med)/2) AS medSalario
FROM medico
ORDER BY medSalario DESC;

--3

SELECT salarios_medios
FROM 
    (SELECT AVG(salario_med) AS salarios_medios FROM medico
    UNION ALL
    SELECT AVG (salario_enf) AS salarios_medios FROM enfermeiro) AS subQuery
ORDER BY salarios_medios DESC;

--4
SELECT medico.CPF_med, (medico.nome_med || ' ' || medico.sobrenome_med) AS nome_completo
FROM medico
WHERE medico.grau_especializacao_med = 'Doutorado'
ORDER BY nome_completo ASC
LIMIT 3;

--5
SELECT paciente.CPF_pac
FROM paciente
INNER JOIN marcar_consulta ON paciente.CPF_pac = marcar_consulta.id_pac
INNER JOIN estar_internado ON paciente.CPF_pac = estar_internado.id_pac;

--6
SELECT (medico.nome_med || ' ' || medico.sobrenome_med) AS nome_completo_medico
FROM medico
INNER JOIN marcar_consulta ON medico.CPF_med = marcar_consulta.id_med
INNER JOIN medico_afiliacao ON medico.CPF_med = medico_afiliacao.id_med
WHERE marcar_consulta.id_pac = '123.456.789-12'
AND medico_afiliacao.med_espec = 'Conselho Federal de Medicina';

--7
SELECT ((2*enfermeiro.salario_enf)/2) AS enfSalario
FROM enfermeiro
ORDER BY enfSalario ASC;

--8
SELECT (paciente.nome_pac || ' ' || paciente.sobrenome_pac) AS paciente_alergico
FROM paciente
INNER JOIN estar_internado ON paciente.CPF_pac = estar_internado.id_pac
INNER JOIN paciente_alergias ON paciente.CPF_pac = paciente_alergias.id_pac
WHERE paciente_alergias.alergia = 'Frutos do mar';

--9
SELECT enfermeiro.CPF_enf
FROM enfermeiro
INNER JOIN gerenciar_hotelaria ON enfermeiro.CPF_enf = gerenciar_hotelaria.id_enf
INNER JOIN avaliar_recuperacao ON enfermeiro.CPF_enf = avaliar_recuperacao.id_enf
WHERE avaliar_recuperacao.id_pac = '233.567.891-23'
AND gerenciar_hotelaria.id_hotelaria = 1;

--10

SELECT COUNT(paciente_alergias.alergia) AS quant_paciente_categoricos
FROM paciente_alergias
INNER JOIN marcar_consulta ON paciente_alergias.id_pac = marcar_consulta.id_pac
INNER JOIN estar_internado ON paciente_alergias.id_pac = estar_internado.id_pac 
WHERE paciente_alergias.alergia = 'Paracetamol'
AND marcar_consulta.id_med = '456.789.123-98'
AND estar_internado.id_hotelaria = 2;