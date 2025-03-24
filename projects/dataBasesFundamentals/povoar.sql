--INSERTION PACIENTES
INSERT INTO paciente(CPF_pac, nome_pac, sobrenome_pac, data_nascimento_pac,genero_pac,cidade_pac,bairro_pac,rua_pac,numero_casa_pac,senha_pac,email_pac)
VALUES
    ('123.456.789-12', 'Ricardo', 'Silva', '2000-01-01', 'M', 'Recife', 'Madalena', 'Rua dos probres', 20, 'esperanca8Hope', 'richardHeartLion@gmail.com'),
    ('234.567.891-23', 'Godofredo', 'Santos', '2000-01-02', 'M', 'Recife', 'Santo Amaro', 'Vigílio de Medeiros', 22, 'vamosLa4', 'vigilioMedeirosOndeVivo@gmail.com'),
    ('122.456.789-12', 'Boemundo', 'Oliveira', '1999-01-01', 'M', 'Rio de Janeiro', 'Copacabana', 'Avenida Atlântica', 123, 'Jerusalem1099', 'boemundo1@gmail.com'),
    ('233.567.891-23', 'Tancredo', 'Ferreira', '1989-01-01', 'M', 'São Paulo', 'Jardim Paulista', 'Avenida Paulista', 456, 'Crusader1050', 'tancredo@outlook.com'),
    ('345.678.912-34', 'Balduíno', 'Gonçalves', '1998-01-01', 'M', 'Jerusalem', 'Old City', 'Via Dolorosa', 789, 'HolyLand1120', 'balduino@hotmail.com'),
    ('456.789.123-45', 'Raimunda', 'Rodrigues', '1997-01-01', 'F', 'Toulouse', 'Saint-Cyprien', 'Rue du Taur', 234, 'Toulouse1130', 'raimundo4@gmail.com'),
    ('567.891.234-56', 'Luisa', 'Martins', '1996-01-01', 'F', 'Paris', 'Marais', 'Rue de Rivoli', 567, 'Paris1080', 'luis7@outlook.com'),
    ('678.912.345-67', 'André', 'Pereira', '1995-01-01', 'M', 'Budapest', 'Castle District', 'Fishermans Bastion', 890, 'Hungarian1060', 'andre2@hotmail.com'),
    ('789.123.456-78', 'Raimundo', 'Mendes', '1994-01-01', 'M', 'Poitiers', 'Centre-Ville', 'Rue de la Chaîne', 345, 'Poitiers1070', 'raimundo7@gmail.com'),
    ('890.234.567-89', 'Louis', 'de la Roi', '1993-01-01', 'M', 'City8', 'Neighborhood8', 'Street8', 8, 'Crusade1040', 'another8@outlook.com');

    --telefones dos pacientes

INSERT INTO paciente_telefone(id_pac, telefone_pac)
VALUES
('123.456.789-12', '+55 88 9 1234-5678'),
('123.456.789-12', '+55 88 9 9876-5433'),
('234.567.891-23', '+55 88 9 2345-6799'),
('234.567.891-23', '+55 88 9 8765-4324'),
('345.678.912-34', '+55 88 9 3456-7890'),
('345.678.912-34', '+55 88 9 8907-6543'),
('456.789.123-45', '+55 88 9 4567-8901'),
('456.789.123-45', '+55 88 9 9012-3459'),
('567.891.234-56', '+55 88 9 5678-9013'),
('567.891.234-56', '+55 88 9 9012-3454'),
('678.912.345-67', '+55 88 9 6789-0123'),
('678.912.345-67', '+55 88 9 0123-4567'),
('789.123.456-78', '+55 88 9 7890-1234'),
('789.123.456-78', '+55 88 9 1234-5677'),
('890.234.567-89', '+55 88 9 8901-2345'),
('890.234.567-89', '+55 88 9 2345-6789');


    --telefones de emergencia dos pacientes

INSERT INTO paciente_telefone_emergencia(id_pac, telefone_emergencia)
VALUES
('123.456.789-12', '+55 88 9 1111-1111'),
('123.456.789-12', '+55 88 9 2222-2222'),
('234.567.891-23', '+55 88 9 3333-3333'),
('234.567.891-23', '+55 88 9 4444-4444'),
('345.678.912-34', '+55 88 9 5555-5555'),
('345.678.912-34', '+55 88 9 6666-6666'),
('456.789.123-45', '+55 88 9 7777-7777'),
('456.789.123-45', '+55 88 9 8888-8888'),
('567.891.234-56', '+55 88 9 9999-9999'),
('567.891.234-56', '+55 88 9 0000-0000'),
('678.912.345-67', '+55 88 9 1122-3344'),
('678.912.345-67', '+55 88 9 5566-7788'),
('789.123.456-78', '+55 88 9 1212-3434'),
('789.123.456-78', '+55 88 9 5656-7878'),
('890.234.567-89', '+55 88 9 1313-3535'),
('890.234.567-89', '+55 88 9 5757-7979');

    --alergias dos pacientes

INSERT INTO paciente_alergias(id_pac, alergia)
VALUES
    ('123.456.789-12', 'Amendoim'),
    ('123.456.789-12', 'Penicilina'),
    ('234.567.891-23', 'Frutos do mar'),
    ('234.567.891-23', 'Aspirina'),
    ('345.678.912-34', 'Lactose'),
    ('345.678.912-34', 'Codeína'),
    ('456.789.123-45', 'Glúten'),
    ('456.789.123-45', 'Ibuprofeno'),
    ('567.891.234-56', 'Nozes'),
    ('567.891.234-56', 'Morfina'),
    ('678.912.345-67', 'Ovos'),
    ('678.912.345-67', 'Sulfa'),
    ('789.123.456-78', 'Amendoim'),
    ('789.123.456-78', 'Insulina'),
    ('890.234.567-89', 'Leite'),
    ('890.234.567-89', 'Paracetamol');

--INSERTION MEDICOS
INSERT INTO medico (CPF_med, nome_med, sobrenome_med, data_nascimento_med, genero_med, cidade_med, bairro_med, rua_med, numero_casa_med, senha_med, email_med, especialidade_med, data_contratacao_med, horarios_trabalho_med, grau_especializacao_med, salario_med, dias_trabalho_med)
VALUES
    ('123.456.789-99', 'Joana', 'Silva', '1988-01-06', 'F', 'Rio de Janeiro', 'Copacabana', 'Avenida Atlântica', 123, 'Joana123', 'joana@gmail.com', 'Cardiologia', '2023-01-15', '9h - 17h', 'Bacharelado', 7000.00, 'Seg, Qua, Sex'),
    ('987.654.321-54', 'Lucas', 'Melo', '1970-01-06', 'M', 'São Paulo', 'Jardins', 'Rua Oscar Freire', 456, 'Lucas987', 'lucas@outlook.com', 'Ortopedia', '2021-02-20', '8h - 16h', 'Doutorado', 12000.00, 'Ter, Qui, Sáb'),
    ('456.789.123-98', 'Cosme', 'Rocha', '1962-11-26', 'M', 'Belo Horizonte', 'Savassi', 'Avenida Getúlio Vargas', 789, 'Cosme456', 'cosme@hotmail.com', 'Gastroenterologia', '2018-03-25', '9h - 18h', 'Mestrado', 10000.00, 'Seg, Qua, Sex'),
    ('321.654.987-32', 'Hildegarda', 'Almeida', '1979-09-16', 'F', 'Salvador', 'Pelourinho', 'Largo do Pelourinho', 23, 'Hildegarda321', 'hildegarda@gmail.com', 'Radiologia', '2018-04-10', '8h - 16h', 'Bacharelado', 7000.00, 'Ter, Qui, Sáb'),
    ('234.567.890-21', 'Maria', 'Pereira', '1986-08-02', 'F', 'Recife', 'Boa Viagem', 'Rua da Amoeba', 55, 'Maria234', 'maria@outlook.com', 'Obstetrícia', '2022-05-05', '9h - 17h', 'Doutorado', 12000.00, 'Seg, Qua, Sex'),
    ('543.789.123-66', 'Geraldo', 'Ferreira', '1986-07-02', 'M', 'Fortaleza', 'Meireles', 'Avenida Beira-Mar', 789, 'Geraldo543', 'geraldo@gmail.com', 'Cirurgia Geral', '2020-06-15', '8h - 16h', 'Mestrado', 10000.00, 'Ter, Qui, Sáb'),
    ('876.543.219-45', 'Rafael', 'Campos', '1986-06-02', 'M', 'Curitiba', 'Batel', 'Rua Vicente Machado', 345, 'Rafael876', 'rafael@hotmail.com', 'Clínico Geral', '2020-07-10', '9h - 17h', 'Bacharelado', 7000.00, 'Seg, Qua, Sex'),
    ('657.432.987-77', 'Catarina', 'Santos', '1975-03-25', 'F', 'Porto Alegre', 'Moinhos de Vento', 'Rua Padre Chagas', 99, 'Catarina657', 'catarina@gmail.com', 'Cardiologia', '2020-08-20', '8h - 16h', 'Doutorado', 12000.00, 'Ter, Qui, Sáb'),
    ('345.678.901-10', 'Martim', 'Pereira', '1980-11-11', 'M', 'Brasília', 'Asa Sul', 'Quadra 104', 12, 'Martim345', 'martim@gmail.com', 'Radiologia', '2020-09-05', '9h - 17h', 'Mestrado', 10000.00, 'Seg, Qua, Sex'),
    ('789.012.345-43', 'Clara', 'Lima', '1989-08-02', 'F', 'Vitória', 'Praia do Canto', 'Avenida Rio Branco', 456, 'Clara789', 'clara@hotmail.com', 'Ortopedia', '2020-10-10', '8h - 16h', 'Doutorado', 12000.00, 'Ter, Qui, Sáb');

    --telefone medicos
INSERT INTO medico_telefone (id_med, telefone_med)
VALUES
('123.456.789-99', '+55 85 9 1234-5678'),
('123.456.789-99', '+55 85 9 9876-5432'),
('987.654.321-54', '+55 85 9 2345-6789'),
('987.654.321-54', '+55 85 9 8765-4321'),
('456.789.123-98', '+55 85 9 3456-7890'),
('456.789.123-98', '+55 85 9 8907-6543'),
('321.654.987-32', '+55 85 9 4567-8901'),
('321.654.987-32', '+55 85 9 9012-3456'),
('234.567.890-21', '+55 85 9 5678-9012'),
('234.567.890-21', '+55 85 9 9012-3456'),
('543.789.123-66', '+55 85 9 6789-0123'),
('543.789.123-66', '+55 85 9 0123-4567'),
('876.543.219-45', '+55 85 9 7890-1234'),
('876.543.219-45', '+55 85 9 1234-5678'),
('657.432.987-77', '+55 85 9 8901-2345'),
('657.432.987-77', '+55 85 9 2345-6789'),
('345.678.901-10', '+55 85 9 1111-1111'),
('345.678.901-10', '+55 85 9 2222-2222'),
('789.012.345-43', '+55 85 9 3333-3333');

    --afiliação médicos

INSERT INTO medico_afiliacao (id_med, med_espec)
VALUES
('123.456.789-99', 'Conselho Federal de Medicina'),
('987.654.321-54', 'Associação Médica Brasileira'),
('456.789.123-98', 'Sociedade Brasileira de Gastroenterologia'),
('456.789.123-98', 'Associação Médica Brasileira'),
('321.654.987-32', 'Conselho Federal de Medicina'),
('234.567.890-21', 'Associação Brasileira de Obstetrícia e Ginecologia'),
('543.789.123-66', 'Associação Médica Brasileira'),
('876.543.219-45', 'Conselho Federal de Medicina'),
('657.432.987-77', 'Sociedade Brasileira de Cardiologia'),
('657.432.987-77', 'Associação Médica Brasileira'),
('345.678.901-10', 'Associação Brasileira de Radiologia'),
('789.012.345-43', 'Associação Médica Brasileira');


--INSERTION ENFERMEIROS

INSERT INTO enfermeiro(CPF_enf, nome_enf, sobrenome_enf, data_nascimento_enf, genero_enf, cidade_enf, bairro_enf, rua_enf, numero_casa_enf, senha_enf, email_enf, data_contratacao_enf, horarios_trabalho_enf, grau_especializacao_enf, salario_enf, dias_trabalho_enf)
VALUES 
    ('988.122.344-87', 'Louis', 'Barreto', '1987-01-01', 'M', 'Recife', 'Água fria', 'Sérgio Portilhole', 190, 'salvarVidas_eu_', 'enfermeiroReal@gmail.com', '2020-03-01', '9h - 17h', 'Bacharelado', '2045.00','Seg, Qua, Sex'),
    ('123.456.789-13', 'Ana', 'Pereira', '1983-07-25', 'F', 'Fortaleza', 'Aldeota', 'Rua A', 123, 'SenhA12345', 'ana@gmail.com', '2017-08-15', '8h-16h', 'Mestrado', 4200.00, 'Seg, Ter, Qua, Qui, Sex'),
    ('987.654.321-12', 'Carlos', 'Silva', '1986-04-12', 'M', 'Fortaleza', 'Meireles', 'Rua B', 456, 'Senha_54321', 'carlos@outlook.com', '2019-03-10', '7h-15h', 'Bacharelado', 3500.00, 'Seg, Ter, Qua, Qui, Sex'),
    ('234.567.890-11', 'Larissa', 'Oliveira', '1975-10-08', 'F', 'Caucaia', 'Centro', 'Rua C', 789, 'MinhaSenha123', 'larissa@hotmail.com', '2016-09-20', '9h-17h', 'Técnico', 3200.00, 'Seg, Ter, Qua, Qui, Sex'),
    ('456.789.123-12', 'Lucas', 'Fernandes', '1987-12-03', 'M', 'Sobral', 'Aldeota', 'Rua D', 234, 'Senha1234567', 'lucas@gmail.com', '2018-05-05', '8h-16h', 'Mestrado', 4500.00, 'Seg, Ter, Qua, Qui, Sex'),
    ('789.123.456-12', 'Isabela', 'Lima', '1979-08-22', 'F', 'Fortaleza', 'Messejana', 'Rua E', 567, 'SenhaEnf123', 'isabela@outlook.com', '2017-06-14', '7h-15h', 'Técnico', 3400.00, 'Seg, Ter, Qua, Qui, Sex'),
    ('234.567.890-12', 'Mariano', 'Rodrigues', '1981-02-17', 'M', 'Caucaia', 'Pabussu', 'Rua F', 321, 'Senha321', 'mariano@hotmail.com', '2016-07-15', '8h-16h', 'Técnico', 3300.00, 'Seg, Ter, Qua, Qui, Sex'),
    ('543.321.654-12', 'Helena', 'Nunes', '1982-06-19', 'F', 'Fortaleza', 'Aldeota', 'Rua G', 765, 'MinhaSenha1', 'helena@gmail.com', '2019-08-30', '9h-17h', 'Bacharelado', 3800.00, 'Seg, Ter, Qua, Qui, Sex'),
    ('678.987.654-12', 'Rafael', 'Pereira', '1980-04-27', 'M', 'Sobral', 'Centro', 'Rua H', 987, 'SenhaEnfermeiro', 'rafael@hotmail.com', '2018-09-01', '8h-16h', 'Bacharelado', 3800.00, 'Seg, Ter, Qua, Qui, Sex'),
    ('765.432.109-12', 'Fernanda', 'Martins', '1977-09-14', 'F', 'Fortaleza', 'Messejana', 'Rua I', 543, 'Senha12345', 'fernanda@gmail.com', '2015-10-25', '8h-16h', 'Bacharelado', 3600.00, 'Seg, Ter, Qua, Qui, Sex');

    --telefone enfermeiros

INSERT INTO enfermeiro_telefone(id_enf, telefone_enf)
VALUES

('988.122.344-87', '+55 89 9 1234-5678'),
('988.122.344-87', '+55 89 9 9876-5432'),
('123.456.789-13', '+55 89 9 2345-6789'),
('123.456.789-13', '+55 89 9 8765-4321'),
('987.654.321-12', '+55 89 9 3456-7890'),
('987.654.321-12', '+55 89 9 8907-6543'),
('234.567.890-11', '+55 89 9 4567-8901'),
('234.567.890-11', '+55 89 9 9012-3456'),
('456.789.123-12', '+55 89 9 5678-9012'),
('456.789.123-12', '+55 89 9 9012-3456'),
('789.123.456-12', '+55 89 9 6789-0123'),
('789.123.456-12', '+55 89 9 0123-4567'),
('234.567.890-12', '+55 89 9 7890-1234'),
('234.567.890-12', '+55 89 9 1234-5678'),
('543.321.654-12', '+55 89 9 8901-2345'),
('543.321.654-12', '+55 89 9 2345-6789'),
('678.987.654-12', '+55 89 9 1111-1111'),
('678.987.654-12', '+55 89 9 2222-2222'),
('765.432.109-12', '+55 89 9 3333-3333');

--INSERÇÕES DA HOTELARIA HOSPITALAR :

/*UTI,enfermaria,sala cirúrgica*/

INSERT INTO hotelaria_hospitalar(nome_hotelaria,total_leitos)
VALUES
    ('UTI',25),
    ('Enfermaria', 30),
    ('Sala cirúrgica', 6);

--Inserções consultório
INSERT INTO consultorio(especialidade_consultorio)
VALUES
    ('Cardiologia'),
    ('Cardiologia'),
    ('Ortopedia'),
    ('Ortopedia'),
    ('Gastroenterologia'),
    ('obstetrícia'),
    ('geral'),
    ('geral'),
    ('geral'),
    ('geral');

--INSERÇÕES DAS RELAÇÕES

    --estar_alocado

INSERT INTO estar_alocado(id_med, id_consultorio)
VALUES
    ('123.456.789-99', 1),
    ('987.654.321-54', 3),
    ('456.789.123-98', 5),
    ('321.654.987-32', 7),
    ('234.567.890-21', 6),
    ('543.789.123-66', 8),
    ('876.543.219-45', 9),
    ('657.432.987-77', 2),
    ('345.678.901-10', 10),
    ('789.012.345-43', 4);

    --marcar_consulta

INSERT INTO marcar_consulta(id_pac, id_med, data_consulta, horario_consulta)
VALUES
    ('123.456.789-12', '876.543.219-45', '2023-10-18', '10:30:00'),
    ('234.567.891-23', '876.543.219-45', '2023-10-18', '11:00:00'),
    ('122.456.789-12', '876.543.219-45', '2023-10-18', '11:30:00'),
    ('233.567.891-23', '123.456.789-99', '2023-10-18', '12:00:00'),
    ('345.678.912-34', '657.432.987-77', '2023-10-18', '13:00:00'),
    ('456.789.123-45', '234.567.890-21', '2023-10-18', '13:30:00'),
    ('567.891.234-56', '234.567.890-21', '2023-10-18', '14:00:00'),
    ('678.912.345-67', '321.654.987-32', '2023-10-18', '14:30:00'),
    ('789.123.456-78', '876.543.219-45', '2023-10-18', '15:00:00'),
    ('890.234.567-89', '456.789.123-98', '2023-10-18', '15:30:00');

INSERT INTO gerenciar_hotelaria(id_enf, id_hotelaria, data_gerencia, horario_gerencia_inic, horario_gerencia_fim)
VALUES
    ('988.122.344-87', 1, 'Seg, Qua, Qui', '06:00:00', '14:00:00'),
    ('988.122.344-87', 2, 'Seg, Qua, Qui', '06:00:00', '14:00:00'),
    ('988.122.344-87', 3, 'Seg, Qua, Qui', '06:00:00', '14:00:00'),

    ('123.456.789-13', 1, 'Seg, Qua, Qui', '14:00:01', '22:00:00'),
    ('123.456.789-13', 2, 'Seg, Qua, Qui', '14:00:01', '22:00:00'),
    ('123.456.789-13', 3, 'Seg, Qua, Qui', '14:00:01', '22:00:00'),

    ('987.654.321-12', 1, 'Seg, Qua, Qui', '22:00:01', '05:59:59'),
    ('987.654.321-12', 2, 'Seg, Qua, Qui', '22:00:01', '05:59:59'),
    ('987.654.321-12', 3, 'Seg, Qua, Qui', '22:00:01', '05:59:59'),

    ('234.567.890-11', 1, 'Ter, Sex, Sab', '06:00:00', '14:00:00'),
    ('234.567.890-11', 2, 'Ter, Sex, Sab', '06:00:00', '14:00:00'),
    ('234.567.890-11', 3, 'Ter, Sex, Sab', '06:00:00', '14:00:00'),
    
    ('456.789.123-12', 1, 'Ter, Sex, Sab', '14:00:01', '22:00:00'),
    ('456.789.123-12', 2, 'Ter, Sex, Sab', '14:00:01', '22:00:00'),
    ('456.789.123-12', 3, 'Ter, Sex, Sab', '14:00:01', '22:00:00'),

    ('789.123.456-12', 1, 'Ter, Sex, Sab', '22:00:01', '05:59:59'),
    ('789.123.456-12', 2, 'Ter, Sex, Sab', '22:00:01', '05:59:59'),
    ('789.123.456-12', 3, 'Ter, Sex, Sab', '22:00:01', '05:59:59'),

    ('678.987.654-12', 1, 'Dom', '06:00:00', '14:00:00'),
    ('678.987.654-12', 2, 'Dom', '06:00:00', '14:00:00'),
    ('678.987.654-12', 3, 'Dom', '06:00:00', '14:00:00'),
    
    ('765.432.109-12', 1, 'Dom', '04:00:01', '22:00:00'),
    ('765.432.109-12', 2, 'Dom', '04:00:01', '22:00:00'),
    ('765.432.109-12', 3, 'Dom', '04:00:01', '22:00:00'),

    ('543.321.654-12', 1, 'Dom', '22:00:01', '05:59:59'),
    ('543.321.654-12', 2, 'Dom', '22:00:01', '05:59:59'),
    ('543.321.654-12', 3, 'Dom', '22:00:01', '05:59:59');

INSERT INTO gerar_laudo(id_pac, id_med, diagnostico, prognostico, tratamento)
VALUES
    ('123.456.789-12', '876.543.219-45', 'infecção pulmonar', 'melhorar após medicamentos', 'bezentacil, Ceftriaxona, Azitromicina, Soro de imunoglobulina, repouso, oxigênio'),
    ('234.567.891-23', '876.543.219-45', 'infecção na unha', 'melhorar após medicamentos', 'bezentacil, Ceftriaxona, Azitromicina, Soro de imunoglobulina'),
    ('122.456.789-12', '876.543.219-45', 'envenenamento leve (jararaca pequena)', 'melhorar após uso de anti-ofidicos', 'soro antiofídico botrópico x2'),
    ('233.567.891-23', '123.456.789-99', 'Hipertensão', 'melhorar com o uso de medicação', 'losartana potássica'),
    ('345.678.912-34', '657.432.987-77', 'gripe comum e tontura', 'melhorar com o uso de medicação', 'cimegripe'),
    ('456.789.123-45', '234.567.890-21', 'Azia e enjoo', 'melhorar com o uso de medicação', 'estomazil e repouso'),
    ('567.891.234-56', '234.567.890-21', 'enjoo e tontura', 'melhorar com o uso de medicação', 'dramin e repouso'),
    ('678.912.345-67', '321.654.987-32', 'Cancer de esofago', 'avanço da doença', 'quimioterapia'),
    ('789.123.456-78', '876.543.219-45', 'Cancer de unha', 'avanço da doença', 'quimioterapia'),
    ('890.234.567-89', '456.789.123-98', 'Cancer no estomago', 'avanço da doença', 'quimioterapia');

INSERT INTO estar_internado(id_pac, id_hotelaria)
VALUES
    ('123.456.789-12', 1),
    ('234.567.891-23', 2),
    ('122.456.789-12', 2),
    ('233.567.891-23', 2),
    ('345.678.912-34', 2),
    ('456.789.123-45', 2),
    ('567.891.234-56', 2),
    ('678.912.345-67', 2),
    ('789.123.456-78', 2),
    ('890.234.567-89', 2);

INSERT INTO avaliar_recuperacao(id_pac, id_enf, descricao_recuperacao)
VALUES 
    ('123.456.789-12', '988.122.344-87', 'melhorando à passos largos'),
    ('234.567.891-23', '988.122.344-87', 'melhorando à passos largos'),
    ('122.456.789-12', '123.456.789-13', 'melhorando devagarinho'),
    ('233.567.891-23', '987.654.321-12', 'já está boa por agora'),
    ('345.678.912-34', '234.567.890-11', 'já está bom'),
    ('456.789.123-45', '456.789.123-12', 'já está boa'),
    ('567.891.234-56', '456.789.123-12', 'já está boa'),
    ('678.912.345-67', '234.567.890-12', 'humor triste, avanço da doença controlado'),
    ('789.123.456-78', '543.321.654-12', 'humor indiferente, avanço da doença controlado'),
    ('890.234.567-89', '765.432.109-12', 'humor risonho; a doença avança');

--CRIANDO UMA VIEW DOS DADOS DE PACIENTE E LOCAL DE INTERNAÇÃO
CREATE VIEW relatorio_geral AS
SELECT
	paciente.CPF_pac,paciente.nome_pac,paciente.sobrenome_pac,
	paciente.data_nascimento_pac,paciente.genero_pac,paciente.cidade_pac,
	paciente.bairro_pac,paciente.rua_pac,paciente.numero_casa_pac,
	paciente.senha_pac,paciente.email_pac, hotelaria_hospitalar.nome_hotelaria
FROM paciente
INNER JOIN estar_internado ON paciente.CPF_pac = estar_internado.id_pac
INNER JOIN hotelaria_hospitalar ON estar_internado.id_hotelaria = hotelaria_hospitalar.id_hotelaria;
