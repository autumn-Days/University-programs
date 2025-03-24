/*
o nome do time
número de partidas
vitórias
derrotas
empates e pontuação.
*/

/*
Essa linha pode se traduzir como :
    Selecione somente no caso em que o time 2 perder, caso ele ganhou, dá o break
*/

-- Create a view to calculate victories for each team
CREATE VIEW vitoria AS
SELECT
    teams.name,
    COALESCE
    (
        SUM
        (
            CASE
                WHEN 
                    teams.id = matches.team_1 AND
                    matches.team_1_goals > matches.team_2_goals
                THEN
                    1
                WHEN
                    teams.id = matches.team_2 AND
                    matches.team_2_goals > matches.team_1_goals
                THEN
                    1
                ELSE
                    0
                END
        ),0
    ) AS vitorias
FROM
    teams
LEFT JOIN matches ON teams.id = matches.team_1-- OR team_id = matches.team_2
GROUP BY teams.name;

CREATE VIEW derrota AS
SELECT
    teams.name,
    COALESCE
    (
        SUM
        (
            CASE
                WHEN 
                    teams.id = matches.team_1 AND
                    matches.team_1_goals < matches.team_2_goals
                THEN
                    1
                WHEN
                    teams.id = matches.team_2 AND
                    matches.team_2_goals < matches.team_1_goals
                THEN
                    1
                ELSE
                    0
                END
        ),0
    ) AS derrotas
FROM
    teams
LEFT JOIN matches ON teams.id = matches.team_1-- OR team_id = matches.team_2
GROUP BY teams.name;

SELECT * FROM vitoria, derrota;

CREATE VIEW empate AS
SELECT
    teams.name,
    COALESCE
    (
        SUM
        (
            CASE
                WHEN 
                    teams.id = matches.team_1 AND
                    matches.team_1_goals = matches.team_2_goals
                THEN
                    1
                WHEN
                    teams.id = matches.team_2 AND
                    matches.team_2_goals = matches.team_1_goals
                THEN
                    1
                ELSE
                    0
                END
        ),0
    ) AS empates
FROM
    teams
LEFT JOIN matches ON teams.id = matches.team_1-- OR team_id = matches.team_2
GROUP BY teams.name;