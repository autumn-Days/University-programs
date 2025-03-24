SELECT name,
FROM customers, legal_person
WHERE legal_person.id_customers = customers.id;
