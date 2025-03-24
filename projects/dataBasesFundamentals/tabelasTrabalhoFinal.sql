DROP TABLE paciente, paciente_telefone_emergencia, paciente_telefone, paciente_alergias,
estar_internado, hotelaria_hospitalar, avaliar_recuperacao, enfermeiro, marcar_consulta,
enfermeiro_telefone, gerenciar_hotelaria, gerar_laudo, medico, estar_alocado, consultorio,
medico_telefone, medico_afiliacao CASCADE;

CREATE TABLE paciente(
	CPF_pac CHAR(14) PRIMARY KEY,
	nome_pac VARCHAR(30),
	sobrenome_pac VARCHAR(100),
	data_nascimento_pac DATE,
	genero_pac CHAR(1), 
	cidade_pac VARCHAR(100),
	bairro_pac VARCHAR(100),
	rua_pac VARCHAR(100),
	numero_casa_pac INTEGER,
	senha_pac TEXT,
	email_pac TEXT UNIQUE
);

--begin : atributos multivalorados de participante
CREATE TABLE paciente_telefone_emergencia
(
	id_pac CHAR(14),
	telefone_emergencia CHAR(18),
	FOREIGN KEY (id_pac) REFERENCES paciente(CPF_pac)
);

CREATE TABLE paciente_telefone
(
	id_pac CHAR(14),
	telefone_pac CHAR(18),
	FOREIGN KEY (id_pac) REFERENCES paciente(CPF_pac)
);

CREATE TABLE paciente_alergias
(
	id_pac CHAR(14),
	alergia TEXT,
	FOREIGN KEY (id_pac) REFERENCES paciente(CPF_pac)
);
--end : atributos multivalorados de participante

CREATE TABLE medico(
	CPF_med CHAR(14) PRIMARY KEY,
	nome_med VARCHAR(30),
	sobrenome_med VARCHAR(150),
	data_nascimento_med DATE,
	genero_med CHAR(1), -- 1 IS MALE and 0 female
	cidade_med VARCHAR(100),
	bairro_med VARCHAR(100),
	rua_med VARCHAR(100),
	numero_casa_med INTEGER,
	senha_med TEXT,
	email_med TEXT UNIQUE,
	especialidade_med TEXT,
	data_contratacao_med DATE,
	horarios_trabalho_med TEXT,
	grau_especializacao_med TEXT,
	salario_med DOUBLE PRECISION,
	dias_trabalho_med TEXT
);

CREATE TABLE medico_telefone
(
	id_med CHAR(14),
	telefone_med CHAR(18),
	FOREIGN KEY (id_med) REFERENCES medico(CPF_med)
);

CREATE TABLE medico_afiliacao
(
	id_med CHAR(14),
	med_espec VARCHAR(50),
	FOREIGN KEY (id_med) REFERENCES medico(CPF_med)
);

CREATE TABLE enfermeiro(
	CPF_enf CHAR(14) PRIMARY KEY,
	nome_enf VARCHAR(30),
	sobrenome_enf VARCHAR(150),
	data_nascimento_enf DATE,
	genero_enf CHAR(1), -- 1 IS MALE and 0 female
	cidade_enf VARCHAR(100),
	bairro_enf VARCHAR(100),
	rua_enf VARCHAR(100),
	numero_casa_enf INTEGER,
	senha_enf TEXT,
	email_enf TEXT UNIQUE,
	data_contratacao_enf DATE,
	horarios_trabalho_enf TEXT,
	grau_especializacao_enf TEXT,
	salario_enf DOUBLE PRECISION,
	dias_trabalho_enf TEXT
);

CREATE TABLE enfermeiro_telefone
(
	id_enf CHAR(14),
	telefone_enf CHAR(18),
	FOREIGN KEY (id_enf) REFERENCES enfermeiro(CPF_enf)
);

CREATE TABLE hotelaria_hospitalar(
	id_hotelaria SERIAL PRIMARY KEY,
	nome_hotelaria VARCHAR(50),
	total_leitos INTEGER
);

CREATE TABLE consultorio
(
	id_consultorio SERIAL PRIMARY KEY,
	especialidade_consultorio TEXT
);

--começo das relações

CREATE TABLE estar_internado
(
	id_pac CHAR(14), --é o cpf do paciente
	id_hotelaria INTEGER, --é o id da hotelaria 
	data_horario_internacao timestamp DEFAULT NOW(),
	FOREIGN KEY (id_pac) REFERENCES paciente(CPF_pac),
	FOREIGN KEY (id_hotelaria) REFERENCES hotelaria_hospitalar(id_hotelaria)
);

CREATE TABLE estar_alocado(
	id_med CHAR(14),
	id_consultorio INTEGER,
	FOREIGN KEY (id_med) REFERENCES medico(CPF_med),
	FOREIGN KEY (id_consultorio) REFERENCES consultorio(id_consultorio)
);

CREATE TABLE gerenciar_hotelaria
(
	id_enf CHAR(14),
	id_hotelaria INTEGER,
	data_gerencia VARCHAR(50),
	horario_gerencia_inic TIME,
	horario_gerencia_fim TIME,
	FOREIGN KEY (id_enf) REFERENCES enfermeiro(CPF_enf),
	FOREIGN KEY (id_hotelaria) REFERENCES hotelaria_hospitalar(id_hotelaria)
);

CREATE TABLE marcar_consulta
(
	id_pac CHAR(14),
	id_med CHAR(14),
	data_consulta DATE,
	horario_consulta TIME,
	FOREIGN KEY (id_pac) REFERENCES paciente(CPF_pac),
	FOREIGN KEY (id_med) REFERENCES medico(CPF_med)
);

CREATE TABLE avaliar_recuperacao
(
	id_pac CHAR(14),
	id_enf CHAR(14),
	descricao_recuperacao TEXT,
	FOREIGN KEY (id_pac) REFERENCES paciente(CPF_pac),
	FOREIGN KEY (id_enf) REFERENCES enfermeiro(CPF_enf)
);

CREATE TABLE gerar_laudo(
	id_pac CHAR(14),
	id_med CHAR(14),
	diagnostico TEXT,
	prognostico TEXT,
	tratamento TEXT,
	data_emissao timestamp DEFAULT NOW(),
	FOREIGN KEY (id_pac) REFERENCES paciente(CPF_pac),
	FOREIGN KEY (id_med) REFERENCES medico(CPF_med)
);
